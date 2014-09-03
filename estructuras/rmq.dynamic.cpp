//Dado un arreglo y una operacion asociativa con neutro, get(i, j) opera sobre el rango [i, j).
#define MAXN 100000
struct RMQ{
	int sz;
	tipo t[4*MAXN];
	tipo &operator[](int p){return t[sz+p];}
	void init(int n){//O(nlgn)
		sz = 1 << (32-__builtin_clz(n));
		fill(t, t+2*sz, 0); // 0=elemento neutro
	}
	void updall(){//O(n)
		dforsn(i, 0, sz) t[i]=max(t[2*i], t[2*i+1]);}
	tipo get(int i, int j){return get(i,j,1,0,sz);}
	tipo get(int i, int j, int n, int a, int b){//O(lgn)
		if(j<=a || i>=b) return 0;//neutro
		if(i<=a && b<=j) return t[n];
		int c=(a+b)/2;
		return max(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	void set(int p, tipo val){//O(lgn)
		for(p+=sz; p>0 && t[p]!=val;){
			t[p]=val;
			p/=2;
			val=max(t[p*2], t[p*2+1]);
		}
	}
}rmq;
//Usage:
cin >> n; rmq.init(n); forn(i, n) cin >> rmq[i]; rmq.updall();
