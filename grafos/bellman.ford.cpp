vector<ii> G[MAX_N];//ady. list with pairs (weight, dst)
int dist[MAX_N];
void bford(int src){//O(VE)
	dist[src]=0;
	forn(i, N-1) forn(j, N) if(dist[j]!=INF) forall(it, G[j])
		dist[it->snd]=min(dist[it->snd], dist[j]+it->fst);
}

bool hasNegCycle(){
	forn(j, N) if(dist[j]!=INF) forall(it, G[j])
		if(dist[it->snd]>dist[j]+it->fst) return true;
	//inside if: all points reachable from it->snd will have -INF distance(do bfs)
	return false;
}
