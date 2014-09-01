#define MAX_V 1000
int N;//valid nodes are [0...N-1]
#define INF 1e9
//special nodes
#define SRC 0
#define SNK 1
map<int, int> G[MAX_V];
//To add an edge use
#define add(a, b, w) G[a][b]=w
ll excess[MAX_V];
int height[MAX_V], active[MAX_V], count[2*MAX_V+1];
queue<int> Q;
void enqueue(int v) { 
	if (!active[v] && excess[v] > 0) active[v]=true, Q.push(v); }
void push(int a, int b) {
	int amt = min(excess[a], ll(G[a][b]));
	if(height[a] <= height[b] || amt == 0) return;
	G[a][b]-=amt, G[b][a]+=amt;
	excess[b] += amt, excess[a] -= amt;
	enqueue(b);
}
void gap(int k) {
	forn(v, N){
		if (height[v] < k) continue;
		count[height[v]]--;
		height[v] = max(height[v], N+1);
		count[height[v]]++;
		enqueue(v);
	}
}
void relabel(int v) {
	count[height[v]]--;
	height[v] = 2*N;
	forall(it, G[v])
		if(it->snd)
			height[v] = min(height[v], height[it->fst] + 1);
	count[height[v]]++;
	enqueue(v);
}
ll maxflow() {//O(V^3)
	zero(height), zero(active), zero(count), zero(excess);
	count[0] = N-1;
	count[N] = 1;
	height[SRC] = N;
	active[SRC] = active[SNK] = true;
	forall(it, G[SRC]){
		excess[SRC] += it->snd;
		push(SRC, it->fst);
	}
	while(sz(Q)) {
		int v = Q.front(); Q.pop();
		active[v]=false;
	forall(it, G[v]) push(v, it->fst);
	if(excess[v] > 0) 
		count[height[v]] == 1? gap(height[v]):relabel(v);
	}
	ll mf=0;
	forall(it, G[SRC]) mf+=G[it->fst][SRC];
	return mf;
}
