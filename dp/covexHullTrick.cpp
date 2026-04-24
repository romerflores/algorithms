struct ConvexHull
{
    struct Ln
    {
        ll m,b;//m pendiente m1>m2>m3... b constante
    };
    
    vector<Ln> cht;
    bool tapa(Ln l1, Ln l2, Ln l3)//verifica si con al agregar la linea 3 la 2 se vuelve irrelevante
    {
        return (__int128)(l3.m-l2.m)*(l1.b-l3.b)>=(__int128)(l2.b-l3.b)*(l3.m-l1.m);
        //<= para maximos
    }
    void addLine(Ln nueva)
    {
        int sz=cht.size();
        while(cht.size()>1)
        {
            sz=cht.size();
            if(tapa(cht[sz-2],cht[sz-1],nueva))cht.pop_back();
            else break;
        }
        cht.push_back(nueva);
    }

    ll f(int p,ll x)
    {
        return cht[p].m*x+cht[p].b;
    }

    int query(ll x)//te da el indice de la mejor linea
    {
        int l = 0, r = cht.size() - 1;

        auto f = [&](int i)
        {
            return cht[i].m * x + cht[i].b;
        };

        while(l < r)
        {
            int mid = (l + r) / 2;
            //>= para maximos
            if(f(mid) <= f(mid + 1))r = mid;
            else l = mid + 1;
        }
        return l;
    }
};
