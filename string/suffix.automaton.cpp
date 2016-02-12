#include <bits/stdc++.h>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int,int> ii;

struct St {
    int len;
    St *link;
    map<char,St*> next;
    St(int len, St* link=NULL):len(len),link(link){}
};
struct SuA{
    St *init, *last;
    SuA(): init(new St(0)), last(init) {}
    void extend(char c){
        St *cur=new St(last->len+1, init), *p=last;
        for(;p && !p->next.count(c); p=p->link) p->next[c]=cur;
        if(p){
            St *q=p->next[c];
            if(p->len+1==q->len) cur->link=q;
            else{
                St *clone = new St(p->len+1, q->link);
                clone->next = q->next;
                for(;p && p->next.count(c) && p->next[c]==q; p=p->link)
                    p->next[c] = clone;
                q->link = cur->link = clone;
            }
        }
        last = cur;
    }
}aut;


int main() {
    string s; cin >> s;
    aut=SuA();
    forn(i, sz(s)) aut.extend(s[i]);	
	return 0;
}
