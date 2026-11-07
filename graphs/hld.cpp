const int MAXN = 2e5 + 5;

vector<int> gf[MAXN];

int parent[MAXN];
int depth[MAXN];
int heavy[MAXN];
int head[MAXN];
int pos[MAXN];

int cur_pos;
int n;

int dfs(int nodo)
{
    int size = 1;
    int max_c_size = 0;

    for(int c : gf[nodo])
    {
        if(c == parent[nodo])
            continue;

        parent[c] = nodo;
        depth[c] = depth[nodo] + 1;

        int c_size = dfs(c);
        size += c_size;

        if(c_size > max_c_size)
        {
            max_c_size = c_size;
            heavy[nodo] = c;
        }
    }

    return size;
}

void decompose(int nodo, int h)
{
    head[nodo] = h;
    pos[nodo] = cur_pos++;

    if(heavy[nodo] != -1)
        decompose(heavy[nodo], h);

    for(int c : gf[nodo])
    {
        if(c != parent[nodo] && c != heavy[nodo])
            decompose(c, c);
    }
}

void init(int root = 0)
{
    fill(heavy, heavy + n, -1);

    cur_pos = 0;
    parent[root] = -1;
    depth[root] = 0;

    dfs(root);
    decompose(root, root);
}

/* ==================== VERTICES ==================== */

void set_vertex(int nodo, ll val)
{
    st.update(
        1, 0, st.sz - 1,
        pos[nodo], pos[nodo],
        val
    );
}

void update_on_vertex(int a, int b, ll val)
{
    while(head[a] != head[b])
    {
        if(depth[head[a]] > depth[head[b]])
            swap(a, b);

        st.update(
            1, 0, st.sz - 1,
            pos[head[b]], pos[b],
            val
        );

        b = parent[head[b]];
    }

    if(depth[a] > depth[b])
        swap(a, b);

    st.update(
        1, 0, st.sz - 1,
        pos[a], pos[b],
        val
    );
}

ll query_on_vertex(int a, int b)
{
    ll res = 0;

    while(head[a] != head[b])
    {
        if(depth[head[a]] > depth[head[b]])
            swap(a, b);

        res = max(
            res,
            st.query(
                1, 0, st.sz - 1,
                pos[head[b]], pos[b]
            )
        );

        b = parent[head[b]];
    }

    if(depth[a] > depth[b])
        swap(a, b);

    res = max(
        res,
        st.query(
            1, 0, st.sz - 1,
            pos[a], pos[b]
        )
    );

    return res;
}

/* ==================== ARISTAS ==================== */

// La arista (u, v) se guarda en el nodo mas profundo.
void set_edge(int u, int v, ll val)
{
    if(parent[u] == v)
    {
        st.update(
            1, 0, st.sz - 1,
            pos[u], pos[u],
            val
        );
    }
    else if(parent[v] == u)
    {
        st.update(
            1, 0, st.sz - 1,
            pos[v], pos[v],
            val
        );
    }
}

void update_on_edge(int a, int b, ll val)
{
    while(head[a] != head[b])
    {
        if(depth[head[a]] > depth[head[b]])
            swap(a, b);

        st.update(
            1, 0, st.sz - 1,
            pos[head[b]], pos[b],
            val
        );

        b = parent[head[b]];
    }

    if(depth[a] > depth[b])
        swap(a, b);

    if(a != b)
    {
        st.update(
            1, 0, st.sz - 1,
            pos[a] + 1, pos[b],
            val
        );
    }
}

ll query_on_edge(int a, int b)
{
    ll res = 0;

    while(head[a] != head[b])
    {
        if(depth[head[a]] > depth[head[b]])
            swap(a, b);

        res += st.query(
            1, 0, st.sz - 1,
            pos[head[b]], pos[b]
        );

        b = parent[head[b]];
    }

    if(depth[a] > depth[b])
        swap(a, b);

    if(a != b)
    {
        res += st.query(
            1, 0, st.sz - 1,
            pos[a] + 1, pos[b]
        );
    }

    return res;
}