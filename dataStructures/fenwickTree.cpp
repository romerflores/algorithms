#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


struct Bit
{
    private:
        vector<ll> bit;
        int sz;
    public:
    
    Bit(int n){bit.resize(n+1,0);this->sz=n;}

    void init(vector<ll> vec)
    {
        for(int i=0;i<sz;i++)
        {
            update(i+1,vec[i]);
        }
    }

    void update(int p,ll val)//1i
    {
        while(p<=sz)
        {
            bit[p]+=val;
            p+=(p&(-p));
        }
    }
    ll query(int p)//[1,p]1i
    {
        ll ans=0;
        while(p>0)
        {
            ans+=bit[p];
            p-=(p&-p);
        }
        return ans;
    }

    ll rquery(ll left,ll right)//[l,r]1i
    {
        return query(right)-query(left-1);
    }
};
