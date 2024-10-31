/*
Este codigo realiza consultas del minimo y cantidad de minimos en un rango
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll infito_long = 9223372036854775806;
const int infinito_int=2147483647;

vector<pair<ll,ll>> tree;  //creamos el arbol

pair<ll,ll> f(int nodo, int left_nodo,int right_nodo, int l_q,int r_q)
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
        return {infinito_int,0};
    }

    int mitad=(left_nodo+right_nodo)/2; ///[l:r] --> [l:mitad] [mitad+1:r]

    pair<ll,ll> iz=f(nodo*2,left_nodo,mitad,l_q,r_q);
    pair<ll,ll> der=f(nodo*2+1,mitad+1,right_nodo,l_q,r_q);

    ll minimo=min(iz.first,der.first);

    if(iz.first==der.first)
    {
        return {minimo,iz.second+der.second};
    }
    else if(iz.first<der.first)
    {
        return {iz.first,iz.second};
    }
    else
    {
        return {der.first,der.second};
    }

}


void update(int i,ll v,int n) //actualizacion de tipo reemplazo
{
    tree[n+i]={v,1};
    for(int j=(n+i)/2;j>=1;j/=2)
    {
        //tree[j]=min(tree[2*j],tree[2*j+1]);

        ll cantidad_minimos=0;
        ll minimo=min(tree[2*j].first,tree[2*j+1].first);
        if(minimo==tree[2*j].first)
        {
            cantidad_minimos+=tree[2*j].second;
        }
        if(minimo==tree[2*j+1].first){
            cantidad_minimos+=tree[2*j+1].second;
        }
        tree[j]={minimo,cantidad_minimos};
    }
}


int main()
{
    int n,q; cin>>n>>q;
    vector<pair<ll,ll>> vec(n);
    for(int i=0;i<n;i++)
    {
        ll numero; cin>>numero;
        vec[i]={numero,1};
    }

    while(__builtin_popcount(n)!=1) //para hacer que n siempre sea potencia de 2, ej  14 -->16   17 -->32
    {
        vec.push_back({infinito_int,1});
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
        ll cantidad_minimos=0;
        ll minimo=min(tree[2*i].first,tree[2*i+1].first);
        if(minimo==tree[2*i].first)cantidad_minimos+=tree[2*i].second;
        if(minimo==tree[2*i+1].first)cantidad_minimos+=tree[2*i+1].second;
        tree[i]={minimo,cantidad_minimos};
    }


    while(q--)
    {



        int type; cin>>type;
        if(type&1)
        {
            //actualizacion
            int i; cin>>i;
            ll v; cin>>v;
            //i--;
            update(i,v,n);
        }
        else
        {
            int l,r; cin>>l>>r;
            //l--;
            r--;
            pair<ll,ll> res=f(1,0,n-1,l,r);
            cout<<res.first<<" "<<res.second<<endl;
        }


    }


    return 0;
}
