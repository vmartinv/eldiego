#include <bits/stdc++.h>
using namespace std;
#define dprint(v) cout << #v"=" << v << endl //;)
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

const int MAXN=10000;
typedef ll tf;
typedef ll tc;
const tf INFFLUJO = 1e14;
const tc INFCOSTO = 1e14;
struct edge {
	int u, v;
	tf cap, flow;
	tc cost;
	tf rem() { return cap - flow; }
};
int nodes; //numero de nodos
vector<int> G[MAXN]; // limpiar!
vector<edge> e;  // limpiar!
void addEdge(int u, int v, tf cap, tc cost) {
	G[u].pb(sz(e)); e.pb((edge){u,v,cap,0,cost});
	G[v].pb(sz(e)); e.pb((edge){v,u,0,0,-cost});
}
tc dist[MAXN], mnCost;
int pre[MAXN];
tf cap[MAXN], mxFlow;
bool in_queue[MAXN];
void flow(int s, int t) {
	zero(in_queue);
	mxFlow=mnCost=0;
	while(1){
		fill(dist, dist+nodes, INFCOSTO); dist[s] = 0;
		memset(pre, -1, sizeof(pre)); pre[s]=0;
		zero(cap); cap[s] = INFFLUJO;		
		queue<int> q; q.push(s); in_queue[s]=1;
		while(sz(q)){
			int u=q.front(); q.pop(); in_queue[u]=0;
			for(auto it:G[u]) {
				edge &E = e[it];
				if(E.rem() && dist[E.v] > dist[u] + E.cost + 1e-9){ // ojo EPS
					dist[E.v]=dist[u]+E.cost;
					pre[E.v] = it;
					cap[E.v] = min(cap[u], E.rem());
					if(!in_queue[E.v]) q.push(E.v), in_queue[E.v]=1;
				}
			}
		}
		if (pre[t] == -1) break;
		mxFlow +=cap[t];
		mnCost +=cap[t]*dist[t];
		for (int v = t; v != s; v = e[pre[v]].u) {
			e[pre[v]].flow += cap[t];
			e[pre[v]^1].flow -= cap[t];
		}
	}
}


int u[MAXN],v[MAXN];
ll cst[MAXN],D,K;

int main() {
//problema ejemplo uva 10594
//http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1535
	//~ freopen("in", "r", stdin);
	int N, M;
	while(cin >> N >> M){
		zero(G), e.clear();
		forn(i, M){
			scanf("%d %d %lld",&u[i],&v[i],&cst[i]);
			--u[i], --v[i];
		}
		scanf("%lld %lld",&D,&K);
		addEdge(0,1,D,0);

		forn(i, M){
			addEdge(u[i]+1,v[i]+1,K,cst[i]);
			addEdge(v[i]+1,u[i]+1,K,cst[i]);
		}
		nodes = N+1;
		flow(0,N);		
		if(mxFlow!=D) printf("Impossible.\n");
		else printf("%lld\n", mnCost);
	}
	return 0;
}
