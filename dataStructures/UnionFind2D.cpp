const int MAX=1000000+10;
vector<int> sz(MAX,1);
vector<int> par(MAX,-1);
int n,m;
 
int comp=0;
 
 
int id(int x,int y)
{
    return x*m+y;
}
 
int find(int v)
{
    if(v==par[v]) return v;
    return par[v]=find(par[v]);
}
 
int find(int x,int y)
{
    return find(id(x,y));
}
 
void unite(int x1,int y1,int x2,int y2)
{
    int a=find(x1,y1);
    int b=find(x2,y2);
 
    if(a!=b)
    {
        if(sz[a]<sz[b]) swap(a,b);
 
        par[b]=a;
        sz[a]+=sz[b];
    }
}
 
bool same(int x1,int y1,int x2,int y2)
{
    return find(x1,y1)==find(x2,y2);
}
 
int size(int x,int y)
{
    return sz[find(x,y)];
}