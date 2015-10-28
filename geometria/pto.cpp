const double EPS=1e-9;
struct pto{
	double x, y;
	pto(double x=0, double y=0):x(x),y(y){}
	pto operator+(pto a){return pto(x+a.x, y+a.y);}
	pto operator-(pto a){return pto(x-a.x, y-a.y);}
	pto operator+(double a){return pto(x+a, y+a);}
	pto operator*(double a){return pto(x*a, y*a);}
	pto operator/(double a){return pto(x/a, y/a);}
	//dot product, producto interno:
	double operator*(pto a){return x*a.x+y*a.y;}
	//module of the cross product or vectorial product:
	//if a is less than 180 clockwise from b, a^b>0
	double operator^(pto a){return x*a.y-y*a.x;}
	//returns true if this is at the left side of line qr
	bool left(pto q, pto r){return ((q-*this)^(r-*this))>0;}
	bool operator<(const pto &a) const{return x<a.x || (abs(x-a.x)<EPS && y<a.y);}
bool operator==(pto a){return abs(x-a.x)<EPS && abs(y-a.y)<EPS;}
	double norm(){return sqrt(x*x+y*y);}
	double norm_sq(){return x*x+y*y;}
};
double dist(pto a, pto b){return (b-a).norm();}
typedef pto vec;

double angle(pto a, pto o, pto b){
	pto oa=a-o, ob=b-o;
	return atan2(oa^ob, oa*ob);}

//rotate p by theta rads CCW w.r.t. origin (0,0)
pto rotate(pto p, double theta){
	return pto(p.x*cos(theta)-p.y*sin(theta),
     p.x*sin(theta)+p.y*cos(theta));
}

//orden total de puntos alrededor de un punto r
struct Cmp{
	pto r;
	Cmp(pto r):r(r) {}
	int cuad(const pto &a) const{
		if(a.x > 0 && a.y >= 0)return 0;
		if(a.x <= 0 && a.y > 0)return 1;
		if(a.x < 0 && a.y <= 0)return 2;
		if(a.x >= 0 && a.y < 0)return 3;
		assert(a.x ==0 && a.y==0);
		return -1;
	}
	bool cmp(const pto&p1, const pto&p2)const{
		int c1 = cuad(p1), c2 = cuad(p2);
		if(c1==c2) return p1.y*p2.x<p1.x*p2.y;
        else return c1 < c2;
	}
    bool operator()(const pto&p1, const pto&p2) const{
    return cmp(pto(p1.x-r.x,p1.y-r.y),pto(p2.x-r.x,p2.y-r.y));
    }
};



