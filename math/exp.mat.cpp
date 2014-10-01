struct M22{		   // |a b|
	double a,b,c,d;// |c d|
	M22 operator*(const M22 &p) const {
		return (M22){a*p.a+b*p.c, a*p.b+b*p.d, c*p.a+d*p.c,c*p.b+d*p.d};}
};
M22 operator^(const M22 &p, int n){
	if(!n) return (M22){1, 0, 0, 1};//identidad
	M22 q=p^(n/2); q=q*q;
	return n%2? p * q : q;}
