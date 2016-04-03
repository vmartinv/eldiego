void make_clockwise(vector<pto> &pt){
	if(pt[0].left(pt[1], pt[2])) reverse(pt.begin(), pt.end());}
int calc_lowest(const vector<pto> &pt){
	int pi=0;
	forn(i, sz(pt))
		if(pt[i].x<pt[pi].x || (pt[i].x==pt[pi].x && pt[i].y<pt[pi].y))
			pi=i;
	return pi;
}
bool inside(pto p, int lw, const vector<pto> &pt){ //lw=calc_lowest(pt)
	int n=sz(pt); //para no contar los bordes pto::left tiene que ser >=0
	if(p.left(pt[lw], pt[(lw+1)%n]) || p.left(pt[(lw+n-1)%n], pt[lw])) return false;
	int a=1, b=n-1;
	while(b-a>1){
		int c=(a+b)/2;
		if(!p.left(pt[lw], pt[(lw+c)%n])) a=c;
		else b=c;
	}
	return !p.left(pt[(lw+a)%n], pt[(lw+a+1)%n]);
}
