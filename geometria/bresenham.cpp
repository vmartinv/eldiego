//plot a line approximation in a 2d map
void bresenham(pto a, pto b){
	pto d=b-a; d.x=abs(d.x), d.y=abs(d.y);
	pto s(a.x<b.x? 1: -1, a.y<b.y? 1: -1);
	int err=d.x-d.y;
	while(1){
		m[a.x][a.y]=1;//plot
		if(a==b) break;
		int e2=err;
		if(e2 >= 0) err-=2*d.y, a.x+=s.x; 
		if(e2 <= 0) err+= 2*d.x, a.y+= s.y;
	}
}
