forn(i, MAXN+1){//comb[i][k]=i tomados de a k
	comb[i][0]=comb[i][i]=1;
	forr(k, 1, i) comb[i][k]=(comb[i-1][k]+comb[i-1][k-1])%MOD;
}
ll lucas (ll n, ll k, int p){ //Calcula (n,k)%p teniendo comb[p][p] precalculado.
	ll aux = 1;
	while (n + k) aux = (aux * comb[n%p][k%p]) %p, n/=p, k/=p;
	return aux;
}


