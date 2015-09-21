#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <cassert>
#include <unistd.h>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define fst first
#define snd second
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
    if (rabin(n))
        f3[n]++;
    else{
        ll aux = rho(n);
        fact3(aux); fact3(n/aux);        
    }
	if(n>1) f3[n]++;
	return;
}

//Usar asi:  divisores(fac, divs, fac.begin()); NO ESTA ORDENADO
void divisores(const map<ll,ll> &f, vector<ll> &divs, map<ll,ll>::iterator it, ll n=1){
    if(it==f.begin()) divs.clear();
    if(it==f.end()) {
        if(n>1) divs.pb(n);
        return;
    }
    ll p=it->fst, k=it->snd; ++it;
    forn(_, k+1)
        divisores(f, divs, it, n), n*=p;
}

int main() {
	buscarprimos();
	forr(x, 1, 400000){
		dprint(x);
		map<ll,ll> f=fact(x);
		map<ll,ll> f2=fact2(x);
		forall(it, f){
			assert(sz(f)==sz(f2));
			forall(it, f) assert(f2[it->first]==it->second);
		}
        //muestra divisores
        vector<ll> d;
        divisores(f, d, f.begin());
        forall(it, d) cout << *it << ' '; cout  << endl;
        sleep(1);
	}
    return 0;
}


