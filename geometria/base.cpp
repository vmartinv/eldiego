struct pto{
	tipo x, y;
	pto(tipo x=0, tipo y=0):x(x),y(y){}
	pto operator+(pto a){return pto(x+a.x, y+a.y);}
	pto operator-(pto a){return pto(x-a.x, y-a.y);}
	pto operator+(tipo a){return pto(x+a, y+a);}
	pto operator*(tipo a){return pto(x*a, y*a);}
	pto operator/(tipo a){return pto(x/a, y/a);}
	//dot product, producto interno:
	tipo operator*(pto a){return x*a.x+y*a.y;}
	//module of the cross product or vectorial product:
	//if a is less than 180 clockwise from b, a^b>0
	tipo operator^(pto a){return x*a.y-y*a.x;}
	//returns true if this is at the left side of line qr
	bool left(pto q, pto r){return ((q-*this)^(r-*this))>0;}
	bool operator<(const pto &a) const{return x<a.x || (abs(x-a.x)<EPS && y<a.y);}
bool operator==(pto a){return abs(x-a.x)<EPS && abs(y-a.y)<EPS;}
	double norm(){return sqrt(x*x+y*y);}
	tipo norm_sq(){return x*x+y*y;}
};
double dist(pto a, pto b){return (b-a).norm();}
typedef pto vec;

double angle(pto a, pto o, pto b){
	vec oa=a-o, ob=b-o;
	return acos((oa*ob) / sqrt(oa.norm_sq()*ob.norm_sq()));}

//rotate p by theta rads CCW w.r.t. origin (0,0)
pto rotate(pto p, double theta){
	return pto(p.x*cos(theta)-p.y*sin(theta),
     p.x*sin(theta)+p.y*cos(theta));
}


struct line{
	line() {}
	double a,b,c;//Ax+By=C
//pto MUST store float coordinates!
	line(double a, double b, double c):a(a),b(b),c(c){}
	line(pto p, pto q): a(q.y-p.y), b(p.x-q.x), c(a*p.x+b*p.y) {}
};
bool parallels(line l1, line l2){return abs(l1.a*l2.b-l2.a*l1.b)<EPS;}
pto inter(line l1, line l2){//intersection
	double det=l1.a*l2.b-l2.a*l1.b;
	if(abs(det)<EPS) return pto(INF, INF);//parallels
	return pto(l2.b*l1.c-l1.b*l2.c, l1.a*l2.c-l2.a*l1.c)/det;
}


struct segm{
	pto s,f;
	segm(pto s, pto f):s(s), f(f) {}
	pto closest(pto p) {//use for dist to point
	   double l2 = dist_sq(s, f);
	   if(l2==0.) return s;
	   double t =((p-s)*(f-s))/l2;
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



struct rect{
	//lower-left and upper-right corners
	pto lw, up;
};
//returns if there's an intersection and stores it in r
bool inter(rect a, rect b, rect &r){
	r.lw=pto(max(a.lw.x, b.lw.x), max(a.lw.y, b.lw.y));
	r.up=pto(min(a.up.x, b.up.x), min(a.up.y, b.up.y));
//check case when only a edge is common
	return r.lw.x<r.up.x && r.lw.y<r.up.y;
}
