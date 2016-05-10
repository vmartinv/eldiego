#define INF 1e9
int N;
#define MAX_V 250001
vector<ii> G[MAX_V];
//To add an edge use
#define add(a, b, w) G[a].pb(make_pair(w, b))
ll dijkstra(int s, int t){//O(|E| log |V|)
	priority_queue<ii, vector<ii>, greater<ii> > Q;
	vector<ll> dist(N, INF); vector<int> dad(N, -1);
	Q.push(make_pair(0, s)); dist[s] = 0;
	while(sz(Q)){
		ii p = Q.top(); Q.pop();
		if(p.snd == t) break;
		forall(it, G[p.snd])
			if(dist[p.snd]+it->first < dist[it->snd]){
				dist[it->snd] = dist[p.snd] + it->fst;
				dad[it->snd] = p.snd;
				Q.push(make_pair(dist[it->snd], it->snd));	}
	}
	return dist[t];
	if(dist[t]<INF)//path generator
		for(int i=t; i!=-1; i=dad[i])
			printf("%d%c", i, (i==s?'\n':' '));}
