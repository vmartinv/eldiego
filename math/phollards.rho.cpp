#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)

typedef long long ll;

ll expmod (ll b, ll e, ll m){//O(log b)
	if(!e) return 1;
	ll q= expmod(b,e/2,m); q=(q*q)%m;
	return e%2? (b * q)%m : q;
}

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

bool es_primo_prob (ll n, int a)
{
	 if (n == a)
        return true;
	ll s = 0,d = n-1;
	while (d % 2 == 0) s++,d/=2;
	
	ll x = expmod(a,d,n);
	if ((x == 1) || (x+1 == n)) return true;
	
	forn (i, s-1){
		x = (x*x)%n;
		if (x == 1) return false;
		if (x+1 == n) return true;
	}
	return false;
}
		
bool miller_rabin (ll n){ //devuelve true si n es primo
	const int ar[] = {2,3,5,7,11,13,17,19,23};
	forn (j,9)
		if (!es_primo_prob(n,ar[j]))
			return false;
	return true;
}

ll pollard_rho (ll n){
	int i = 0, k = 2;
	ll x = 3, y = 3;
	while (1){
		i++;
		x = (mulmod (x,x,n) + n - 1) % n;
		ll d = gcd (abs(y-x), n);
		if(d==n) return -1;//FAILURE
		if (d != 1) return d;
		if (i == k) y = x, k*=2;
	}
}

int main(){
	ll n;
	srand(time(NULL));
	while(1){
		n=rand()%(ll(1e18))+50;
		dprint(n);
		if(!miller_rabin(n)){
			dprint(n);
			ll ans = pollard_rho (n);
			assert(!(n%ans) && ans>0);
		}
	}
	n = 2063512844981574047LL;
	while(cin >> n){
		if(miller_rabin (n))
			cout << n << " es primo.\n";
		else{
			ll ans = pollard_rho (n);
			if (ans > n / ans) ans = n / ans;
			printf ("%lld = %lld * %lld\n", n, ans, n / ans);
		}
    }
    return 0;
}
