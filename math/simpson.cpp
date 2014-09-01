double integral(double a, double b, int n=10000) {//O(n), n=cantdiv
	double area=0, h=(b-a)/n, fa=f(a), fb;
	forn(i, n){
		fb=f(a+h*(i+1));
		area+=fa+ 4*f(a+h*(i+0.5)) +fb, fa=fb;
	}
	return area*h/6.;}
