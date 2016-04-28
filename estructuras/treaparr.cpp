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
typedef long long ll;
typedef pair<int,int> ii;

typedef ii Value;//ii(profundidad, nodo)
typedef struct node *pnode;
struct node{
    Value val, mini;
    int dirty;
    int prior, size;
    pnode l,r,parent;
    node(Value val): val(val), mini(val), dirty(0), prior(rand()), size(1), l(0), r(0), parent(0) {}
};
static int size(pnode p) { return p ? p->size : 0; } 
void push(pnode p) {//propagar dirty a los hijos(aca para lazy)
	p->val.fst+=p->dirty;
	p->mini.fst+=p->dirty;
	if(p->l) p->l->dirty+=p->dirty;
	if(p->r) p->r->dirty+=p->dirty;
	p->dirty=0;
}
static Value mini(pnode p) { return p ? push(p), p->mini : ii(1e9, -1); } 
// Update function and size from children's Value
void pull(pnode p) {//recalcular valor del nodo aca (para rmq)
	p->size = 1 + size(p->l) + size(p->r);
	p->mini = min(min(p->val, mini(p->l)), mini(p->r));//operacion del rmq!
	p->parent=0;
	if(p->l) p->l->parent=p;
	if(p->r) p->r->parent=p;
}
//junta dos arreglos
pnode merge(pnode l, pnode r) {
	if (!l || !r) return l ? l : r;
	push(l), push(r);
	pnode t;
	if (l->prior < r->prior) l->r=merge(l->r, r), t = l;
	else r->l=merge(l, r->l), t = r; 
	pull(t);
	return t;
}
//parte el arreglo en dos, sz(l)==tam
void split(pnode t, int tam, pnode &l, pnode &r) {
	if (!t) return void(l = r = 0);
	push(t);
	if (tam <= size(t->l)) split(t->l, tam, l, t->l), r = t; 
	else split(t->r, tam - 1 - size(t->l), t->r, r), l = t; 
	pull(t);
}
pnode at(pnode t, int pos) {
	if(!t) exit(1);
	push(t);
	if(pos == size(t->l)) return t;
	if(pos < size(t->l)) return at(t->l, pos);
	return at(t->r, pos - 1 - size(t->l));
}
int getpos(pnode t){//inversa de at
	if(!t->parent) return size(t->l);
	if(t==t->parent->l) return getpos(t->parent)-size(t->r)-1;
	return getpos(t->parent)+size(t->l)+1;
}
void split(pnode t, int i, int j, pnode &l, pnode &m, pnode &r) {
	split(t, i, l, t), split(t, j-i, m, r);}
Value get(pnode &p, int i, int j){//like rmq
	pnode l,m,r;
    split(p, i, j, l, m, r);
    Value ret=mini(m);
    p=merge(l, merge(m, r));
    return ret;
}
void print(const pnode &t) {//for debugging
	if(!t) return;
    push(t);
    print(t->l);
    cout << t->val.fst << ' ';
    print(t->r);
}

//Sample program: C. LCA Online from Petrozavodsk Summer-2012. Petrozavodsk SU Contest
//Available at http://opentrains.snarknews.info/~ejudge
const int MAXN=300100;
int n;
pnode beg[MAXN], fin[MAXN];
pnode lista;
vector<int> G[MAXN];
void euler(int v, int L=0){
	fin[v]=beg[v]=new node(ii(L, v));
	lista=merge(lista, fin[v]);
	forall(it, G[v]){
		euler(*it, L+1);
		fin[v]=new node(ii(L, v));
		lista=merge(lista, fin[v]);
	}
}

int query(int u, int v){
	int pu=getpos(beg[u]), pv=getpos(beg[v]);
	if(pu>pv) return query(v, u);
	pnode l,m,r;
	split(lista, pu, pv+1, l, m, r);
	int ret=mini(m).snd;
	lista=merge(merge(l, m),r);
    return ret;
}

void change(int u, int nuparent){
	int b=getpos(beg[u]), e=getpos(fin[u]);
    int pnu=getpos(beg[nuparent]);
	int lv=get(lista, pnu, pnu+1).fst;
	pnode l,m,r;
	split(lista, b, e+1, l, m, r);
	m->dirty=-get(m, 0, 1).fst+lv+1;
	lista=merge(l, r);
	split(lista, getpos(fin[nuparent])+1, l, r);
	fin[nuparent]=new node(ii(lv, nuparent));
	lista=merge(merge(l, m), merge(fin[nuparent], r));
}

int main() {
    //~ freopen("f.in", "r", stdin);
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    ios::sync_with_stdio(0);
    while(cin >> n){
		zero(G);
		forn(i, n-1){
			int x; cin >>x; x--;
			G[x].pb(i+1);
		}
		lista=0;
		euler(0);
		int m; cin >> m;
		while(m--){
			char ty[10]; int u,v;
			cin >> ty >> u >> v; u--, v--;
			if(ty[0]=='Q')   cout << query(u, v)+1 << endl;
            else change(u, v);
		}
    }
    return 0;
}
