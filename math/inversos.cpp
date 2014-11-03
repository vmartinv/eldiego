#include<iostream>
#include<cassert>
using namespace std;
#define forr(i, a, b) for(int i=(a); i<(b); i++)
typedef long long ll;

#define MAXMOD 15485867
ll inv[MAXMOD];//inv[i]*i=1 mod MOD
void calc(int p){//O(p)
	inv[1]=1;
	forr(i, 2, p) inv[i]= p-((p/i)*inv[p%i])%p;
}
int inverso(int x){//O(log x)
	return expmod(x, eulerphi(MOD)-2);//si mod no es primo(sacar a mano)
	return expmod(x, MOD-2);//si mod es primo
}

int main(){
	calc(15485867);
	return 0;
}
