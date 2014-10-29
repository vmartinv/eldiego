#include <cmath>
#include <cstdio>
#include <cstdlib>
typedef long long ll;

ll gcd(ll a, ll b){return a?gcd(b %a, a):b;}

ll mulmod (ll a, ll b, ll c) { //returns (a*b)%c, and minimize overfloor
	ll x = 0, y = a%c;
	while (b > 0){
		if (b % 2 == 1) x = (x+y) % c;
		y = (y*2) % c;
		b /= 2;
	}
	return x % c;
}

ll pollard_rho (ll n){
	int i = 0, k = 2;
	ll x = 3, y = 3;
	while (1){
		i++;
		x = (mulmod (x,x,n) + n - 1) % n;
		ll d = gcd (abs(y-x), n);
		if (d != 1 && d != n) return d;
		if (i == k) y = x, k*=2;
	}
}

int main(){
	ll n = 2063512844981574047LL;
	ll ans = pollard_rho (n);
	if (ans > n / ans) ans = n / ans;
	printf ("%lld %lld\n", ans, n / ans);
    return 0;
}
