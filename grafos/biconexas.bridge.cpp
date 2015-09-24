#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
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
#define fst first
#define snd second

#define pb push_back
typedef long long ll;
typedef pair<int,int> ii;
#define pb push_back

const int MAXN=1010;
int n, m;
vector<int> G[MAXN];

struct edge {
	int u,v, comp;
	bool bridge;
};
vector<edge> e;
void addEdge(int u, int v) {
	G[u].pb(sz(e)), G[v].pb(sz(e));
	e.pb((edge){u,v,-1,false});
}
//d[i]=id de la dfs
//b[i]=lowest id reachable from i
int d[MAXN], b[MAXN], t;
int nbc;//cant componentes
int comp[MAXN];//comp[i]=cant comp biconexas a la cual pertenece i
void initDfs(int n) {
	zero(G), zero(comp);
	e.clear();
	forn(i,n) d[i]=-1;
	nbc = t = 0;
}
stack<int> st;
void dfs(int u, int pe) {//O(n + m)
	b[u] = d[u] = t++;
	comp[u] = (pe != -1);
	forall(ne, G[u]) if (*ne != pe){
		int v = e[*ne].u ^ e[*ne].v ^ u;
		if (d[v] == -1) {
			st.push(*ne);
			dfs(v,*ne);
			if (b[v] > d[u]){
				e[*ne].bridge = true; // bridge
			}
			if (b[v] >= d[u]){ // art
				int last;
				do {
					last = st.top(); st.pop();
					e[last].comp = nbc;
				} while (last != *ne);
				nbc++;
				comp[u]++;
			}
			b[u] = min(b[u], b[v]);
		}
		else if (d[v] < d[u]) { // back edge
			st.push(*ne);
			b[u] = min(b[u], d[v]);
		}
	}
}

int main() {
	//~ freopen("in", "r", stdin);
	while(cin >> n >> m){
		initDfs(n);
		forn(i, m){
			int a,b; cin >> a >> b;
			addEdge(a,b);
		}
		forn(i, n) cout << "comp[" << i << "] = " <<  comp[i] << endl;
		forall(ne, e) cout << ne->u << "->" << ne->v << " en la comp. " << ne->comp << endl;
		cout << "Cant. de componentes biconexas = " << nbc << endl;
	}
    return 0;
}
