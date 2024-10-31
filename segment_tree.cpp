#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> tree;  //creamos el arbol

ll f(int nodo, int left_nodo,int right_nodo, int l_q,int r_q)
{
    /*
     los indices de los nodos empieza desde 1;
     */
    if(l_q<=left_nodo && right_nodo<=r_q)
    {
        return tree[nodo];
    }
    if(l_q>right_nodo || left_nodo>r_q)
    {
        return 0;
    }

    int mitad=(left_nodo+right_nodo)/2; ///[l:r] --> [l:mitad] [mitad+1:r]
    return f(nodo*2,left_nodo,mitad,l_q,r_q)+f(nodo*2+1,mitad+1,right_nodo,l_q,r_q);

}


void update(int i;int v,int n) //actualizacion de tipo reemplazo
{
    tree[n+i]=v;
    for(int i=(n+i)/2;j>=1;j/=2)
    {
        tree[j]=tree[2*j]+tree[2*j+1];
    }
}


int main()
{
    int n,q; cin>>n>>q;
    vector<int> vec(n);
    for(int i=0;i<n;i++)cin>>vec[i];

    while(__builtin_popcount(n)!=1) //para hacer que n siempre sea potencia de 2, ej  14 -->16   17 -->32
    {
        vec.push_back(0);
        n++;
    }

    tree.resize(2*n); //siempre sera tamaño de 2*n

    /*
     para construir el arbol siempre empezaremos de [n:2*n)
     */
    for(int i=0;i<n;i++)
    {
        tree[n+i]=vec[i];
    }
    for(int i=n-1;i>=1;i--) //construimos a partir de los hijos hasta  el root
    {
        tree[i]=tree[2*i]+tree[(i*2)+1];
    }


    while(q--)
    {
        int type; cin>>type;
        if(type&1)
        {
            //actualizacion
            int i,v; cin>>i>>v;
            i--;
            update(i,v,n);
        }
        else
        {
            int l,r; cin>>l>>r;
            l--;r--;
            cout<<f(1,0,n-1,l,r)<<endl;
        }

    }


    return 0;
}
