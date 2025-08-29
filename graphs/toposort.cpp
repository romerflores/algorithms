#include <bits/stdc++.h>
using namespace std;
int n; // number of vertices
vector<vector<int>> gf;
vector<bool> vis;
vector<int> ans;

void dfs(int v) {//0i
    vis[v] = true;
    for (int u : gf[v]) {
        if (!vis[u]) {
            dfs(u);
        }
    }
    ans.push_back(v);
}

void topological_sort() {
    vis.assign(n, false);
    ans.clear();
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    reverse(ans.begin(), ans.end());
}