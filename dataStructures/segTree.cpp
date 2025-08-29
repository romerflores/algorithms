#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Data
{
    ll cant = 0;
    Data() { cant = 1e18; }

    Data(ll c) { cant = c; }
};

struct SegTree
{
private:
    vector<Data> st;

public:
    int sz;
    Data merge(Data a, Data b)
    {
        return min(a.cant, b.cant);
    }
    void init(int n, vector<Data> v)
    {
        while (__builtin_popcount(n) != 1)
        {
            n++;
        }
        st.resize(2 * n, Data());
        sz = n; // solo n, NO 2*n
        for (int i = 0; i < (int)v.size(); i++)
        {
            st[n + i] = v[i];
        }

        for (int i = n - 1; i > 0; --i)
        {
            st[i] = merge(st[i << 1], st[(i << 1) + 1]);
        }
    }

    void updateTreeNode(int p, Data nuevoValor) // 0i pos
    {
        st[p + sz] = nuevoValor;
        p = p + sz;
        for (int i = p; i > 1; i >>= 1)
            st[i >> 1] = merge(st[i], st[i ^ 1]);
    }

    Data query(int nodo, int left_nodo, int right_nodo, int l_q, int r_q) //
    {
        // query(1,0,st.sz-1,l_q,r_q) tipo->[l_q,r_q]0i
        /*
         los indices de los nodos empieza desde 1;
         */
        if (l_q <= left_nodo && right_nodo <= r_q)
        {
            return st[nodo];
        }
        if (l_q > right_nodo || left_nodo > r_q)
        {
            return Data();
        }

        int mitad = (left_nodo + right_nodo) / 2; ///[l:r] --> [l:mitad] [mitad+1:r]
        return merge(query(nodo * 2, left_nodo, mitad, l_q, r_q), query(nodo * 2 + 1, mitad + 1, right_nodo, l_q, r_q));
    }
};
