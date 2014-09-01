//f[v][k] holds the 2^k father of v
//L[v] holds the level of v
int N, f[100001][20], L[100001];
void build(){//f[i][0] must be filled previously, O(nlgn)
	forn(k, 20-1) forn(i, N) f[i][k+1]=f[f[i][k]][k];}
	
#define lg(x) (31-__builtin_clz(x))//=floor(log2(x))

int climb(int a, int d){//O(lgn)
	if(!d) return a;
	dforn(i, lg(L[a])+1)
		if(1<<i<=d)
			a=f[a][i], d-=1<<i;
    return a;
}
int lca(int a, int b){//O(lgn)
	if(L[a]<L[b]) swap(a, b);
	a=climb(a, L[a]-L[b]);
	if(a==b) return a;
	dforn(i, lg(L[a])+1)
		if(f[a][i]!=f[b][i])
			a=f[a][i], b=f[b][i];
	return f[a][0];
}
