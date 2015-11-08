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

//Compilar: g++ --std=c++11
struct Hash{
	size_t operator()(const ii &a)const{
		size_t s=hash<int>()(a.fst);
		return hash<int>()(a.snd)+0x9e3779b9+(s<<6)+(s>>2);
	}
	size_t operator()(const vector<int> &v)const{
		size_t s=0;
		for(auto &e : v)
			s ^= hash<int>()(e)+0x9e3779b9+(s<<6)+(s>>2);
		return s;
	}
};
unordered_set<ii, Hash> s;
unordered_map<ii, int, Hash> m;//map<key, value, hasher>

int main() {
    srand(time(NULL));
	set<size_t> coli;
    forn(i, 1000000){
		s.insert(ii(rand()%10000, rand()%10000));
		coli.insert(Hash()(ii(rand()%10000, rand()%10000)));
    }
    dprint(sz(coli));
	return 0;
}
