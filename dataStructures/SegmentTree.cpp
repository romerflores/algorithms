struct Node
{
    //constructor
    Node operator+(const Node &other)const
    {
        //merge
    }
};

struct SegmentTree
{
    int sz;
    vector<Node> st;
 
    SegmentTree(int n,vector<ll> &v)
    {
        if(__builtin_popcount(n)!=1)n=(1<<(31-__builtin_clz(n)+1));
        sz=n;
        st.assign(2*sz,Node());
        for(int i=0;i<(int)v.size();i++)
        {
            st[sz+i]=Node(v[i]);
        }
        for(int i=2*sz-1;i>=2;i-=2)
        {
            int p=i/2;
            st[p]=st[p*2]+st[p*2+1];//orden importanteeeeeee aaaaa media hora debuguenado mierda aaaaaaasex0000
        }
    }
 
    void update(ll num,int pos)//0i
    {
        st[sz+pos]=Node(num);
        pos+=sz;
        while(pos>1)
        {
            int par=pos/2;
            st[par]=st[2*par]+st[2*par+1];
            pos=par;
        }
    }
 
    Node query(int nodo,int l_n,int r_n,int l_q,int r_q)
    {
        //si tengo todo retorna todo
        if(l_q<=l_n and r_n<=r_q)return st[nodo];
        // si no tengo nada retorna neutro
        if(l_q>r_n or l_n>r_q)return Node();//neutro
        int m=(l_n+r_n)/2;
        return query(2*nodo,l_n,m,l_q,r_q)+query(2*nodo+1,m+1,r_n,l_q,r_q);
    }
 
    int first_ge(int nodo,int l_n,int r_n,ll num)
    {
        if(l_n==r_n)return l_n;
        int m=(l_n+r_n)/2;
        if(st[2*nodo].maxi>=num)return first_ge(nodo*2,l_n,m,num);
        else return first_ge(nodo*2+1,m+1,r_n,num);
    }
};
