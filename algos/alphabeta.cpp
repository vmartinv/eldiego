ll alphabeta(State &s, bool player = true, int depth = 1e9, ll alpha = -INF, ll beta = INF) { //player = true -> Maximiza
    if(s.isFinal()) return s.score;
	//~ if (!depth) return s.heuristic();
    vector<State> children;
    s.expand(player, children);
    int n = children.size();
    forn(i, n) {
        ll v = alphabeta(children[i], !player, depth-1, alpha, beta);
        if(!player) alpha = max(alpha, v);
        else beta = min(beta, v);
        if(beta <= alpha) break;
    }
    return !player ? alpha : beta;}
