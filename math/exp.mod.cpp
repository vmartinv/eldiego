#define MOD 1000000007
int expmod (int b, int e){//O(log b)
	if(!e) return 1;
	ll q= expmod(b,e/2); q=(q*q)%MOD;
	return e%2? (b * q)%MOD : q;
}
