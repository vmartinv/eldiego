#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
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
typedef int tipo;
const int MAXNODE=16;

const tipo NEUTRO=999;
struct node{
	tipo v;
	int l,r;
	node(tipo v=NEUTRO, int l=-1, int r=-1):v(v), l(l), r(r) {}
} nds[MAXNODE];
int qn;
int tset(int ni, int p, tipo v, int a, int b){
	node n=(ni==-1?node():nds[ni]);
	if(a+1 == b) return nds[qn]=node(v), qn++;
	int m = (a+b)>>1;
	if(p<m) n.l=tset(n.l, p, v, a, m);
	else n.r=tset(n.r, p, v, m, b);
	n.v=min(n.l==-1?NEUTRO:nds[n.l].v, n.r==-1?NEUTRO:nds[n.r].v);
	return nds[qn]=n, qn++;
}
tipo tget(int ni, int i, int j, int a, int b){
	if(ni==-1) return NEUTRO;
	node n=nds[ni];
    if(i==a && j==b) return n.v;
	int m=(a+b)/2;
	if(m>=j) return tget(n.l, i, j, a, m);
	else if(m<=i) return tget(n.r, i, j, m, b);
	return min(tget(n.l, i, m, a, m), tget(n.r, m, j, m, b));
}
int main() {
	//~ freopen("in", "r", stdin);
	int n=8, a,b; char c[10];
	int root=0;
	nds[root]=node();
	qn=0;
	while(scanf("%s %d %d", c, &a, &b)>0){
		if(tolower(c[0])=='s') root=tset(root, a, b, 0, n);
		else printf("%d\n", tget(root, a, b, 0, n));
	}
	return 0;
}
