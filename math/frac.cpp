tipo mcd(tipo a, tipo b){return a?mcd(b%a, a):b;}
struct frac{
	tipo p,q;
	frac(tipo p=0, tipo q=1):p(p),q(q) {norm();}
	void norm(){
		tipo a = mcd(p,q);
		if(a) p/=a, q/=a;
		else q=1;
		if (q<0) q=-q, p=-p;}
	frac operator+(const frac& o){
		tipo a = mcd(q,o.q);
		return frac(p*(o.q/a)+o.p*(q/a), q*(o.q/a));}
	frac operator-(const frac& o){
		tipo a = mcd(q,o.q);
		return frac(p*(o.q/a)-o.p*(q/a), q*(o.q/a));}
	frac operator*(frac o){
		tipo a = mcd(q,o.p), b = mcd(o.q,p);
		return frac((p/b)*(o.p/a), (q/a)*(o.q/b));}
	frac operator/(frac o){
		tipo a = mcd(q,o.q), b = mcd(o.p,p);
		return frac((p/b)*(o.q/a),(q/a)*(o.p/b));}
	bool operator<(const frac &o) const{return p*o.q < o.p*q;}
	bool operator==(frac o){return p==o.p&&q==o.q;}
};
