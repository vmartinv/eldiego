#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define fst first
#define snd second

#define pb push_back
typedef long long ll;
typedef pair<int,int> ii;

typedef double tipo;
typedef vector<tipo> Vec;
typedef vector<Vec> Mat;
#define eps 1e-10
#define feq(a, b) (fabs((a)-(b))<eps)

bool resolver_ev(Mat a, Vec y, Vec &x, Mat &ev){
	int n = a.size(), m = n?a[0].size():0, rw = min(n, m);
	vector<int> p; forn(i,m) p.push_back(i);
	forn(i, rw) {
		int uc=i, uf=i;
		forr(f, i, n) forr(c, i, m) if(fabs(a[f][c])>fabs(a[uf][uc])) {uf=f;uc=c;}
		if (feq(a[uf][uc], 0)) { rw = i; break; }
		forn(j, n) swap(a[j][i], a[j][uc]);
		swap(a[i], a[uf]); swap(y[i], y[uf]); swap(p[i], p[uc]);
		tipo inv = 1 / a[i][i]; //aca divide
		forr(j, i+1, n) {
			tipo v = a[j][i] * inv;
			forr(k, i, m) a[j][k]-=v * a[i][k];
			y[j] -= v*y[i];
		}
	} // rw = rango(a), aca la matriz esta triangulada
	forr(i, rw, n) if (!feq(y[i],0)) return false; // checkeo de compatibilidad
	x = vector<tipo>(m, 0);
	dforn(i, rw){
		tipo s = y[i];
		forr(j, i+1, rw) s -= a[i][j]*x[p[j]];
		x[p[i]] = s / a[i][i]; //aca divide
	}
	ev = Mat(m-rw, Vec(m, 0)); // Esta parte va SOLO si se necesita el ev
	forn(k, m-rw) {
		ev[k][p[k+rw]] = 1;
		dforn(i, rw){
			tipo s = -a[i][k+rw];
			forr(j, i+1, rw) s -= a[i][j]*ev[k][p[j]];
			ev[k][p[i]] = s / a[i][i]; //aca divide
		}
	}
	return true;
}


int n,m;

int main() {
	freopen("test", "r", stdin);
	while(cin >> n >> m){
		vector< vector<double > > A,Av;
		vector< double > b,x;
		
		A.resize(n); x.resize(n); b.resize(n); Av.resize(n);
		forn(i,n) {
			A[i].resize(m);
			Av[i].resize(m);
		}
		
		forn(i,n) forn(j,m) cin >> A[i][j];
		forn(i,n) cin >> b[i];
		
		resolver_ev(A,b,x,Av);
		
		forn(i,n) cout << " " << x[i];
		cout << endl;
		dprint("ev");
		forn(i,n) {
			forn(j,m) cout << Av[i][j]<< " ";
			cout << endl;
		}
	}
    return 0;
}
