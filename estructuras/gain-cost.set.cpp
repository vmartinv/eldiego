#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
typedef long long ll;
typedef pair<int,int> ii;
#define INF 1e9

//esta estructura mantiene pairs(beneficio, costo)
//de tal manera que en el set quedan ordenados
//por beneficio Y COSTO creciente. (va borrando los que no son optimos)
struct V{
	int gain, cost;
	bool operator<(const V &b)const{return gain<b.gain;}
};
set<V> s;
void add(V x){
	set<V>::iterator p=s.lower_bound(x);//primer elemento mayor o igual
	if(p!=s.end() && p->cost <= x.cost) return;//ya hay uno mejor
	p=s.upper_bound(x);//primer elemento mayor
	if(p!=s.begin()){//borro todos los peores (<=beneficio  y >=costo)
		--p;//ahora es ultimo elemento menor o igual
		while(p->cost >= x.cost){
			if(p==s.begin()){s.erase(p); break;}
			s.erase(p--);
		}
	}
	s.insert(x);
}
int get(int gain){//minimo costo de obtener tal ganancia
	set<V>::iterator p=s.lower_bound((V){gain, 0});
	return p==s.end()? INF : p->cost;}

int main() {
	V x;
	while(cout << "pair=", cin >> x.gain >> x.cost){
		add(x);
		forall(it, s) cout << '(' << it->gain << ',' << it->cost << ") "; cout << endl;
	}
    return 0;
}

