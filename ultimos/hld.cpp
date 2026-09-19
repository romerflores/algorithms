
const int MAXN=2e5;
vector<int> gf[MAXN];
int parent[MAXN],depth[MAXN],heavy[MAXN],head[MAXN],pos[MAXN];
int cur_pos;
const ll MOD=1000000007;
 
int n;

int dfs(int nodo)
{
    int size=1;
    int max_c_size=0;
    for(int &c:gf[nodo])
    {   
        if(c!=parent[nodo])
        {
            parent[c]=nodo;
            depth[c]=depth[nodo]+1;
 
            int c_size=dfs(c);
            size+=c_size;
 
            if(c_size>max_c_size)
            {
                max_c_size=c_size;
                heavy[nodo]=c;
            }
        }
    }
    return size;
}
 
void update_on_vertex(int a, int b, ll val)
{
    for(; head[a] != head[b]; b = parent[head[b]])
    {
        if(depth[head[a]] > depth[head[b]])
            swap(a,b);
 
        st.update(1,0,st.sz-1,pos[head[b]],pos[b],val);
    }
 
    if(depth[a] > depth[b])
        swap(a,b);
 
    st.update(1,0,st.sz-1,pos[a],pos[b],val);
}
 
ll query_on_vertex(int a, int b)
{
    ll res = 0;
 
    for(; head[a] != head[b]; b = parent[head[b]])
    {
        if(depth[head[a]] > depth[head[b]])
            swap(a,b);
 
        res = max(res , st.query(1,0,st.sz-1,pos[head[b]],pos[b]));
    }
 
    if(depth[a] > depth[b])
        swap(a,b);
 
    res = max(res , st.query(1,0,st.sz-1,pos[a],pos[b]));
    return res;
}
 
 
void decompose(int v,int h)
{
    head[v]=h;
    pos[v]=cur_pos++;
    if(heavy[v]!=-1)
    {
        decompose(heavy[v],h);
    }
    for(int &c:gf[v])
    {
        if(c!=parent[v] && c!=heavy[v])
        {
            decompose(c,c);
        }
    }
}
 
void init()
{
    // parent=vector<int>(n);
    // depth=vector<int>(n);
    // heavy=vector<int>(n);
    // head=vector<int>(n);
    // pos=vector<int>(n);
    for(int i=0;i<MAXN;i++)heavy[i]=-1;
    cur_pos=0;
 
    dfs(0);
    decompose(0,0);
}
 
 
void update(int a,int b, ll val)//es query y update a la vez
{
    for(;head[a]!=head[b];b=parent[head[b]])
    {
        if(depth[head[a]]>depth[head[b]])swap(a,b);
        // ll resdomer=st.query()
        st.update(1,0,st.sz-1,pos[head[b]],pos[b],val);
        // res=(res*resdomer)%MOD;
    }
 
    if(depth[a]>depth[b])swap(a,b);
 
    if(a != b)st.update(1,0,st.sz-1,pos[a]+1,pos[b],val);
}
 
 
ll query(int a,int b)//quety on edges
{
    ll res=0;
 
    for(;head[a]!=head[b];b=parent[head[b]])
    {
        if(depth[head[a]]>depth[head[b]])swap(a,b);
        // ll resdomer=st.query()
        ll redomer=st.query(1,0,st.sz-1,pos[head[b]],pos[b]);
        res=(res+redomer);
    }
 
    if(depth[a]>depth[b])swap(a,b);
 
 
    ll last_heavy_path_res=0;
    if(a != b)last_heavy_path_res=st.query(1,0,st.sz-1,pos[a]+1,pos[b]);
 
    // ll last_heavy_path_res=1;
    res=(res+last_heavy_path_res);
    return res;
}
 