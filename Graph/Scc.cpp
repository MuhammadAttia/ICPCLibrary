void SccDfs(const Graph &g, int from, vector<int> &visit, vector<int> &st) {
  visit[from] = 1;
  for (Edges::const_iterator it = g[from].begin(); it != g[from].end(); it++) {
    if (visit[it->dest]) { continue; }
    SccDfs(g, it->dest, visit, st);
  }
  st.push_back(from);
}

vector<vector<int> > Scc(const Graph &g) {
  const int n = g.size();
  vector<vector<int> > ret;
  Graph revg(n);
  for (int i = 0; i < n; i++) {
    for (Edges::const_iterator it = g[i].begin(); it != g[i].end(); it++) {
      revg[it->dest].push_back(Edge(it->dest, i, it->weight));
    }
  }
  vector<int> st;
  vector<int> visit(n, 0);
  for (int i = 0; i < n; i++) {
    if (visit[i]) { continue; }
    SccDfs(g, i, visit, st);
  }
  visit = vector<int>(n, 0);
  for (int i = n - 1; i >= 0; i--) {
    int index = st[i];
    if (visit[index]) { continue; }
    vector<int> nret;
    SccDfs(revg, index, visit, nret);
    ret.push_back(nret);
  }
  return ret;
}

// select min weight edge
Graph SccGraph(const Graph &g) {
  vector<vector<int> > scc = Scc(g);
  const int n = g.size();
  const int m = scc.size();
  vector<int> mapto(n);
  for (int i = 0; i < (int)scc.size(); i++) {
    for (int j = 0; j < (int)scc[i].size(); j++) {
      mapto[scc[i][j]] = i;
    }
  }
  Graph ret(m);
  vector<int> indexs(m, -1);
  for (int from = 0; from < m; from++) {
    int e = 0;
    for (int i = 0; i < (int)scc[from].size(); i++) {
      for (Edges::const_iterator it = g[scc[from][i]].begin(); it != g[scc[from][i]].end(); it++) {
        int to = mapto[it->dest];
        if (from == to) { continue; } // loopback
        if (indexs[to] == -1) {
          ret[from].push_back(Edge(from, to, it->weight));
          indexs[to] = e++;
        } else {
          // select edge
          ret[from][indexs[to]].weight = min(ret[from][indexs[to]].weight, it->weight);
        }
      }
    }
    for (Edges::const_iterator it = ret[from].begin(); it != ret[from].end(); it++) {
      indexs[it->dest] = -1;
    }
  }
  return ret;
}
