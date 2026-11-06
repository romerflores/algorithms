//O(E*F)donde F flujo maximo

int dfs(int v, int t, int pushed) {
    if (v == t) return pushed;
    vis[v] = 1;

    for (auto &e : G[v]) {
        if (!vis[e.to] && e.cap > 0) {
            int f = dfs(e.to, t, min(pushed, e.cap));
            if (f) {
                e.cap -= f;
                G[e.to][e.rev].cap += f;
                return f;
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    while (true) {
        fill(vis.begin(), vis.end(), 0);
        int pushed = dfs(s, t, INF);
        if (!pushed) break;
        flow += pushed;
    }
    return flow;
}