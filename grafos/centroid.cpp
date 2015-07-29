#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <queue>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
#define dprint(v) cout << #v"=" << v << endl //;)
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
int n,szt[100100],letter[100100];
bool taken[100100];
vector<int> G[100100];

void calcsz(int v, int p) {
	szt[v] = 1;
	forall(it,G[v]) if (*it!=p && !taken[*it])
		calcsz(*it,v), szt[v]+=szt[*it];
}

void centroid(int v, int lvl=0, int tam=-1) {
	if(tam==-1)	calcsz(v, -1), tam=szt[v];
	forall(it, G[v]) if(!taken[*it] && szt[*it]>=tam/2)
		{szt[v]=0; centroid(*it, lvl, tam); return;}
	taken[v]=true;
	letter[v]=lvl;
	forall(it, G[v]) if(!taken[*it])
		centroid(*it, lvl+1, -1);
}


int main() {
	//~ freopen("9.in", "r", stdin);
	//~ freopen("9.out", "w", stdout);
	ios::sync_with_stdio(0);
	while(cin >> n){
		zero(G);
		forn(i, n-1){int a,b; cin >> a >> b; a--, b--;
			G[a].pb(b);
			G[b].pb(a);
		}
		zero(taken);
		centroid(0, 0);
		forn(i,n) cout << char(letter[i]+'A') << (i!=n-1?' ':'\n');
		
	}
	return 0;
}
