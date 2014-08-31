#include<iostream>
#include<string>
#include<cstring>
#include<map>
using namespace std;
#define forn(i,n) for(int i=0; i<n; i++)
#define sz(c) ((int)c.size())


struct trie{
	map<char, trie> next;
	trie* tran[256];
	int idhoja, szhoja;//id de la hoja o 0 si no lo es
	trie *padre;
	trie *link//lleva al sufijo mas largo
	trie *match;//lleva a la hoja mas larga que es sufijo
	char pch;//caracter que conecta con padre
	void add(const string &s, int id=1, int p=0){
		if(s[p]){
			trie &ch=next[s[p]];
			tran[(int)s[p]]=&ch;
			ch.padre=this, ch.pch=s[p];
			ch.add(s, id, p+1);
		}
		else idhoja=id, szhoja=sz(s);
	}
	trie* get_link() {
		if(!link){
			if(!padre) link=this;
			else if(!padre->padre) link=padre;
			else link=padre->get_link()->get_tran(pch);
		}
		return link;
	}
	trie* get_tran(int c) {
		if(!tran[c])
			tran[c] = !padre? this : this->get_link()->get_tran(c);
		return tran[c];
	}
	trie *get_match(){
		if(!match)
			match = get_link()->idhoja? link : link->match;
		return match;
	}
	void printocur(int p){
		if(idhoja){
			 cout << "found " << idhoja << "  at position " << p-szhoja+1 << endl;
		}
		if(get_match()) match->printocur(p);
	}
	void ocurrencias(const string &s, int p=0){
		printocur(p-1);
		if(s[p]) get_tran(s[p])->ocurrencias(s, p+1);
	}
}tri;


int main(){
	tri=trie();//clear
	tri.add("ho", 1);
	tri.add("hoho", 2);
	tri.add("hola", 3);
	tri.ocurrencias("hohohola");
	return 0;
}
