struct mnum{
	static const tipo mod=12582917;
	tipo v;
	mnum(tipo v=0): v(v%mod) {}
	mnum operator+(mnum b){return v+b.v;}
	mnum operator-(mnum b){return v>=b.v? v-b.v : mod-b.v+v;}
	mnum operator*(mnum b){return v*b.v;}
	mnum operator^(int n){
		if(!n) return 1;
		return n%2? (*this)^(n/2)*(this) : (*this)^(n/2);}
};
