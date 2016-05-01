#include <bits/stdc++.h>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define fst first
#define snd second
#define mkp make_pair
typedef long long ll;
typedef pair<int,int> ii;

struct UnionFind{
	vector<int> f;//the array contains the parent of each node
	vector<pair<int&,int>> m;
	void init(int n){m.clear();f.clear(); f.insert(f.begin(), n, -1);}
	int comp(int x){return (f[x]==-1?x:assign(f[x],comp(f[x])));}//O(1)
	bool join(int i, int j) {
		bool con=comp(i)==comp(j);
		if(!con) assign(f[comp(i)],comp(j));
		return con;
	}
	int assign(int& l, int r) { m.emplace_back(l,l); return l=r; }
	int snapt() {return sz(m);}
	void rollback(int s) { 
		while (sz(m)>s) { auto lr = m.back(); lr.fst=lr.snd; m.pop_back(); } 
	}} uf;

#define MAXQ 100000
struct DynamicConnectivity {
	enum querytype { ADD, DEL, QUERY };
    struct query { 
		int type,u,v; 
		query(int type, int u, int v) : type(type), u(u), v(v) {}
	};
    int match[MAXQ];
    vector<query> q;
    UnionFind dsu;
    map<ii,int> last;
    map<ii,int> cante;
    vector<bool> res;
    

    void init(int n) {
        dsu.init(n);
        last.clear();
        res.clear();
        q.clear();
    }

    void add(int u, int v) {
        if (u > v) swap(u,v); 
        if (cante[mkp(u,v)]++) return;
        last[mkp(u,v)] = sz(q);
        match[sz(q)] = -1;
        q.pb(query(ADD,u,v));
    }

    void remove(int u, int v) {
        if (u > v) swap(u,v);
        if (!cante[mkp(u,v)]) return;
        if (--cante[mkp(u,v)]) return;
        int l = last[ii(u,v)];
        match[l] = sz(q);
        match[sz(q)] = l;
        q.pb(query(DEL,u,v));
    }

    void request(int u, int v) {
        match[sz(q)] = -1;
        q.pb(query(QUERY,u,v));
    }

    void process() {
        forn(i,sz(q)) if (q[i].type == ADD && match[i] == -1) match[i] = sz(q);
        if (sz(q)) go(0,sz(q));
    }

    void go(int l, int r) {
		
        if (l+1 == r) {
            if (q[l].type == QUERY) {
				//~ dprint(l); dprint(r);
				int snap = dsu.snapt();
				res.pb(dsu.comp(q[l].u)==dsu.comp(q[l].v));
				dsu.rollback(snap);
			}
            return;
        }
        int snap, m = (l+r) / 2;
        snap = dsu.snapt();
        forr(i,m,r) if (match[i] != -1 && match[i] < l) dsu.join(q[i].u, q[i].v);
        go(l,m);
        dsu.rollback(snap);

        snap = dsu.snapt();
        forr(i,l,m) if (match[i] != -1 && match[i] >= r) dsu.join(q[i].u, q[i].v);
        go(m,r);
        dsu.rollback(snap);
    }
}dc;
	

const int MAXN=100100;
int n,m;
multiset<int> G[MAXN];

void addEdge(int a, int b) {
	G[a].insert(b);
	G[b].insert(a);
}
void removeEdge(int a, int b) {
	G[a].erase(G[a].find(b));
	G[b].erase(G[b].find(a));
}
vector<int> nres;
bool vis[MAXN];
void dfs(int v) {
	vis[v]=true; 
	forall(it,G[v]) if (!vis[*it]) dfs(*it);
}
void request(int a, int b) {
	zero(vis);
	//~ cout << "asd:\n";
	//~ forall(it,G[a]) cout << *it << " "; cout << endl;
	//~ forall(it,G[b]) cout << *it << " "; cout << "a:\n";
	dfs(a);
	nres.pb(vis[b]);
}

int main() {
    freopen("in", "r", stdin);
    ios::sync_with_stdio(0);
    while(cin >> n >> m){
		dc.init(n);
		forn(i,m) { int a,b,t; cin >>t >> a >> b;
			
			if (t==0) dc.add(a,b);
			else if (t==1) dc.remove(a,b);
			else dc.request(a,b);
			
			if (t==0) addEdge(a,b);
			else if (t==1) removeEdge(a,b);
			else request(a,b);
			
		}
		
		dc.process();
		dprint(sz(dc.res));
		dprint(sz(nres));
		assert(sz(dc.res)==sz(nres));
		forn(i,sz(dc.res)) {
			cout << dc.res[i] << " " <<nres[i] << endl;
			 assert(dc.res[i]==nres[i]);
		 }
		 cout << endl;
		nres.clear();
		forn(i,n) G[i].clear();
    }
    return 0;
}
