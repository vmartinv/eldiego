struct trie{
	map<char, trie> m;
	void add(const string &s, int p=0){
		if(s[p]) m[s[p]].add(s, p+1);
	}
	void dfs(){
		//Do stuff
		forall(it, m)
			it->second.dfs();
	}
};
