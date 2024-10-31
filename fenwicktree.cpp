    #include <bits/stdc++.h>
    using namespace std;

    typedef long long ll;

    int n;
    vector<ll> ft;


    //updates

    void update(ll pos,ll val)
    {
        //pos++;
        while(pos<=n)
        {
            ft[pos]+=val;
            pos+=(pos&-pos);//se acarrea el bit menos significativo
        }
    }


    ll query(ll pos)
    {
        //pos++;
        ll res=0;
        while(pos>0)
        {
            res+=ft[pos];
            pos-=(pos&-pos);//se quita el bit menos significativo
        }
        return res;
    }



    int main()
    {

        cin>>n;
        int m; cin>>m;
        ft.resize(n+1);
        vector<ll> original(n+1);
        //construir;
        for(int i=1;i<=n;i++)
        {
            ll numero; cin>>numero;
            update(i,numero);
            original[i]=numero;
        }

        while(m--)
        {

            /*for(int i=0;i<=n;i++)
            {
                cout<<ft[i]<<" ";
            }
            cout<<endl;*/
            int caso; cin>>caso;
            if(caso&1)
            {
                //update
               int indice; ll nuevo_valor; cin>>indice>>nuevo_valor;
               indice++;
               ll valor=nuevo_valor-original[indice];
               original[indice]=nuevo_valor;
               //cout<<"v "<<valor<<endl;
               update(indice,valor);

            }
            else
            {
                //query siuuu
                int l,r; cin>>l>>r;
                ll ans=query(r)-query(l);
                cout<<ans<<endl;

            }
        }




        return 0;
    }
