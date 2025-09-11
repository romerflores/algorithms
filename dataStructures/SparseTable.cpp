struct SparseTable {
    int n;
    vector<int> log2;
    vector<vector<int>> st;

    SparseTable(const vector<int>& a) {
        n = a.size();
        log2.resize(n + 1);
        log2[1] = 0;
        for (int i = 2; i <= n; i++)
            log2[i] = log2[i/2] + 1;

        int k = log2[n] + 1;
        st.assign(n, vector<int>(k));

        for (int i = 0; i < n; i++) st[i][0] = a[i];

        for (int j = 1; j < k; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[i][j] = min(st[i][j-1], st[i + (1 << (j-1))][j-1]);
    }

    // Consulta de minimo en el rango [l, r]oi
    int query(int l, int r) {
        int j = log2[r - l + 1];
        return min(st[l][j], st[r - (1 << j) + 1][j]);
    }
};