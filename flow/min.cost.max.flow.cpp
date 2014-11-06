#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define dprint(a) cerr << #a << "=" << a << endl;
#define pb push_back
#define zero(v) memset(v, 0, sizeof(v))
#define mkp make_pair
typedef long long ll;


const int MAXN=1+2*100;
const int INF = 1<<29;


struct edge {
	int u, v;
	ll cap, cost, flow;
	ll rem() { return cap - flow; }
};
int n;//numero de nodos
vector<int> G[MAXN];
vector<edge> e;
void addEdge(int u, int v, ll cap, ll cost) {
	G[u].pb(si(e)); e.pb((edge){u,v,cap,cost,0});
	G[v].pb(si(e)); e.pb((edge){v,u,0,-cost,0});
}
ll pot[MAXN], dist[MAXN], pre[MAXN], cap[MAXN];
ll mxFlow, mnCost;
void flow(int s, int t) {
	fill(pot, pot+n, 0);
	mxFlow=mnCost=0;
	while(1){
		fill(dist, dist+n, INF); dist[s] = 0;
		fill(pre, pre+n, -1); pre[s]=0;
		fill(cap, cap+n, 0); cap[s] = INF;
		priority_queue<pair<ll,int> > q; q.push(mkp(0,s));
		while (!q.empty()) {
			pair<ll,int> top = q.top(); q.pop();
			int u = top.second, d = -top.first;
			if (u == t) break;
			if (d > dist[u]) continue;
			forn(i,si(G[u])) {
				edge E = e[G[u][i]];
				int c = E.cost + pot[u] - pot[E.v];
				if (E.rem() && dist[E.v] > dist[u] + c) {
					dist[E.v] = dist[u] + c;
					pre[E.v] = G[u][i];
					cap[E.v] = min(cap[u], E.rem());
					q.push(mkp(-dist[E.v], E.v));
				}
			}
		}
		if (pre[t] == -1) break;
		forn(u,n) 
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
	freopen("input.in", "r", stdin);
	int N, M;
	while(cin >> N >> M){
		zero(G), e.clear();
		n = 2*N+1;
		forn(i, M){
			scanf("%d %d %lld",&u[i],&v[i],&cst[i]);
			--u[i], --v[i];
		}
		scanf("%lld %lld",&D,&K);
		addEdge(0,1,D,0);

		forn(i, N) addEdge(1+2*i,1+2*i+1,INF,0);
		forn(i, M){
			addEdge(1+2*u[i]+1,1+2*v[i],K,cst[i]);
			addEdge(1+2*v[i]+1,1+2*u[i],K,cst[i]);
		}
		flow(0,2*N-1);		
		if(mxFlow!=D) printf("Impossible.\n");
		else printf("%lld\n", mnCost);
	}
	
	

}
