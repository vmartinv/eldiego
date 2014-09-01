int N;
vector<int> G[1000000];
//V[i]=node number(if visited), L[i]= lowest V[i] reachable from i
int qV, V[1000000], L[1000000], P[1000000];
void dfs(int v, int f){
	L[v]=V[v]=++qV;
	forall(it, G[v])
		if(!V[*it]){
			dfs(*it, v);
			L[v] = min(L[v], L[*it]);
			P[v]+= L[*it]>=V[v];
		}
		else if(*it!=f)
			L[v]=min(L[v], V[*it]);
}
int cantart(){ //O(n)
	qV=0;
	zero(V), zero(P);
	dfs(1, 0); P[1]--;
	int q=0;
	forn(i, N) if(P[i]) q++;
return q;
}
