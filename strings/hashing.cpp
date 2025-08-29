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

//concate substrings(or strings) from non necesary two differents strings [idx,indx+lex)
ll concat_cross_hashes(const StrHash& A, int i1, int len1, const StrHash& B, int i2, int len2)
{
    ll res[2];
    for (int k = 0; k < 2; ++k)
    {
        // hash de substring A[i1..i1+len1-1]
        ll h1 = A.hs[k][i1 + len1] - A.hs[k][i1] * A.bs[k][len1] % A.ms[k];
        if (h1 < 0) h1 += A.ms[k];

        // hash de substring B[i2..i2+len2-1]
        ll h2 = B.hs[k][i2 + len2] - B.hs[k][i2] * B.bs[k][len2] % B.ms[k];
        if (h2 < 0) h2 += B.ms[k];

        // combinacion: h1 * b^len2 + h2
        res[k] = (h1 * A.bs[k][len2] + h2) % A.ms[k];
    }
    return (res[0] << 32) | res[1];
}


//0 indexed
ll h=StrHash("Hola").get(0,0+"Hola".size());
