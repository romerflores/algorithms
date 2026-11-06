#include <bits/stdc++.h>

const int N = 1e5 + 1;

// adj_t is the transpose of adj
std::vector<int> adj[N], adj_t[N];
std::vector<int> order;
std::vector<int> vis(N), id(N);

// calculates the order in which nodes are processed
void dfs1(int v) {
	vis[v] = true;
	for (int u : adj[v]) {
		if (!vis[u]) { dfs1(u); }
	}
	order.push_back(v);
}

/*
 * traverse one SCC at a time and
 * assign component ID to all nodes in one SCC
 */
void dfs2(int x, int comp) {
	vis[x] = true;

	for (int u : adj_t[x]) {
		if (!vis[u]) { dfs2(u, comp); }
	}
	id[x] = comp;
}

int main() {
	int n, m;
	std::cin >> n >> m;

	for (int i = 1; i <= m; i++) {
		int u, v;
		std::cin >> u >> v;
		adj[u].push_back(v);
		adj_t[v].push_back(u);
	}

	vis.assign(N, false);

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) { dfs1(i); }
	}

	vis.assign(N, false);
	std::reverse(begin(order), end(order));
	int comps = 0;
	for (int v : order) {
		if (!vis[v]) {
			comps++;  // counter for SCC
			dfs2(v, comps);
		}
	}

	std::cout << comps << '\n';

	for (int i = 1; i <= n; i++) { std::cout << id[i] << " \n"[i == n]; }
}