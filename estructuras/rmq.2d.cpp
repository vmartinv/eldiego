struct RMQ2D{
	static const int sz=1024;
	RMQ t[sz];
	RMQ &operator[](int p){return t[sz/2+p];}
	void build(int n, int m){//O(nm)
		forr(y, sz/2, sz/2+m)
			t[y].build(m);
		forr(y, sz/2+m, sz)
			forn(x, sz)
				t[y].t[x]=0;
		dforn(y, sz/2)
			forn(x, sz)
				t[y].t[x]=max(t[y*2].t[x], t[y*2+1].t[x]);
	}
	void set(int x, int y, tipo v){//O(lgm.lgn)
		y+=sz/2;
		t[y].set(x, v);
		while(y/=2)
			t[y].set(x, max(t[y*2][x], t[y*2+1][x]));
	}
	//O(lgm.lgn)
	int get(int x1, int y1, int x2, int y2, int n=1, int a=0, int b=sz/2){
		if(y2<=a || y1>=b) return 0;
		if(y1<=a && b<=y2) return t[n].get(x1, x2);
		int c=(a+b)/2;
		return max(get(x1, y1, x2, y2, 2*n, a, c),
         get(x1, y1, x2, y2, 2*n+1, c, b));
	}
};
//Example to initialize a grid of M rows and N columns:
RMQ2D rmq;
forn(i, M)
	forn(j, N)
		cin >> rmq[i][j];
rmq.build(N, M);
