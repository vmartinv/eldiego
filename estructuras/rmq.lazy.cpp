//Dado un arreglo y una operacion asociativa con neutro, get(i, j) opera sobre el rango [i, j).
typedef int tipo;//tipo de los elementos del arreglo
typedef int tipo2;//tipo de la alteracion
#define operacion(x,y) x+y
const tipo neutro=0; const tipo2 neutro2=0;
#define MAXN 100000
struct RMQ{
	int sz;
	tipo t[4*MAXN];
	tipo2 dirty[4*MAXN];//las alteraciones pueden ser de distinto tipo
	tipo &operator[](int p){return t[sz+p];}
	void init(int n){//O(nlgn)
		sz = 1 << (32-__builtin_clz(n));
		forr(i, sz, 2*sz) t[i]=neutro;
		forn(i, 2*sz) dirty[i]=neutro2;
	}
	tipo f(tipo v, tipo2 k){//la alteracion
		return v+k;}
	tipo2 acum(tipo2 k1, tipo2 k2){//acumula dos alteraciones
		return k1+k2;}
	tipo predict(tipo v, tipo2 k, int n){//sobre un arreglo de tamanio n
		return v+k*n;	}
		
	void modify(tipo2 v, int cant, int n){
		t[n]=predict(t[n], v, cant);//altera un nodo 
		if(n<sz){//y marca sucio sus hijos
			dirty[2*n  ]=acum(dirty[2*n  ], v);
			dirty[2*n+1]=acum(dirty[2*n+1], v);
		}
	}
	void correct(int cant, int n){
		modify(dirty[n], cant, n);
		dirty[n]=neutro2;}
	tipo get(int i, int j){return get(i,j,1,0,sz);}
	tipo get(int i, int j, int n, int a, int b){//O(lgn)
		correct(n, b-a);//corrige el valor antes de usarlo
		if(j<=a || i>=b) return neutro;
		if(i<=a && b<=j) return t[n];
		int c=(a+b)/2;
		return operacion(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	//altera los valores en [i, j) con una alteracion de val
	void set(tipo2 val, int i, int j){set(val,i,j,1,0,sz);}
	void set(tipo2 val, int i, int j, int n, int a, int b){//O(lgn)
		correct(n, b-a);
		if(j<=a || i>=b) return;
		if(i<=a && b<=j){
			modify(val, b-a, n);
			return;
		}
		int c=(a+b)/2;
		set(val, i, j, 2*n, a, c), set(val, i, j, 2*n+1, c, b);
		t[n]=operacion(t[2*n], t[2*n+1]);
	}
}rmq;
