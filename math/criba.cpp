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
#define dforsn(i,a,b) for(int i=(b)-1; i>=a; i--)
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
typedef long long ll;
typedef pair<int,int> ii;

#define MAXP 130000	//no necesariamente primo
int criba[MAXP+1];
vector<int> primos;

void buscarprimos(){
	forr(p, 2, MAXP+1) if(!criba[p]){
		primos.push_back(p);
		for(int m=2*p; m<=MAXP; m+=p)//borro los multiplos de p
			if(!criba[m])criba[m]=p;
	}
}

int main() {
	buscarprimos();
	forall(it, primos) cout << *it << endl;
    return 0;
}

