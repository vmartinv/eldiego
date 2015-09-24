#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
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
#define INF 1e9
typedef long long ll;
typedef pair<int,int> ii;

const int maxnodes = 2200;
int nodes, src, dest;
int dist[maxnodes], q[maxnodes], work[maxnodes];

struct Edge {
  int to, rev;
  ll f, cap;
  Edge(int to, int rev, ll f, ll cap) : to(to), rev(rev), f(f), cap(cap) {}
};

vector<Edge> g[maxnodes];

// Adds bidirectional edge
void addEdge(int s, int t, ll cap){
  Edge a = Edge(t, g[t].size(), 0, cap);
  Edge b = Edge(s, g[s].size(), 0, 0);
  g[s].push_back(a);
  g[t].push_back(b);
}

bool dinic_bfs() {
  fill(dist, dist + nodes, -1);
  dist[src] = 0;
  int qt = 0;
  q[qt++] = src;
  for (int qh = 0; qh < qt; qh++) {
    int u = q[qh];
    for (int j = 0; j < (int) g[u].size(); j++) {
      Edge &e = g[u][j];
      int v = e.to;
      if (dist[v] < 0 && e.f < e.cap) {
        dist[v] = dist[u] + 1;
        q[qt++] = v;
      }
    }
  }
  return dist[dest] >= 0;
}

ll dinic_dfs(int u, ll f) {
  if (u == dest)
    return f;
  for (int &i = work[u]; i < (int) g[u].size(); i++) {
    Edge &e = g[u][i];
    if (e.cap <= e.f) continue;
    int v = e.to;
    if (dist[v] == dist[u] + 1) {
      ll df = dinic_dfs(v, min(f, e.cap - e.f));
      if (df > 0) {
        e.f += df;
        g[v][e.rev].f -= df;
        return df;
      }
    }
  }
  return 0;
}

ll maxFlow(int _src, int _dest) {
  src = _src;
  dest = _dest;
  ll result = 0;
  while (dinic_bfs()) {
    fill(work, work + nodes, 0);
    while (ll delta = dinic_dfs(src, INF))
      result += delta;
  }
  return result;
}

void cleanDinic() {
	forn(i,nodes) g[i].clear();
}

// asume que el dinic YA ESTA tirado
// asume que nodes-1 y nodes-2 son la fuente y destino
int match[maxnodes]; // match[v]=u si u-v esta en el matching, -1 si v no esta matcheado
int s[maxnodes]; // numero de la bfs del koning
queue<int> kq;
// s[e]%2==1  o si e esta en V1 y s[e]==-1-> lo agarras 
void koning() {//O(n)
	forn(v,nodes-2) s[v] = match[v] = -1;
	forn(v,nodes-2) forall(it,g[v]) if (it->to < nodes-2 && it->f>0)
		{ match[v]=it->to; match[it->to]=v;}
	forn(v,nodes-2) if (match[v]==-1) {s[v]=0;kq.push(v);}
	while(!kq.empty()) {
		int e = kq.front(); kq.pop();
		if (s[e]%2==1) {
			s[match[e]] = s[e]+1;
			kq.push(match[e]);
		} else {
			
			forall(it,g[e]) if (it->to < nodes-2 && s[it->to]==-1) {
				s[it->to] = s[e]+1;
				kq.push(it->to);
			}
		}
	}
}


int main() {
    return 0;
}
