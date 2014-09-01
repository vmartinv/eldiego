bool operator< (const ii &a, const ii &b) {return a.fst<b.fst;}
//Stores intervals as [first, second]
//in case of a collision it joins them in a single interval
struct disjoint_intervals {
	set<ii> segs;
	void insert(ii v) {//O(lgn)
		if(v.snd-v.fst==0.) return;//OJO
		set<ii>::iterator it,at;
		at = it = segs.lower_bound(v);
		if (at!=segs.begin() && (--at)->snd >= v.fst)
			v.fst = at->fst, --it;
		for(; it!=segs.end() && it->fst <= v.snd; segs.erase(it++))
			v.snd=max(v.snd, it->snd);
		segs.insert(v);
	}
};
