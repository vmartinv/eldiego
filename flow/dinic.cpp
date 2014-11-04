#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define zero(v) memset(v, 0, sizeof(v));
#define INF 1e18

const int MAX = 300;
int nodes, src, dest;
int dist[MAX], q[MAX], work[MAX];

struct Edge {
	int to, rev;
	ll f, cap;
	Edge(int to, int rev, ll f, ll cap) : to(to), rev(rev), f(f), cap(cap) {}
};

vector<Edge> G[MAX];

// Adds bidirectional edge
void addEdge(int s, int t, ll cap){
	G[s].push_back(Edge(t, G[t].size(), 0, cap));
	G[t].push_back(Edge(s, G[s].size()-1, 0, 0));
}

bool dinic_bfs() {
	fill(dist, dist + nodes, -1);
	dist[src] = 0;
	int qt = 0;
	q[qt++] = src;
	for (int qh = 0; qh < qt; qh++) {
		int u = q[qh];
		forall(e, G[u]){
			int v = e->to;
			if(dist[v]<0 && e->f < e->cap){
				dist[v]=dist[u]+1;
				q[qt++]=v;
			}
		}
	}
	return dist[dest] >= 0;
}

ll dinic_dfs(int u, ll f) {
	if (u == dest) return f;
	for (int &i = work[u]; i < (int) G[u].size(); i++) {
		Edge &e = G[u][i];
		if (e.cap <= e.f) continue;
		int v = e.to;
		if (dist[v] == dist[u] + 1) {
			ll df = dinic_dfs(v, min(f, e.cap - e.f));
			if (df > 0) {
				e.f += df;
				G[v][e.rev].f -= df;
				return df;
			}
		}
	}
	return 0;
}

ll maxFlow(int _src, int _dest) {//O(V^2 E)<
  src = _src;
  dest = _dest;
  ll result = 0;
  while (dinic_bfs()) {
    fill(work, work + nodes, 0);
    while(ll delta = dinic_dfs(src, INF))
      result += delta;
  }
  
  // todos los nodos  con dist[v]!=-1 vs los que tienen dist[v]==-1 forman el min cut
  
  return result;
}
