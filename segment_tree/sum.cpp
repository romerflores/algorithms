

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;

struct info
{
    ll num;
};

info merge(info a, info b)
{
    info res;
    res.num = a.num+b.num;
    return res;
}

vector<info> st;
int n;

void buildSt(vector<ll> vec)
{
    for (int i = 0; i < n; i++) // Añadimos las hojas
    {
        info a;
        a.num = vec[i];
        st[n + i] = a;
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
        info xd;
        xd.num = 0;
        return xd; // neutro
    }

    int mitad = (left_nodo + right_nodo) / 2; ///[l:r] --> [l:mitad] [mitad+1:r]
    return merge(query(nodo * 2, left_nodo, mitad, l_q, r_q), query(nodo * 2 + 1, mitad + 1, right_nodo, l_q, r_q));
}

int main()
{
    cin >> n;
    int Q;
    cin >> Q;
    vector<ll> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }

    while (__builtin_popcount(n) != 1)
    {
        vec.push_back(0); // introduce neutro;
        n++;
    }
    st.resize(2 * n);

    buildSt(vec); // construimos el st

   // los updates deben ser 0 indexed
    
    while(Q--)
    {
        int q;cin>>q;
        if(q==1){ //update, son 0 indexed

            int indi;cin>>indi;
            info val;cin>>val.num;
            updateTreeNode(indi,val);

        }
        else
        {
            int l,r;cin>>l>>r;
            //q(nodo inicio,rango inicio 0i,rango fin0i,q_inicio 0i,q_fin 0i)
            cout<<query(1,0,n-1,l,r-1).num<<endl;//la resta a l o r denpenda del input constrait

        }
    }



    

    return 0;
}