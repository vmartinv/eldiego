#include <bits/stdc++.h>
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


typedef int Value;
typedef struct node *pnode;
struct node{
    Value val;
    int prior, size;
    pnode l,r;
    node(Value val=0): val(val), prior(rand()), size(1), l(0), r(0) {}
};
static int size(pnode p) { return p ? p->size : 0; } 
void push(pnode p) {
	// modificar y propagar el dirty a los hijos aca(para lazy)
}
// Update function and size from children's Value
void pull(pnode p) {//recalcular valor del nodo aca (para rmq)
	p->size = 1 + size(p->l) + size(p->r);
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
	if(pos == size(t->l)) return t;
	if(pos < size(t->l)) return at(t->l, pos);
	return at(t->r, pos - 1 - size(t->l));
}

ostream& operator<<(ostream &out, const pnode &t) {
	if(!t) return out;
    return out << t->l << t->val << ' ' << t->r;
}


struct arr {//para usar el treap como un arreglo
    pnode root;
    arr(Value val): root(new node(val)) {}
    arr(pnode root=0): root(root) {}
    void insert(int pos, Value val) {//agrega un elemento
        pnode t1,t2; ::split(root, pos, t1, t2);
        t1=merge(t1, new node(val));
        root=merge(t1,t2);
    }
    void erase(int i, int j=-1) {//borra un rango
		if(j==-1) j=i+1;
        pnode t1,t2,t3;
        ::split(root,i,t1,t2);
        ::split(t2,j-i,t2,t3);
        root=merge(t1, t3);
    }
    void push_back(Value val) {insert(size(root), val);}
    Value &operator[](int pos){return at(root, pos)->val;}//ojito
    //parte el arreglo en dos con sz(l)==tam
    void split(int tam, arr &l, arr &r){::split(root, tam, l.root, r.root);}
    //dado un rango, parte el arreglo en tres. m = rango [i, j)
    void split(int i, int j, arr &l, arr &m, arr &r){
		::split(root, i, l.root, m.root);
		::split(m.root, j-i, m.root, r.root);
	}
};
//concatena dos arreglos
arr merge(arr a, arr b){return arr(merge(a.root, b.root));}


int main(){
    arr t;
    int x;
    forn(_, 10) t.pb(rand()%10);
    cout << t.root << endl;
    while(cin >> x) {
        //~ if (x == 0) break;
        //~ else if (x > 0) t.pb(x);
        //~ else{
            //~ x = -x;
            //~ t.erase(x);
        //~ }
        
        //~ pnode q;
        int y; cin >> y;
        arr l, m, r;
        t.split(x, y, l, m, r);
        cout << l.root << endl;
        cout << m.root << endl;
        cout << r.root << endl;
        t=merge(l, m);
        t=merge(t, r);
        cout << t.root << endl;
    }
    return 0;
}
