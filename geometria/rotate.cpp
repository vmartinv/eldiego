//rotates matrix t 90 degrees clockwise
//using auxiliary matrix t2(faster)
void rotate(){
	forn(x, n) forn(y, n)
		t2[n-y-1][x]=t[x][y];
	memcpy(t, t2, sizeof(t));
}
