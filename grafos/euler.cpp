int n,m,ars[MAXE], eq;
vector<int> G[MAXN];//fill G,n,m,ars,eq
list<int> path;
int used[MAXN];
bool usede[MAXE];
queue<list<int>::iterator> q;
int get(int v){
	while(used[v]<sz(G[v]) && usede[ G[v][used[v]] ]) used[v]++;
	return used[v];
}
void explore(int v, int r, list<int>::iterator it){
	int ar=G[v][get(v)]; int u=v^ars[ar];
	usede[ar]=true;
	list<int>::iterator it2=path.insert(it, u);
	if(u!=r) explore(u, r, it2);
	if(get(v)<sz(G[v])) q.push(it);
}
void euler(){
	zero(used), zero(usede);
	path.clear();
	q=queue<list<int>::iterator>();
	path.push_back(0); q.push(path.begin());
	while(sz(q)){
		list<int>::iterator it=q.front(); q.pop();
		if(used[*it]<sz(G[*it])) explore(*it, *it, it);
	}
	reverse(path.begin(), path.end());
}
void addEdge(int u, int v){
	G[u].pb(eq), G[v].pb(eq);
	ars[eq++]=u^v;
}
