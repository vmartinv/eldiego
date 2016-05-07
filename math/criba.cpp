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
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
typedef long long ll;
typedef pair<int,int> ii;

#define MAXP 100000	//no necesariamente primo
int criba[MAXP+1];
void crearcriba(){
	int w[] = {4,2,4,2,4,6,2,6};
	for(int p=25;p<=MAXP;p+=10) criba[p]=5;
	for(int p=9;p<=MAXP;p+=6) criba[p]=3; 
	for(int p=4;p<=MAXP;p+=2) criba[p]=2;
	for(int p=7,cur=0;p*p<=MAXP;p+=w[cur++&7]) if (!criba[p]) 
		for(int j=p*p;j<=MAXP;j+=(p<<1)) if(!criba[j]) criba[j]=p;
}
vector<int> primos;
void buscarprimos(){
	crearcriba();
	forr (i,2,MAXP+1) if (!criba[i]) primos.push_back(i);
}
//~ Useful for bit trick: #define SET(i) ( criba[(i)>>5]|=1<<((i)&31) ), #define INDEX(i) ( (criba[i>>5]>>((i)&31))&1 ), unsigned int criba[MAXP/32+1];


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

