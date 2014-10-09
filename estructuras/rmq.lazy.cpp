//Dado un arreglo y una operacion asociativa con neutro, get(i, j) opera sobre el rango [i, j).
#define MAXN 100000
typedef int tipo1;
typedef int tipo2;
const tipo1 neutro=0;
#define operacion(x,y) x+y
struct RMQ{
	int sz;
	tipo t[4*MAXN];
	tipo2 dirty[4*MAXN];//las alteraciones pueden ser de distinto tipo
	tipo &operator[](int p){return t[sz+p];}
	void init(int n){//O(nlgn)
		sz = 1 << (32-__builtin_clz(n));
		forr(i, sz, 2*sz) t[i]=neutro;
		forn(i, 2*sz) dirty[i]=0;
	}
	void modify(tipo2 v, int n){//altera un elemento y marca sucio sus hijos
		t[n]+=v;
		if(n<sz){
			dirty[2*n]+=v/2;
			dirty[2*n+1]+=v/2;
		}
	}
	void correct(int n){//corrige un elemento(sacandole lo dirty)
		if(dirty[n]){
			modify(dirty[n], n);
			dirty[n]=0;
		}
	}
	tipo get(int i, int j){return get(i,j,1,0,sz);}
	tipo get(int i, int j, int n, int a, int b){//O(lgn)
		correct(n);//corrige el valor antes de usarlo
		if(j<=a || i>=b) return neutro;
		if(i<=a && b<=j) return t[n];
		int c=(a+b)/2;
		return operacion(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	//altera los valores en [i, j) con una alteracion de val
	void set(tipo2 val, int i, int j){set(val,i,j,1,0,sz);}
	void set(tipo2 val, int i, int j, int n, int a, int b){//O(lgn)
		correct(n);
		if(j<=a || i>=b) return;
		if(i<=a && b<=j){
			modify((b-a)*val, n);
			return;
		}
		int c=(a+b)/2;
		set(val, i, j, 2*n, a, c), set(val, i, j, 2*n+1, c, b);
		t[n]=operacion(t[2*n], t[2*n+1]);
	}
}rmq;
