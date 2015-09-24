struct segm{
	pto s,f;
	segm(pto s, pto f):s(s), f(f) {}
	pto closest(pto p) {//use for dist to point
	   double l2 = dist_sq(s, f);
	   if(l2==0.) return s;
	   double t =((p-s)*(f-s))/l2/l2;
	   if (t<0.) return s;//not write if is a line
	   else if(t>1.)return f;//not write if is a line
	   return s+((f-s)*t);
	}
	bool inside(pto p){
return ((s-p)^(f-p))==0 && min(s, f)<*this&&*this<max(s, f);}
};

bool insidebox(pto a, pto b, pto p) {
	return (a.x-p.x)*(p.x-b.x)>-EPS && (a.y-p.y)*(p.y-b.y)>-EPS;
}
pto inter(segm s1, segm s2){
	pto r=inter(line(s1.s, s1.f), line(s2.s, s2.f));
	if(insidebox(s1.s,s1.f,p) && insidebox(s2.s,s2.f,p))
			return r;
	return pto(INF, INF);
}
