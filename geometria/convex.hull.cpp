//stores convex hull of P in S, CCW order
void CH(vector<pto>& P, vector<pto> &S){
	S.clear();
	sort(P.begin(), P.end());
	forn(i, sz(P)){//left must return >=0 to delete collinear points!
		while(sz(S)>= 2 && S[sz(S)-1].left(S[sz(S)-2], P[i])) S.pop_back();
		S.pb(P[i]);
	}
	S.pop_back();
	int k=sz(S);
	dforn(i, sz(P)){//left must return >=0 to delete collinear points!
		while(sz(S) >= k+2 && S[sz(S)-1].left(S[sz(S)-2], P[i])) S.pop_back();
		S.pb(P[i]);
	}
	S.pop_back();
}
