vector<vector<int>> gf;  // lista de adyacencia
vector<int> visited;     // 0 = no visitado, 1 = visitando, 2 = visitado

bool dfs(int u) {
    visited[u] = 1; // visitando
    for (int v : gf[u]) {
        if (visited[v] == 1) return true;  // ciclo detectado
        if (visited[v] == 0 && dfs(v)) return true;
    }
    visited[u] = 2; // visitado
    return false;
}

bool isDAG(int n) {
    visited.assign(n, 0);
    for (int i = 0; i < n; i++)
        if (visited[i] == 0 && dfs(i))
            return false;  // hay ciclo
    return true; // no hay ciclos
}