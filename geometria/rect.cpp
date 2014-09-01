struct rect{
	//lower-left and upper-right corners
	pto lw, up;
};
//returns if there's an intersection and stores it in r
bool inter(rect a, rect b, rect &r){
	r.lw=pto(max(a.lw.x, b.lw.x), max(a.lw.y, b.lw.y));
	r.up=pto(min(a.up.x, b.up.x), min(a.up.y, b.up.y));
//check case when only a edge is common
	return r.lw.x<r.up.x && r.lw.y<r.up.y;
}
