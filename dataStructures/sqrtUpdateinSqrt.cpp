#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Sqrt
{
    vector<ll> vec;
    vector<ll> blocks;
    int sz;
    int szb;

    Sqrt(vector<ll> v, int n)
    {
        sz = n;
        szb = int(ceil(sqrt(n)));
        vec = v;
        blocks.assign(szb, 1e18);
        for (int i = 0; i < sz; i++)
        {
            blocks[i / szb]=min(vec[i],blocks[i / szb]);
        }
    }

    ll rq(int l, int r) //[l,r]0i
    {
        ll ans=1e18;
        int c_l = l / szb, c_r = r / szb;
        if (c_l == c_r)
            for (int i = l; i <= r; i++)
                ans=min(ans,vec[i]);
        else
        {
            for (int i = l, end = (c_l + 1) * szb - 1; i <= end; i++)
                ans=min(ans,vec[i]);
            for (int i = c_l + 1; i <= c_r - 1; i++)
                ans=min(ans,blocks[i]);
            for (int i = c_r * szb; i <= r; i++)
                ans=min(ans,vec[i]);
        }
        return ans;
    }

    void update(int pos, ll v) // 0i
    {
        vec[pos] = v;
        ll ans=1e18;

        int ini=(pos/szb)*szb;
        for(int i=ini;i<min(ini+szb,sz);i++)
        {
            ans=min(ans,vec[i]);
        }
        blocks[pos/szb]=ans;
    }
};
