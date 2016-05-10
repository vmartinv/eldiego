#include <bits/stdc++.h>
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
const int MAXN=100100;

vector<int> G[MAXN]; int n,m,p[MAXN],d[MAXN],d2[MAXN];
int bfs(int r, int *d) {
	queue<int> q;
	d[r]=0; q.push(r);
	int v;
	while(sz(q)) { v=q.front(); q.pop();
		forall(it,G[v]) if (d[*it]==-1)
			d[*it]=d[v]+1, p[*it]=v, q.push(*it);
	}
	return v;//ultimo nodo visitado
}
vector<int> diams; vector<ii> centros;
void diametros(){
	memset(d,-1,sizeof(d));
	memset(d2,-1,sizeof(d2));
	diams.clear(), centros.clear();
	forn(i, n) if(d[i]==-1){
		int v,c;
		c=v=bfs(bfs(i, d2), d);
		forn(_,d[v]/2) c=p[c];
		diams.pb(d[v]);
		if(d[v]&1) centros.pb(ii(c, p[c]));
		else centros.pb(ii(c, c));
	}
}

int main() {
	freopen("in", "r", stdin);
	while(cin >> n >> m){
		forn(i,m) { int a,b; cin >> a >> b; a--, b--;
			G[a].pb(b);
			G[b].pb(a);
		}
		diametros();
		cout << "Diametros: ";
		forall(it, diams) cout << *it << ' '; cout << endl;
		cout << "Centros:" << endl;
		forall(it, centros){
			cout << '\t';
			if(it->fst==it->snd) cout << it->fst+1 << endl;
			else cout << it->fst+1 << "-" << it->snd+1 << endl;
		}
		zero(G);
	}
	return 0;
}
