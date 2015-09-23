#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
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

typedef int tipo;
tipo oper(const tipo &a, const tipo &b){
    return a+b;
}
struct node{
	tipo v; node *l,*r;
	node(tipo v):v(v), l(NULL), r(NULL) {}
    node(node *l, node *r) : l(l), r(r){
        if(!l) v=r->v;
        else if(!r) v=l->v;
        else v=oper(l->v, r->v);
    }
};
node *build (tipo *a, int tl, int tr) {//modificar para que tome tipo a
	if (tl+1==tr) return new node(a[tl]);
	int tm=(tl + tr)>>1;
	return new node(build(a, tl, tm), build(a, tm, tr));
}
node *update(int pos, int new_val, node *t, int tl, int tr){
	if (tl+1==tr) return new node(new_val);
	int tm=(tl+tr)>>1;
	if(pos < tm) return new node(update(pos, new_val, t->l, tl, tm), t->r);
	else return new node(t->l, update(pos, new_val, t->r, tm, tr));
}
tipo get(int l, int r, node *t, int tl, int tr){
    if(l==tl && tr==r) return t->v;
	int tm=(tl + tr)>>1;
    if(r<=tm) return get(l, r, t->l, tl, tm);
    else if(l>=tm) return get(l, r, t->r, tm, tr);
	return oper(get(l, tm, t->l, tl, tm), get(tm, r, t->r, tm, tr));
}

int vv[10000];
      
int main() {
	//~ freopen("in", "r", stdin);
	int n=8, a,b; char c[10];
	node *root=build(vv, 0, n);
	while(scanf("%s %d %d", c, &a, &b)>0){
		if(tolower(c[0])=='s') root=update(a, b, root, 0, n);
		else printf("%d\n", get(a, b, root, 0, n));
	}
	return 0;
}
