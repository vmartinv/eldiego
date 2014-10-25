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

int main() {
	buscarprimos();
	int x=476928;
	cout << x << " = ";
	map<ll,ll> f=fact(x);
	forall(it, f) cout << it->first << '^' << it->second << " * ";
	cout << 1 << endl;
    return 0;
}

