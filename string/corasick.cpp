#include<iostream>
#include<string>
#include<cstring>
#include<map>
using namespace std;
#define forn(i,n) for(int i=0; i<n; i++)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))

struct trie{
	map<char, trie> next;
	trie* tran[256];//transiciones del automata
	int idhoja, szhoja;//id de la hoja o 0 si no lo es
	//link lleva al sufijo mas largo, nxthoja lleva al mas largo pero que es hoja
	trie *padre, *link, *nxthoja;
	char pch;//caracter que conecta con padre
	trie(): tran(),  idhoja(), padre(), link() {}
	void insert(const string &s, int id=1, int p=0){//id>0!!!
		if(p<sz(s)){
			trie &ch=next[s[p]];
			tran[(int)s[p]]=&ch;
			ch.padre=this, ch.pch=s[p];
			ch.insert(s, id, p+1);
		}
		else idhoja=id, szhoja=sz(s);
	}
	trie* get_link() {
		if(!link){
			if(!padre) link=this;//es la raiz
			else if(!padre->padre) link=padre;//hijo de la raiz
			else link=padre->get_link()->get_tran(pch);
		}
		return link; }
	trie* get_tran(int c) {
		if(!tran[c]) tran[c] = !padre? this : this->get_link()->get_tran(c);
		return tran[c];	}
	trie *get_nxthoja(){
		if(!nxthoja) nxthoja = get_link()->idhoja? link : link->nxthoja;
		return nxthoja;	}
	void print(int p){
		if(idhoja) cout << "found " << idhoja << "  at position " << p-szhoja << endl;
		if(get_nxthoja()) get_nxthoja()->print(p); }
	void matching(const string &s, int p=0){
		print(p); if(p<sz(s)) get_tran(s[p])->matching(s, p+1);	}
}tri;


int main(){
	tri=trie();//clear
	tri.insert("ho", 1);
	tri.insert("hoho", 2);
	tri.insert("hola", 3);
	tri.matching("hohohola");
	return 0;
}
