#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<map>
using namespace std;
#define forn(i,n) for(int i=0; i<n; i++)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define dprint(v) cout << #v"=" << (v) << endl //;)

void found(int id, int p);

// Teoria: https://cp-algorithms.com/string/aho_corasick.html
struct corasick{
	map<char, corasick> next;//trie, sirve para limpiar
	corasick* tran[256];//transiciones del automata
	int idhoja, szhoja;//id de la hoja o 0 si no lo es
	//link lleva al sufijo mas largo, linkhoja lleva al mas largo pero que es hoja (o a la raiz si no hay)
	corasick *padre, *link, *linkhoja;
	char pch;//caracter que conecta con padre
	corasick(): tran(),  idhoja(-1), padre(), link(), linkhoja() {}
	void insert(const string &s, int id, int p=0){//id>=0!!!
		if(p<sz(s)){
			corasick &ch=next[s[p]];
			tran[(int)s[p]]=&ch;
			ch.padre=this, ch.pch=s[p];
			ch.insert(s, id, p+1);
		}
		else idhoja=id, szhoja=sz(s);
	}
	corasick* get_link() {
		if(!link){
			if(!padre) link=this;//es la raiz
			else if(!padre->padre) link=padre;//hijo de la raiz
			else link=padre->get_link()->get_tran(pch);
		}
		return link; }
	corasick* get_tran(int c) {
		if(!tran[c]) tran[c] = !padre? this : this->get_link()->get_tran(c);
		return tran[c];	}
	corasick *get_linkhoja(){
		if(!linkhoja){
			if(get_link()->idhoja>=0) linkhoja = link;
			else if(!padre) linkhoja=this;//es la raiz
			else linkhoja=link->get_linkhoja();
		}
		return linkhoja; }
	void report(int p){
		if(idhoja>=0) cout << "found " << idhoja << " at position " << p-szhoja << endl;
		if(get_linkhoja()->idhoja>=0) linkhoja->report(p); }
	void matching(const string &s, int p=0){
		report(p); if(p<sz(s)) get_tran(s[p])->matching(s, p+1);	}
}cora;

void ejemplo(){
	cora=corasick();//clear
	cora.insert("ho", 1);
	cora.insert("hoho", 2);
	cora.insert("hola", 3);
	cora.matching("hohohola");
}

// Codigo para: http://codeforces.com/problemset/problem/963/D
// IMPORTANTE para testear prob. reemplazar 51 por esta linea en report:
// if(idhoja>=0) found(idhoja, p-szhoja);
// y comentar/descomentar 104/105 respectivamente.
const int MAXN=1e5+100;
string s;
int n;
int ks[MAXN];
int szq[MAXN];

vector<int> matches[MAXN];
void found(int id, int p){
	matches[id].push_back(p);
}

void solve_prob(){
	while(cin >> s >> n){
		cora=corasick();
		zero(matches);
		forn(i, n){
			string u; cin >> ks[i] >> u;
			szq[i]=sz(u);
			cora.insert(u, i);
		}
		cora.matching(s);
		forn(i, n){
			if(sz(matches[i])<ks[i]) cout << -1 << endl;
			else{
				int mn=sz(s);
				forn(j, sz(matches[i])-ks[i]+1){
					mn=min(mn, matches[i][j+ks[i]-1]+szq[i]-matches[i][j]);
				}
				cout << mn << endl;
			}
		}
	}
}

int main(){
	ejemplo();
	//~ solve_prob();
	return 0;
}
