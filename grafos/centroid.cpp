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
const int MAXN=100100;

int n;
vector<int> G[MAXN];
bool taken[MAXN];//poner todos en FALSE al principio!!
int padre[MAXN];//padre de cada nodo en el centroid tree

int szt[MAXN];
void calcsz(int v, int p) {
	szt[v] = 1;
	forall(it,G[v]) if (*it!=p && !taken[*it])
		calcsz(*it,v), szt[v]+=szt[*it];
}
void centroid(int v=0, int f=-1, int lvl=0, int tam=-1) {//O(nlogn)
	if(tam==-1)	calcsz(v, -1), tam=szt[v];
	forall(it, G[v]) if(!taken[*it] && szt[*it]>=tam/2)
		{szt[v]=0; centroid(*it, f, lvl, tam); return;}
	taken[v]=true;
	padre[v]=f;
	forall(it, G[v]) if(!taken[*it])
		centroid(*it, v, lvl+1, -1);
}


//f[v][k] holds the 2^k father of v
//L[v] holds the level of v
int f[MAXN][20], L[MAXN];
//call before build:
void dfs(int v, int fa=-1, int lvl=0){//generate required data
	f[v][0]=fa, L[v]=lvl;
	forall(it, G[v])if(*it!=fa)
		dfs(*it, v, lvl+1);
}
void build(){//f[i][0] must be filled previously, O(nlgn)
	forn(k, 20-1) forn(i, n) f[i][k+1]=f[f[i][k]][k];}
	
#define lg(x) (31-__builtin_clz(x))//=floor(log2(x))

int climb(int a, int d){//O(lgn)
	if(!d) return a;
	dforn(i, lg(L[a])+1)
		if(1<<i<=d)
			a=f[a][i], d-=1<<i;
    return a;
}
int lca(int a, int b){//O(lgn)
	if(L[a]<L[b]) swap(a, b);
	a=climb(a, L[a]-L[b]);
	if(a==b) return a;
	dforn(i, lg(L[a])+1)
		if(f[a][i]!=f[b][i])
			a=f[a][i], b=f[b][i];
	return f[a][0];
}
int dist(int a, int b) {
	return L[a]+L[b]-2*L[lca(a, b)];}
	
	
int dstsub[MAXN];
void update(int v, int org){
	dstsub[v]=min(dstsub[v], dist(v, org));
	if(padre[v]!=-1) update(padre[v], org);
}
int query(int v, int org){
	if(padre[v]==-1) return dstsub[v]+dist(v, org);
	return min(dstsub[v]+dist(v, org), query(padre[v], org));
}

int main() {
	//~ freopen("input.in", "r", stdin);
//PROBLEMA EJEMPLO:
//http://codeforces.com/contest/342/problem/E
    ios::sync_with_stdio(0);
    int queris;
	while(cin >> n >> queris){
		zero(G);
		zero(taken);
		forn(i, n-1){
			int a,b; cin >> a >> b; a--, b--;
			G[a].pb(b), G[b].pb(a);
		}
		centroid();
		dfs(0);
		build();
		forn(i, n) dstsub[i]=1e9;
		update(0, 0);
		while(queris--){
			int t,v;
			cin>> t >> v; v--;
			if(t==1) update(v, v);
			else cout << query(v, v) << endl;
		}
	}
	return 0;
}
