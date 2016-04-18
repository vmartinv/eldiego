bool isConvex(vector<int> &p){//O(N), delete collinear points!
	int N=sz(p);
	if(N<3) return false;
	bool isLeft=p[0].left(p[1], p[2]);
	forr(i, 1, N)
		if(p[i].left(p[(i+1)%N], p[(i+2)%N])!=isLeft)
			return false;
	return true; }
