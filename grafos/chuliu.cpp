struct Ar{
    int src,dst,w;
};
typedef int weight ;
const weight inf=1e9;
typedef vector< vector< Ar > > graph;
void backward_traverse(int v, int s, int r,
graph &gg,
vector<int> &no, vector< vector<int> > &comp,
vector<int> &prev, vector< vector<int> > &next, vector<weight> &mcost,
vector<int> &mark, weight &cost, bool &found) {
    if (mark[v]) {
        vector<int> temp = no;
        found = true;
        do {
            cost += mcost[v];
            v = prev[v];
            if (v != s) {
                while (comp[v].size() > 0) {
                    no[comp[v].back()] = s;
                    comp[s].push_back(comp[v].back());
                    comp[v].pop_back();
                }
            }
        } while (v != s);
        
        for (int k = 0; k < sz(comp[s]); ++k) {
            int j = comp[s][k];
            if (j != r)
            for (int l = 0; l < sz(gg[j]); ++l)
            if (no[ gg[j][l].src ] != s)
            gg[j][l].w -= mcost[ temp[j] ];
        }
    }
    mark[v] = true;
    for (int k = 0; k < sz(next[v]); ++k) {
        int i = next[v][k];
        if (no[i] != no[v] && prev[ no[i] ] == v)
        if (!mark[ no[i] ] || i == s)
        backward_traverse(i, s, r, gg,
        no, comp, prev, next, mcost, mark, cost, found);
    }
}
weight minimum_spanning_arborescence(int r, graph &g) {
    const int n = g.size();
    graph gg(n);
    for (int i = 0; i < sz(g); ++i)
		for (int j = 0; j < sz(g[i]); ++j)
			gg[ g[i][j].dst ].push_back( g[i][j] );
    vector<int> no(n);
    vector< vector<int> > comp(n);
    for (int i = 0; i < n; ++i) {
        no[i] = i;
        comp[i].push_back(i);
    }
    weight cost = 0;
    while (1) {
        vector<int> prev(n, -1);
        vector<weight> mcost(n, inf);
        for (int j = 0; j < n; ++j) {
            if (j == r) continue;
            for (int k = 0; k < sz(gg[j]); ++k) {
                int i = gg[j][k].src;
                if (no[i] != no[j]) {
                    if (gg[j][k].w < mcost[ no[j] ]) {
                        mcost[ no[j] ] = gg[j][k].w;
                        prev[ no[j] ] = no[i];
                    }
                }
            }
        }
        vector< vector<int> > next(n);
        for (int i = 0; i < n; ++i)
        if (prev[i] >= 0)
        next[ prev[i] ].push_back( i );
        
        bool stop = true;
        vector<int> mark(n);
        for (int i = 0; i < n; ++i) {
            if (i == r || mark[i] || comp[i].size() == 0) continue;
            bool found = false;
            backward_traverse(i, i, r, gg,
            no, comp, prev, next, mcost, mark, cost, found);
            if (found) stop = false;
        }
        if (stop) {
            for (int i = 0; i < n; ++i)
              if (prev[i] >= 0)
                cost += mcost[i];
            return cost;
}}}
