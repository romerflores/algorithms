struct Sqrt
{
    vector<ll> vec;
    vector<ll> blocks;
    int sz;
    int szb;

    Sqrt(vector<ll> v,int n)
    {
        sz=n;
        szb=int(ceil(sqrt(n)));
        vec=v;
        blocks.assign(szb,0ll);
        for(int i=0;i<sz;i++)
        {
            blocks[i/szb]+=vec[i];
        }
    }

    ll q(int r)//[0,r)
    {
        ll ans=0;
        for(int i=0;i<r/szb;i++)
        {
            ans+=blocks[i];
        }
        for(int i=(r/szb)*szb;i<r;i++)
        {
            ans+=vec[i];
        }
        return ans;
    }

    ll rq(int l,int r)//[l,r]1i
    {
        return q(r)-q(l-1);
    }

    void update(int pos,ll v)//0i
    {
        blocks[pos/szb]-=vec[pos];
        vec[pos]=v;
        blocks[pos/szb]+=vec[pos];
    }
};
