#define MAX_N 1000
#define RABOUND(x) (x<n? RA[x] : 0)
//SA will hold the suffixes in order.
int SA[MAX_N], RA[MAX_N], n;
string s; //input string, n=sz(s)

void countingSort(int k){
	int f[MAX_N], tmpSA[MAX_N];
	zero(f);
	forn(i, n) f[RABOUND(i+k)]++;
	int sum=0;
	forn(i, max(255, n)){
		int t=f[i]; f[i]=sum; sum+=t;}
	forn(i, n)
		tmpSA[f[RABOUND(SA[i]+k)]++]=SA[i];
	memcpy(SA, tmpSA, sizeof(SA));
}
void constructSA(){//O(n log n)
	n=sz(s);
	forn(i, n) SA[i]=i, RA[i]=s[i];
	for(int k=1; k<n; k<<=1){
		countingSort(k), countingSort(0);
		int r, tmpRA[MAX_N];
		tmpRA[SA[0]]=r=0;
		forr(i, 1, n)
			tmpRA[SA[i]]=(RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k] )? r : ++r;
		memcpy(RA, tmpRA, sizeof(RA));
		if(RA[SA[n-1]]==n-1) break;
	}
}
void print(){//for debug
	forn(i, n)
		cout << i << ' ' <<
		s.substr(SA[i], s.find( '$', SA[i])-SA[i]) << endl;}


//returns (lowerbound, upperbound) of the search
ii stringMatching(string P){ //O(sz(P)lgn)
	int lo=0, hi=n-1, mid=lo;
	while(lo<hi){
		mid=(lo+hi)/2;
		int res=s.compare(SA[mid], sz(P), P);
		if(res>=0) hi=mid;
		else lo=mid+1;
	}
	if(s.compare(SA[lo], sz(P), P)!=0) return ii(-1, -1);
	ii ans; ans.fst=lo;
	lo=0, hi=n-1, mid;
	while(lo<hi){
		mid=(lo+hi)/2;
		int res=s.compare(SA[mid], sz(P), P);
		if(res>0) hi=mid;
		else lo=mid+1;
	}
	if(s.compare(SA[hi], sz(P), P)!=0) hi--;
	ans.snd=hi;
	return ans;
}

//Calculates the LCP between consecutives suffixes in the Suffix Array.
//LCP[i] is the length of the LCP between SA[i] and SA[i-1]
int LCP[MAX_N];
void computeLCP(){//O(n)
	int phi[MAX_N], PLCP[MAX_N];
	phi[SA[0]]=-1;
	forr(i, 1, n) phi[SA[i]]=SA[i-1];
	int L=0;
	forn(i, n){
		if(phi[i]==-1) {PLCP[i]=0; continue;}
		while(s[i+L]==s[phi[i]+L]) L++;
		PLCP[i]=L;
		L=max(L-1, 0);
	}
	forn(i, n) LCP[i]=PLCP[SA[i]];
}

