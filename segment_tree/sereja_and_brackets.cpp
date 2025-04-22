

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;

struct info
{
    int a, b, c;
};

info merge(info x, info y)
{
    info ret;
    int t = min(x.b, y.c);
    ret.a = x.a + y.a + t;
    ret.b = x.b + y.b - t;
    ret.c = x.c + y.c - t;
    return ret;
}

info make_info(char ch) {
    if (ch == '(')
        return {0, 1, 0};
    else
        return {0, 0, 1};
}
info neutral() {
    return {0, 0, 0};
}

vector<info> st;
int n;

void buildSt(vector<char> vec)
{
    for (int i = 0; i < n; i++) // Añadimos las hojas
    {
        st[n + i] = make_info(vec[i]);
    }
    for (int i = n - 1; i > 0; --i) // construmos los padres a partir de las hojas
    {
        st[i] = merge(st[i << 1], st[(i << 1) + 1]);
    }
}

void updateTreeNode(int p, info nuevoValor)
{
    // set value at position p
    st[p + n] = nuevoValor;
    p = p + n;

    // actualizar padres
    for (int i = p; i > 1; i >>= 1)
        st[i >> 1] = merge(st[i], st[i ^ 1]);
}

info query(int nodo, int left_nodo, int right_nodo, int l_q, int r_q)
{
    /*
     los indices de los nodos empieza desde 1;
     */
    if (l_q <= left_nodo && right_nodo <= r_q)
    {
        return st[nodo];
    }
    if (l_q > right_nodo || left_nodo > r_q)
    {
        return neutral();
    }

    int mitad = (left_nodo + right_nodo) / 2; ///[l:r] --> [l:mitad] [mitad+1:r]
    return merge(query(nodo * 2, left_nodo, mitad, l_q, r_q), query(nodo * 2 + 1, mitad + 1, right_nodo, l_q, r_q));
}

int main()
{
    string cad;
    cin >> cad;
    n = cad.length();
    int Q;
    cin >> Q;
    bitset<10> xd;
    vector<char> vec(n);
    for (int i = 0; i < n; i++)
    {
        vec[i] = cad[i];
    }

    while (__builtin_popcount(n) != 1)
    {
        vec.push_back(0); // introduce neutro;
        n++;
    }
    st.resize(2 * n);

    buildSt(vec); // construimos el st

    // los updates deben ser 0 indexed

    while (Q--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << query(1, 0, n - 1, l, r).a * 2 << endl;
    }

    return 0;
}