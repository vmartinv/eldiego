vec perp(vec v){return vec(-v.y, v.x);}
line bisector(pto x, pto y){
	line l=line(x, y); pto m=(x+y)/2;
	return line(-l.b, l.a, -l.b*m.x+l.a*m.y);
}
struct Circle{
	pto o;
	double r;
//circle determined by three points, uses line
	Circle(pto x, pto y, pto z){
		o=inter(bisector(x, y), bisector(y, z));
		r=dist(o, x);
	}
	pair<pto, pto> ptosTang(pto p){
		pto m=(p+o)/2;
		tipo d=dist(o, m);
		tipo a=r*r/(2*d);
		tipo h=sqrt(r*r-a*a);
		pto m2=o+(m-o)*a/d;
		vec per=perp(m-o)/d;
		return mkp(m2-per*h, m2+per*h);
	}
};
//finds the center of the circle containing p1 and p2 with radius r
//as there may be two solutions swap p1, p2 to get the other
bool circle2PtsRad(pto p1, pto p2, double r, pto &c){
        double d2=(p1-p2).norm_sq(), det=r*r/d2-0.25;
        if(det<0) return false;
        c=(p1+p2)/2+perp(p2-p1)*sqrt(det);
        return true;
}
