#define MAX_V 1000
#define INF 1e9
//special nodes
#define SRC 0
#define SNK 1
map<int, int> G[MAX_V];//limpiar esto
//To add an edge use
#define add(a, b, w) G[a][b]=w
int f, p[MAX_V];
void augment(int v, int minE){
	if(v==SRC) f=minE;
	else if(p[v]!=-1){
		augment(p[v], min(minE, G[p[v]][v]));
		G[p[v]][v]-=f, G[v][p[v]]+=f;
	}
}
ll maxflow(){//O(VE^2)
	ll Mf=0;
	do{
		f=0;
		char used[MAX_V]; queue<int> q; q.push(SRC);
		zero(used), memset(p, -1, sizeof(p));
		while(sz(q)){
			int u=q.front(); q.pop();
			if(u==SNK) break;
			forall(it, G[u])
				if(it->snd>0 && !used[it->fst])
					used[it->fst]=true, q.push(it->fst), p[it->fst]=u;
		}
		augment(SNK, INF);
		Mf+=f;
	}while(f);
	return Mf;
}
