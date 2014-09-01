#define MAX_GR  20
struct poly {
	int p[MAX_GR];//guarda los coeficientes del polinomio
	poly(){zero(p);}
	int gr(){//calculates grade of the polynomial
		dforn(i,MAX_GR) if(p[i]) return i;
		return 0; }
	bool isnull() {return gr()==0 && !p[0];}
	poly operator+(poly b) {// - is analogous
		poly c=THIS;
		forn(i,MAX_GR) c.p[i]+=b.p[i];
		return c;
	}
	poly operator*(poly b) {
		poly c;
		forn(i,MAX_GR) forn(k,i+1) c.p[i]+=p[k]*b.p[i-k];
		return c;
	}
	int eval(int v) {
		int sum = 0;
		forn(i,MAX_GR) sum+=p[i]*pow(v,i);
		return sum;
	}
	//the following function generates the roots of the polynomial
//it can be easily modified to return float roots
	set<int> roots(){
		set<int> roots;
		int a0 = abs(p[0]), an = abs(p[gr()]);
		vector<int> ps,qs;
		forr(p,1,sqrt(a0)+1) if (a0%p==0) ps.pb(p),ps.pb(a0/p);
		forr(q,1,sqrt(an)+1) if (an%q==0) qs.pb(q),qs.pb(an/q);
		forall(pt,ps)
			forall(qt,qs) if ( (*pt) % (*qt)==0 ) {
				int root = abs((*pt) / (*qt));
				if (eval(root)==0) roots.insert(root);
			}
		return roots;
	}
};
//the following functions allows parsing an expression like
//34+150+4*45
//into a polynomial(el numero en funcion de la base)
#define LAST(s) (sz(s)? s[sz(s)-1] : 0)
#define POP(s) s.erase(--s.end());
poly D(string &s) {
	poly d;
	for(int i=0; isdigit(LAST(s)); i++) d.p[i]=LAST(s)-'0', POP(s);
	return d;}

poly T(string &s) {
	poly t=D(s);
	if (LAST(s)=='*'){POP(s); return T(s)*t;}
	return t;
}
//main function, call this to parse
poly E(string &s) {
	poly e=T(s);
	if (LAST(s)=='+'){POP(s); return E(s)+e;}
	return e;
}
