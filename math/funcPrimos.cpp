//Testear!

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
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

#define MAXP 46341	//no necesariamente primo
int criba[MAXP+1];
vector<int> primos;

void buscarprimos(){
	forr(p, 2, MAXP+1) if(!criba[p]){
		primos.push_back(p);
		for(int m=2*p; m<=MAXP; m+=p)//borro los multiplos de p
			if(!criba[m])criba[m]=p;
	}
}

//factoriza bien numeros hasta (maximo primo)^2
map<ll,ll> fact(ll n){
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

ll numPrimeFactors (ll n)
{
  ll rta = 0;
  map<ll,ll> f=fact(n);
  forall(it, f) rta += it->second;
  return rta;
}

ll numDiffPrimeFactors (ll n)
{
  ll rta = 0;
  map<ll,ll> f=fact(n);
  forall(it, f) rta += 1;
  return rta;
}

ll sumPrimeFactors (ll n)
{
  ll rta = 0;
  map<ll,ll> f=fact(n);
  forall(it, f) rta += it->first;
  return rta;
}

ll numDiv (ll n)
{
  ll rta = 1;
  map<ll,ll> f=fact(n);
  forall(it, f) rta *= (it->second + 1);
  return rta;
}

ll sumDiv (ll n)
{
  ll rta = 1;
  map<ll,ll> f=fact(n);
  forall(it, f) rta *= ((ll)pow((double)it->first, it->second + 1.0)-1) / (it->first-1); 
  return rta;
}

ll eulerPhi (ll n)
{
  ll rta = n;
  map<ll,ll> f=fact(n);
  forall(it, f) rta -= rta / it->first;
  return rta;
}


int main() {
	buscarprimos();
	int x=24;
	cout << "x = " << x << endl;
  cout << "Numero de factores primos: " << numPrimeFactors(n) << endl;
  cout << "Numero de distintos factores primos: " << numDiffPrimeFactors(n) << endl;
  cout << "Suma de factores primos: " << sumPrimeFactors(n) << endl;
  cout << "Numero de divisores: " << numDiv(n) << endl;
  cout << "Suma de divisores: " << sumDiv(n) << endl;
  cout << "Phi de Euler: " << eulerPhi(n) << endl;
  return 0;
}
