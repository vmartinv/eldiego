#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
#include <map>
#include <cmath>
#include <string>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
typedef long long ll;
typedef pair<int,int> ii;

#define MAXP 500000	//no necesariamente primo
int criba[MAXP+1];
vector<int> primos;
void buscarprimos(){
	int sq=sqrt(MAXP)+1;
	forr(p, 2, MAXP+1) if(!criba[p]){
		primos.push_back(p);
		if(p<=sq)
			for(int m=p*p; m<=MAXP; m+=p)//borro los multiplos de p
				if(!criba[m])criba[m]=p;
	}
}

//factoriza bien numeros hasta MAXP^2
map<ll,ll> fact(ll n){ //O (cant primos)
	map<ll,ll> ret;
	forall(p, primos){
		while(!(n%*p)){
			ret[*p]++;//divisor found
			n/=*p;
		}
	}
	if(n>1) ret[n]++;
	return ret;
}

//factoriza bien numeros hasta MAXP
map<ll,ll> fact2(ll n){ //O (lg n)
	map<ll,ll> ret;
	while (criba[n]){
		ret[criba[n]]++;
		n/=criba[n];
	}
	if(n>1) ret[n]++;
	return ret;
}

map<ll,ll> f3;
void fact3(ll n){ //O (lg n)^3. un solo numero
    if (n == 1) return;
    if (miller_rabin(n))
        f3[n]++;
    else{
        ll aux = pollard_rho(n);
        fac3(aux); fac3(n/aux);        
    }
	if(n>1) f3[n]++;
	return;
}

int main() {
	buscarprimos();
	int x=476928;
	//~ cout << x << " = ";
	forr(x, 1, 400000){
		dprint(x);
		map<ll,ll> f=fact(x);
		map<ll,ll> f2=fact2(x);
		forall(it, f){
			assert(sz(f)==sz(f2));
			forall(it, f) assert(f2[it->first]==it->second);
		}
	}
    return 0;
}


