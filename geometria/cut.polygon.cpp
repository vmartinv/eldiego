//cuts polygon Q along the line ab
//stores the left side (swap a, b for the right one) in P
void cutPolygon(pto a, pto b, vector<pto> Q, vector<pto> &P){
	P.clear();
	forn(i, sz(Q)){
		double left1=(b-a)^(Q[i]-a), left2=(b-a)^(Q[(i+1)%sz(Q)]-a);
		if(left1>=0) P.pb(Q[i]);
		if(left1*left2<0)
			P.pb(inter(line(Q[i], Q[(i+1)%sz(Q)]), line(a, b)));
	}
}
