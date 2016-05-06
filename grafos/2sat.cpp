//We have a vertex representing a var and other for his negation.
//Every edge stored in G represents an implication. To add an equation of the form a||b, use addor(a, b)
//MAX=max cant var, n=cant var
#define addor(a, b) (G[neg(a)].pb(b), G[neg(b)].pb(a)) 
vector<int> G[MAX*2];
//idx[i]=index assigned in the dfs
//lw[i]=lowest index(closer from the root) reachable from i
int lw[MAX*2], idx[MAX*2], qidx;
stack<int> q;
int qcmp, cmp[MAX*2];
//verdad[cmp[i]]=valor de la variable i
bool verdad[MAX*2+1];

int neg(int x) { return x>=n? x-n : x+n;}
void tjn(int v){
	lw[v]=idx[v]=++qidx;
	q.push(v), cmp[v]=-2;
	forall(it, G[v]){
		if(!idx[*it] || cmp[*it]==-2){
			if(!idx[*it]) tjn(*it);
			lw[v]=min(lw[v], lw[*it]);
		}
	}
	if(lw[v]==idx[v]){
		int x;
		do{x=q.top(); q.pop(); cmp[x]=qcmp;}while(x!=v);
		verdad[qcmp]=(cmp[neg(v)]<0);
		qcmp++;
	}
}
//remember to CLEAR G!!!
bool satisf(){//O(n)
	memset(idx, 0, sizeof(idx)), qidx=0;
	memset(cmp, -1, sizeof(cmp)), qcmp=0;
	forn(i, n){
		if(!idx[i]) tjn(i);
		if(!idx[neg(i)]) tjn(neg(i));
	}
	forn(i, n) if(cmp[i]==cmp[neg(i)]) return false;
	return true;
}
