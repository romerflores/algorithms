

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;

const ll NEG_INF = -1e15;

struct info
{
    ll sum;
    ll maxSuff;
    ll maxPreff;
    ll ans;
};

info make_data(ll num)
{
    info ret;
    ret.sum = num;
    ret.maxPreff = ret.maxSuff = ret.ans = max(0LL, num);  // <= permite segmento vacío
    return ret;
}

info merge(info a, info b)
{
    info ret;
    ret.sum = a.sum + b.sum;
    ret.maxPreff = max({a.maxPreff, a.sum + b.maxPreff});
    ret.maxSuff = max({b.maxSuff, b.sum + a.maxSuff});
    ret.ans = max({a.maxSuff + b.maxPreff, a.ans, b.ans});
    return ret;
}

info neutral()
{
    return {0, 0, 0, 0};
}

vector<info> st;
int n;

void buildSt(vector<ll> vec)
{
    for (int i = 0; i < n; i++) // Añadimos las hojas
    {
        if (vec[i] == NEG_INF)
        {
            st[n + i] = neutral();
        }
        else
        {
            info a = make_data(vec[i]);
            st[n + i] = a;
        }
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
    cin >> n;
    int tam = n;
    int Q;
    cin >> Q;
    vector<ll> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }

    while (__builtin_popcount(n) != 1)
    {
        vec.push_back(NEG_INF); // introduce neutro;
        n++;
    }
    st.resize(2 * n);

    buildSt(vec); // construimos el st

    for (int i = 1; i < 2 * n; i++)
    {
        if (__builtin_popcount(i) == 1)
            cout << endl;
        cout << st[i].sum << " ";
    }
    cout << endl;

    cout << query(1, 0, n - 1, 0, n - 1).ans << endl;

    while (Q--)
    {

        int indi;
        cin >> indi;
        int val;
        cin >> val;
        updateTreeNode(indi, make_data(val));
        for (int i = 1; i < 2 * n; i++)
        {
            if (__builtin_popcount(i) == 1)
                cout << endl;
            cout << st[i].ans << " ";
        }
        cout << endl;
        cout << st[1].ans << endl;
    }
    cout<<NEG_INF<<endl;

    return 0;
}