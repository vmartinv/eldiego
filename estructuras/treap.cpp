#include <bits/stdc++.h>
using namespace std;

typedef int Key;

typedef struct node *pnode;
struct node{
    Key key;
    int prior, size;
    pnode l,r;
    node(Key key=0, int prior=0): key(key), prior(prior), size(1), l(0), r(0) {}
};
struct treap {
    pnode root;
    treap(): root(0) {}
    int size(pnode p) { return p ? p->size : 0; }
    int size() { return size(root); }
    void push(pnode p) {
        // modificar y propagar el dirty a los hijos aca(para lazy)
    }
    // Update function and size from children's values
    void pull(pnode p) {//recalcular valor del nodo aca (para rmq)
        p->size = 1 + size(p->l) + size(p->r);
    }  
    pnode merge(pnode l, pnode r) {
        if (!l || !r) return l ? l : r;
        push(l), push(r);
        pnode t;
        if (l->prior < r->prior) l->r=merge(l->r, r), t = l;
        else r->l=merge(l, r->l), t = r; 
        pull(t);
        return t;
    }//opcional:
    void merge(treap t) {root = merge(root, t.root), t.root=0;}
    //*****KEY OPERATIONS*****//
    void splitKey(pnode t, Key key, pnode &l, pnode &r) {
        if (!t) return void(l = r = 0);
        push(t);
        if (key <= t->key) splitKey(t->l, key, l, t->l), r = t;
        else splitKey(t->r, key, t->r, r), l = t;
        pull(t);
    }
    void insertKey(Key key) {
        pnode elem = new node(key, rand());
        pnode t1, t2; splitKey(root, key, t1, t2);
        t1=merge(t1,elem);
        root=merge(t1,t2);
    }
    void eraseKeys(Key key1, Key key2) {
        pnode t1,t2,t3;
        splitKey(root,key1,t1,t2);
        splitKey(t2,key2, t2, t3);
        root=merge(t1,t3);
    }
    void eraseKey(pnode &t, Key key) {
        if (!t) return;
        push(t);
        if (key == t->key) t=merge(t->l, t->r);
        else if (key < t->key) eraseKey(t->l, key);
        else eraseKey(t->r, key);
        pull(t);
    }
    void eraseKey(Key key) {eraseKey(root, key);}
    pnode findKey(pnode t, Key key) {
        if (!t) return 0;
        if (key == t->key) return t;
        if (key < t->key) return findKey(t->l, key);
        return findKey(t->r, key);
    }
    pnode findKey(Key key) { return findKey(root, key); }
    //*****POS OPERATIONS*****// No mezclar con las funciones Key
    //(No funciona con pos:)
    void splitSize(pnode t, int sz, pnode &l, pnode &r) {
        if (!t) return void(l = r = 0);
        push(t);
        if (sz <= size(t->l)) splitSize(t->l, sz, l, t->l), r = t; 
        else splitSize(t->r, sz - 1 - size(t->l), t->r, r), l = t; 
        pull(t);
    }
    void insertPos(int pos, Key key) {
        pnode elem = new node(key, rand());
        pnode t1,t2; splitSize(root, pos, t1, t2);
        t1=merge(t1,elem);
        root=merge(t1,t2);
    }
    void erasePos(int pos1, int pos2=-1) {
		if(pos2==-1) pos2=pos1+1;
        pnode t1,t2,t3;
        splitSize(root,pos1,t1,t2);
        splitSize(t2,pos2-pos1,t2,t3);
        root=merge(t1, t2);
    }
    pnode findPos(pnode t, int pos) {
        if(!t) return 0;
        if(pos <= size(t->l)) return findPos(t->l, pos);
        return findPos(t->r, pos - 1 - size(t->l));
    }
    Key &operator[](int pos){return findPos(root, pos)->key;}//ojito
};


ostream& operator<<(ostream &out, const pnode &t) {
	if(!t) return out;
    return out << t->l << t->key << ' ' << t->r;
}

int main(){
    treap t;
    int x;
    while(cin >> x) {
        if (x == 0) break;
        else if (x > 0) t.insertKey(x);
        else{
            x = -x;
            t.eraseKey(x);
        }
        cout << t.root << endl;
    }
    return 0;
}
