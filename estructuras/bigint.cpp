#define BASEXP 6
#define BASE 1000000
#define LMAX 1000
struct bint{
    int l;
    tipo n[LMAX];
    bint(tipo x){
        l=0;
        forn(i, LMAX){
            n[i]=x%BASE;
            x/=BASE;
            l+=!!x||!i;
        }
    }
    bint(){THIS = bint(0);}
    bint(string x){
l=(x.size()-1)/BASEXP+1;
        fill(n, n+LMAX, 0);
        tipo r=1;
        forn(i, sz(x)){
            n[i / BASEXP] += r * (x[x.size()-1-i]-'0');
            r*=10; if(r==BASE)r=1;
        }
    }
    void out(){
		cout << n[l-1];
		dforn(i, l-1) printf("%6.6llu", n[i]);//6=BASEXP!
	}
	void invar(){
		fill(n+l, n+LMAX, 0);
		while(l>1 && !n[l-1]) l--;
	}
};
bint operator+(const bint&a, const bint&b){
	bint c;
    c.l = max(a.l, b.l);
    tipo q = 0;
    forn(i, c.l) q += a.n[i]+b.n[i], c.n[i]=q %BASE, q/=BASE;
    if(q) c.n[c.l++] = q;
    c.invar();
    return c;
}
pair<bint, bool> lresta(const bint& a, const bint& b)   // c = a - b
{
	bint c;
    c.l = max(a.l, b.l);
    tipo q = 0;
    forn(i, c.l) q += a.n[i]-b.n[i], c.n[i]=(q+BASE) %BASE, q=(q+BASE)/BASE-1;
    c.invar();
    return mkp(c, !q);
}
bint& operator-= (bint& a, const bint& b){return a=lresta(a, b).fst;}
bint operator- (const bint&a, const bint&b){return lresta(a, b).fst;}
bool operator< (const bint&a, const bint&b){return !lresta(a, b).snd;}
bool operator<= (const bint&a, const bint&b){return lresta(b, a).snd;}
bool operator==(const bint&a, const bint&b){return a <= b && b <= a;}
bint operator*(const bint&a, tipo b){
    bint c;
    tipo q = 0;
    forn(i, a.l) q += a.n[i]*b, c.n[i] = q %BASE, q/=BASE;
    c.l = a.l;
    while(q) c.n[c.l++] = q %BASE, q/=BASE;
    c.invar();
    return c;
}
bint operator*(const bint&a, const bint&b){
    bint c;
    c.l = a.l+b.l;
    fill(c.n, c.n+b.l, 0);
    forn(i, a.l){
        tipo q = 0;
        forn(j, b.l) q += a.n[i]*b.n[j]+c.n[i+j], c.n[i+j] = q %BASE, q/=BASE;
        c.n[i+b.l] = q;
    }
    c.invar();
    return c;
}
pair<bint, tipo> ldiv(const bint& a, tipo b){// c = a / b ; rm = a % b
bint c;
	tipo rm = 0;
dforn(i, a.l){
        		rm = rm * BASE + a.n[i];
        		c.n[i] = rm / b;
        		rm %= b;
    }
    c.l = a.l;
    c.invar();
    return mkp(c, rm);
}
bint operator/(const bint&a, tipo b){return ldiv(a, b).fst;}
tipo operator%(const bint&a, tipo b){return ldiv(a, b).snd;}
pair<bint, bint> ldiv(const bint& a, const bint& b){
	bint c;
    bint rm = 0;
    dforn(i, a.l){
        if (rm.l==1 && !rm.n[0])
            rm.n[0] = a.n[i];
        else{
            dforn(j, rm.l) rm.n[j+1] = rm.n[j];
            rm.n[0] = a.n[i];
            rm.l++;
        }
        tipo q = rm.n[b.l] * BASE + rm.n[b.l-1];
        tipo u = q / (b.n[b.l-1] + 1);
        tipo v = q /  b.n[b.l-1] + 1;
        while (u < v-1){
            tipo m = (u+v)/2;
            if (b*m <= rm) u = m;
            else v = m;
        }
        c.n[i]=u;
        rm-=b*u;
    }
	c.l=a.l;
    c.invar();
    return mkp(c, rm);
}
bint operator/(const bint&a, const bint&b){return ldiv(a, b).fst;}
bint operator%(const bint&a, const bint&b){return ldiv(a, b).snd;}
