#include <cstdio>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;
#define forn(i, n) for(int i=0; i<(n); i++)
#define forr(i, a, b) for(int i=a; i<(b); i++)
const int MAXN = 100100;
 

pair<int, int> sf[MAXN];
bool comp(int lhs, int rhs) {return sf[lhs] < sf[rhs];}
struct SuffixArray {
	//sa guarda los indices de los sufijos ordenados
    int sa[MAXN], r[MAXN];
    void init(const char *a, int n) {
        forn(i, n) r[i] = a[i];
        for(int m = 1; m < n; m <<= 1) {
			forn(i, n) sa[i]=i, sf[i] = make_pair(r[i], i+m<n? r[i+m]:-1);
            stable_sort(sa, sa+n, comp);
            r[sa[0]] = 0;
            forr(i, 1, n) r[sa[i]]= sf[sa[i]] != sf[sa[i - 1]] ? i : r[sa[i-1]];
        }
    }
} sa;

int main(){
	char in[MAXN];
	while(cin >> in){
		sa.init(in, strlen(in));
		forn(i, (int)strlen(in)) cout << '\t' << in+sa.sa[i] << '\n';
	}
	return 0;
}
