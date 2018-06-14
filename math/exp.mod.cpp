#define MOD 1000000007
ll expmod (ll b, ll e, ll m){//O(log e)
	if(!e) return 1;
	ll q= expmod(b,e/2,m); q=(q*q)%m;
	return e%2? (b * q)%m : q;
}
