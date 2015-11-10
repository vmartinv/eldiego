#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
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
const int MAXN=100100;
vector<int> G[MAXN];
int n;

int treesz[MAXN];//cantidad de nodos en el subarbol del nodo v
int dad[MAXN];//dad[v]=padre del nodo v
void dfs1(int v, int p=-1){//pre-dfs
	dad[v]=p;
	treesz[v]=1;
	forall(it, G[v]) if(*it!=p){
		dfs1(*it, v);
		treesz[v]+=treesz[*it];
	}
}
//PONER Q EN 0  !!!!!
int pos[MAXN], q;//pos[v]=posicion del nodo v en el recorrido de la dfs
//Las cadenas aparecen continuas en el recorrido!
int cantcad;
int homecad[MAXN];//dada una cadena devuelve su nodo inicial
int cad[MAXN];//cad[v]=cadena a la que pertenece el nodo
void heavylight(int v, int cur=-1){
	if(cur==-1) homecad[cur=cantcad++]=v;
	pos[v]=q++;
	cad[v]=cur;
	int mx=-1;
	forn(i, sz(G[v])) if(G[v][i]!=dad[v])
		if(mx==-1 || treesz[G[v][mx]]<treesz[G[v][i]]) mx=i;
	if(mx!=-1) heavylight(G[v][mx], cur);
	forn(i, sz(G[v])) if(i!=mx && G[v][i]!=dad[v])
		heavylight(G[v][i], -1);
}
//ejemplo de obtener el maximo numero en el camino entre dos nodos
//RTA: max(query(low, u), query(low, v)), con low=lca(u, v)
//esta funcion va trepando por las cadenas
int query(int an, int v){//O(logn)
	//si estan en la misma cadena:
	if(cad[an]==cad[v]) return rmq.get(pos[an], pos[v]+1);
	return max(query(an, dad[homecad[cad[v]]]),
			   rmq.get(pos[homecad[cad[v]]], pos[v]+1));
}
