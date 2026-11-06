int query(int l, int r)
{
    int ans = INT_MIN;

    for(l += n, r += n; l <= r; l >>= 1, r >>= 1)
    {
        if(l & 1) ans = max(ans, st[l++]);
        if(!(r & 1)) ans = max(ans, st[r--]);
    }

    return ans;
}