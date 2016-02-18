int sq,n;//n=cantidad de elementos, sq=sqrt(n);
struct Qu{//queries
    //intervalos cerrado abiertos !!! importante!!
    int l, r, id;//qs[i].id=i (orden de impresion)
    ll ans;//respuesta de la querie
}qs[MAXN];
bool bymos(const Qu &a, const Qu &b){
    if(a.l/sq!=b.l/sq) return a.l<b.l;
	return (a.l/sq)&1? a.r<b.r : a.r>b.r;
}
void mos(){
    sort(qs, qs+t, bymos);
    int cl=0, cr=0; 
    forn(i, t){ //intervalos cerrado abiertos !!! importante!!
        Qu &q=qs[i];
        while(cl<q.l) remove(cl++);
        while(cl>q.l) add(--cl);
        while(cr<q.r) add(cr++);
        while(cr>q.r) remove(--cr);
        q.ans=ans;
    }
    sort(qs, qs+t, byid);
}
