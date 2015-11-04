#define SIZE 350
int NN;
void mul(double a[SIZE][SIZE], double b[SIZE][SIZE])
{
    double res[SIZE][SIZE] = {{0}};
    forn(i, NN) forn(j, NN) forn(k, NN) res[i][j]+=a[i][k]*b[k][j];
    forn(i, NN) forn(j, NN) a[i][j]=res[i][j];
}
void powmat(double a[SIZE][SIZE], int n, double res[SIZE][SIZE])
{
    forn(i, NN) forn(j, NN) res[i][j]=(i==j);
    while(n){
        if(n&1) mul(res, a), n--;
        else mul(a, a), n/=2;
    }
}

struct M22{		   // |a b|
	tipo a,b,c,d;// |c d|
	M22 operator*(const M22 &p) const {
		return (M22){a*p.a+b*p.c, a*p.b+b*p.d, c*p.a+d*p.c,c*p.b+d*p.d};}
};
M22 operator^(const M22 &p, int n){
	if(!n) return (M22){1, 0, 0, 1};//identidad
	M22 q=p^(n/2); q=q*q;
	return n%2? p * q : q;}

ll fibo(ll n){//calcula el fibonacci enesimo
	M22 mat=(M22){0, 1, 1, 1}^n;
	return mat.a*f0+mat.b*f1;//f0 y f1 son los valores iniciales
}
