//checks if v is inside of P, using ray casting
//works with convex and concave.
//excludes boundaries, handle it separately using segment.inside()
bool inPolygon(pto v, vector<pto>& P) {
	bool c = false;
	forn(i, sz(P)){
		int j=(i+1)%sz(P);
		if((P[j].y>v.y) != (P[i].y > v.y) &&
	(v.x < (P[i].x - P[j].x) * (v.y-P[j].y) / (P[i].y - P[j].y) + P[j].x))
			c = !c;
	}
	return c;
}
