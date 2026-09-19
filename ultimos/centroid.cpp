#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN=1e5;
vector<int> gf[MAXN];
bool die[MAXN]={};
int ch[MAXN]={};
int n,q;

vector<int> min_dist(MAXN,1e9);

int get_sz_subTree(int nodo,int p)
{
    ch[nodo]=1;
    for(int &h:gf[nodo])
    {
        if(die[h] or h==p)continue;
        ch[nodo]+=get_sz_subTree(h,nodo);
    }
    return ch[nodo];
}

int get_centroid(int nodo,int p,int sz)
{
    for(int &h:gf[nodo])
    {
        if(die[h] or h==p)continue;
        if(ch[h]*2>sz)return get_centroid(h,nodo,sz);
    }
    return nodo;
}

vector<pair<int,int>> ancenstros[MAXN];

void get_dist(int nodo,int p,int lvl,int cent)
{
    ancenstros[nodo].push_back({cent,lvl});
    for(int &h:gf[nodo])
    {
        if(h!=p and !die[h])
        {
            get_dist(h,nodo,lvl+1,cent);
        }
    }
}

void sexo_decomposition(int nodo)
{
    int cent=get_centroid(nodo,-1,get_sz_subTree(nodo,-1));
    //algo

    for(int &h:gf[cent])
    {
        if(!die[h])
        {
            get_dist(h,cent,1,cent);
        }
    }


    die[cent]=1;
    for(int &h:gf[cent])if(!die[h])sexo_decomposition(h);    
}

void pintar(int nodo)
{
    for(auto &[ancestro,dis]:ancenstros[nodo])
    {
        min_dist[ancestro]=min(min_dist[ancestro],dis);
    }
    min_dist[nodo]=0;
}

int query(int nodo)
{
    int res=min_dist[nodo];

    for(auto [ancient,dist]:ancenstros[nodo])
    {
        res=min(res,dist+min_dist[ancient]);
    }
    return res;

}


int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n>>q;

    for(int i=0;i<n-1;i++)
    {
        int a,b;cin>>a>>b;
        a--;b--;
        gf[a].push_back(b);
        gf[b].push_back(a);
    }

    sexo_decomposition(0);

    pintar(0);

    while(q--)
    {
        int type;cin>>type;
        int v;cin>>v;v--;
        if(type&1)
        {
            pintar(v);
        }
        else
        {
            cout<<query(v)<<"\n";
        }
    }




    return 0;

}