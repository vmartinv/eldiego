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
typedef long long ll;
typedef pair<int,int> ii;
typedef int tipo;

struct poly {
    vector<tipo> c;//guarda los coeficientes del polinomio
    poly(const vector<tipo> &c): c(c) {}
    poly() {}
	bool isnull() {return c.empty();}
    poly operator+(const poly &o) const {
        int m = sz(c), n = sz(o.c);
        vector<tipo> res(max(m,n));
        forn(i, m) res[i] += c[i];
        forn(i, n) res[i] += o.c[i];
        return poly(res);    }
    poly operator*(const tipo cons) const {
		vector<tipo> res(sz(c));
        forn(i, sz(c)) res[i]=c[i]*cons;
        return poly(res);    }
    poly operator*(const poly &o) const {
        int m = sz(c), n = sz(o.c);
        vector<tipo> res(m+n-1);
        forn(i, m) forn(j, n) res[i+j]+=c[i]*o.c[j];
        return poly(res);    }
	tipo eval(tipo v) {
		tipo sum = 0;
		dforn(i, sz(c)) sum=sum*v + c[i];
		return sum;	}
    //poly contains only a vector<int> c (the coeficients)
	//the following function generates the roots of the polynomial
//it can be easily modified to return float roots
	set<tipo> roots(){
		set<tipo> roots;
		tipo a0 = abs(c[0]), an = abs(c[sz(c)-1]);
		vector<tipo> ps,qs;
		forr(p,1,sqrt(a0)+1) if (a0%p==0) ps.pb(p),ps.pb(a0/p);
		forr(q,1,sqrt(an)+1) if (an%q==0) qs.pb(q),qs.pb(an/q);
		forall(pt,ps)
			forall(qt,qs) if ( (*pt) % (*qt)==0 ) {
				tipo root = abs((*pt) / (*qt));
				if (eval(root)==0) roots.insert(root);
			}
		return roots;	}
};
pair<poly,tipo> ruffini(const poly p, tipo r) {
	int n = sz(p.c) - 1 ;
	vector<tipo> b(n);
	b[n-1] = p.c[n];
	dforn(k,n-1) b[k] = p.c[k+1] + r*b[k+1];
	tipo resto = p.c[0] + r*b[0];
	poly result(b);
	return make_pair(result,resto);
}
poly interpolate(const vector<tipo>& x,const vector<tipo>& y) {
    poly A; A.c.pb(1);
    forn(i,sz(x)) { poly aux; aux.c.pb(-x[i]), aux.c.pb(1), A = A * aux; }
	poly S; S.c.pb(0);
	forn(i,sz(x)) { poly Li;
		Li = ruffini(A,x[i]).fst;
		Li = Li * (1.0 / Li.eval(x[i])); // here put a multiple of the coefficients instead of 1.0 to avoid using double
		S = S + Li * y[i];	}
	return S;
}

int  main(){ 
	return 0;
}
