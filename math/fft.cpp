#include <bits/stdc++.h>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int,int> ii;

//~ typedef complex<double> base; //menos codigo, pero mas lento
//elegir si usar complejos de c (lento) o estos
struct base{
    double r,i;
    base(double r=0, double i=0):r(r), i(i){}
    double real()const{return r;}
    void operator/=(const int c){r/=c, i/=c;}
};
base operator*(const base &a, const base &b){
    return base(a.r*b.r-a.i*b.i, a.r*b.i+a.i*b.r);}
base operator+(const base &a, const base &b){
    return base(a.r+b.r, a.i+b.i);}
base operator-(const base &a, const base &b){
    return base(a.r-b.r, a.i-b.i);}
vector<int> rev; vector<base> wlen_pw;
inline static void fft(base a[], int n, bool invert) {
    forn(i, n) if(i<rev[i]) swap(a[i], a[rev[i]]);
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*M_PI/len * (invert?-1:+1);
		int len2 = len>>1;
		base wlen (cos(ang), sin(ang));
		wlen_pw[0] = base (1, 0);
        forr(i, 1, len2) wlen_pw[i] = wlen_pw[i-1] * wlen;
		for (int i=0; i<n; i+=len) {
			base t, *pu = a+i, *pv = a+i+len2,  *pu_end = a+i+len2, *pw = &wlen_pw[0];
			for (; pu!=pu_end; ++pu, ++pv, ++pw)
				t = *pv * *pw, *pv = *pu - t,*pu = *pu + t;
		}
	}
	if (invert) forn(i, n) a[i]/= n;}
inline static void calc_rev(int n){//precalculo: llamar antes de fft!!
    wlen_pw.resize(n), rev.resize(n);
    int lg=31-__builtin_clz(n);
    forn(i, n){
		rev[i] = 0;
        forn(k, lg) if(i&(1<<k)) rev[i]|=1<<(lg-1-k);
    }}
inline static void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res) {
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    int n=1; while(n < max(sz(a), sz(b))) n <<= 1; n <<= 1;
    calc_rev(n);
	fa.resize (n),  fb.resize (n);
	fft (&fa[0], n, false),  fft (&fb[0], n, false);
	forn(i, n) fa[i] = fa[i] * fb[i];
	fft (&fa[0], n, true);
	res.resize(n);
    forn(i, n) res[i] = int (fa[i].real() + 0.5); }
void toPoly(const string &s, vector<int> &P){//convierte un numero a polinomio
    P.clear();
    dforn(i, sz(s)) P.pb(s[i]-'0');}
