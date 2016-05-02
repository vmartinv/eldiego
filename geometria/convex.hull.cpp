//stores convex hull of P in S, CCW order
//left must return >=0 to delete collinear points!
void CH(vector<pto>& P, vector<pto> &S){
	S.clear();
	sort(P.begin(), P.end());//first x, then y
	forn(i, sz(P)){//lower hull
		while(sz(S)>= 2 && S[sz(S)-1].left(S[sz(S)-2], P[i])) S.pop_back();
		S.pb(P[i]);
	}
	S.pop_back();
	int k=sz(S);
	dforn(i, sz(P)){//upper hull
		while(sz(S) >= k+2 && S[sz(S)-1].left(S[sz(S)-2], P[i])) S.pop_back();
		S.pb(P[i]);
	}
	S.pop_back();
}
