//aca a la hora de aniadir un edge, debemos ya tener que a es el grupo 1 y b el grupo 2

struct Kuhn {
    int n, m;
    vector<vector<int>> adj;
    vector<int> mt, vis;

    Kuhn(int n, int m) : n(n), m(m) {
        adj.resize(n);
        mt.assign(m, -1);
        vis.assign(n, 0);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool dfs(int u) {
        if (vis[u]) return false;
        vis[u] = 1;

        for (int v : adj[u]) {
            if (mt[v] == -1 || dfs(mt[v])) {
                mt[v] = u;
                return true;
            }
        }

        return false;
    }

    int maximum_matching() {
        int ans = 0;

        for (int u = 0; u < n; ++u) {
            fill(vis.begin(), vis.end(), 0);
            ans += dfs(u);
        }

        return ans;
    }
};