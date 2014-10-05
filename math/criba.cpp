#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>
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

#define MAXP 80000	//no necesariamente primo
int criba[MAXP+1];
vector<int> primos;

void buscarprimos(){
	int sq=sqrt(MAXP)+2;
	forr(p, 2, sq) if(!criba[p]){
		for(int m=p*p; m<=MAXP; m+=p)//borro los multiplos de p
			if(!criba[m])criba[m]=p;
	}
}

int main() {
	freopen("primos", "w", stdout);
	buscarprimos();
	cout << '{';
	bool first=true;
	forall(it, primos){
		if(first) first=false;
		else cout << ',';
		cout << *it;
    }
    cout << "};\n";
    return 0;
}

