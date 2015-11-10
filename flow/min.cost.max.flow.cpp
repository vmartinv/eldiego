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
ll parche = 0;

const int MAXN=10000;
const ll INF = 1e14;

struct edge {
	int u, v;
	ll cap, cost, flow;
	ll rem() { return cap - flow; }
};
int nodes;//numero de nodos
vector<int> G[MAXN];
vector<edge> e;
void addEdge(int u, int v, ll cap, ll cost) {
	G[u].pb(sz(e)); e.pb((edge){u,v,cap,cost,0});
	G[v].pb(sz(e)); e.pb((edge){v,u,0,-cost,0});
}
ll pot[MAXN], dist[MAXN], pre[MAXN], cap[MAXN];
ll mxFlow, mnCost;
void flow(int s, int t) {
	fill(pot, pot+nodes, 0);
	mxFlow=mnCost=0;
	while(1){
		fill(dist, dist+nodes, INF); dist[s] = 0;
		fill(pre, pre+nodes, -1); pre[s]=0;
		fill(cap, cap+nodes, 0); cap[s] = INF;
		priority_queue<pair<ll,int> > q; q.push(make_pair(0,s));
		//~ Bellman Ford
		//~ forn(i,nodes) {
			//~ forn(j,sz(e)) if (e[j].rem()) {
				//~ ll c = e[j].cost + pot[e[j].u] - pot[e[j].v];
				//~ if (dist[e[j].v] > dist[e[j].u] + c) {
					//~ dist[e[j].v] = dist[e[j].u] + c;
					//~ pre[e[j].v] = j;
					//~ cap[e[j].v] = min(cap[e[j].u], e[j].rem());
			//~ } }
		//~ }
		//~ Dijkstra
		while (!q.empty()) {
			pair<ll,int> top = q.top(); q.pop();
			int u = top.second;
			ll d = -top.first;
			if (u == t) break;
			if (d > dist[u]) continue;
			forn(i,sz(G[u])) {
				edge E = e[G[u][i]];
				ll c = E.cost + pot[u] - pot[E.v];
				if (E.rem() && dist[E.v] > dist[u] + c) {
					dist[E.v] = dist[u] + c;
					pre[E.v] = G[u][i];
					cap[E.v] = min(cap[u], E.rem());
					q.push(make_pair(-dist[E.v], E.v));
				}
			}
		}
		if (pre[t] == -1) break;
		forn(u,nodes) 
			if (dist[u] == INF) pot[u] = INF;
			else pot[u] += dist[u];
		mxFlow +=cap[t];
		mnCost +=cap[t]*pot[t];
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
