struct bitrie{
	static const int sz=1<<5;//5=ceil(log(n))
	int V;//valor del nodo
	vector<bitrie> ch;//childs
	bitrie():V(0){}//NEUTRO
	void set(int p, int v, int bit=sz>>1){//O(log sz)
		if(bit){
			ch.resize(2);
			ch[(p&bit)>0].set(p, v, bit>>1);
			V=max(ch[0].V, ch[1].V);
		}
		else V=v;
	}
	int get(int i, int j, int a=0, int b=sz){//O(log sz)
		if(j<=a || i>=b) return 0;//NEUTRO
		if(i<=a && b<=j) return V;
		if(!sz(ch)) return V;
		int c=(a+b)/2;
		return max(ch[0].get(i, j, a, c), ch[1].get(i, j, c, b));
	}
};
