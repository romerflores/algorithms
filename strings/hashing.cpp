struct StrHash
{ // Hash polinomial con exponentes decrecientes.
    static constexpr ll ms[] = {1'000'000'007, 1'000'000'403};
    static constexpr ll b = 500'000'000;
    vector<ll> hs[2], bs[2];
    StrHash(string const &s)
    {
        int n = s.length();
        for(int k=0;k<2;k++)
        {
            hs[k].resize(n + 1), bs[k].resize(n + 1, 1);
            for(int i=0;i<n;i++)
            {
                hs[k][i + 1] = (hs[k][i] * b + s[i]) % ms[k];
                bs[k][i + 1] = bs[k][i] * b % ms[k];
            }
        }
    }
    ll get(int idx, int len) const
    { // Hashes en `s[idx, idx+len)`.
        ll h[2];
        for(int k=0;k<2;k++)
        {
            h[k] = hs[k][idx + len] - hs[k][idx] * bs[k][len] % ms[k];
            if (h[k] < 0)
                h[k] += ms[k];
        }
        return (h[0] << 32) | h[1];
    }
};
//0 indexed
ll h=StrHash("Hola").get(0,"Hola".size());
