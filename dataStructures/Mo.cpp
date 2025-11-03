struct Query
{
    int l, r, idx;
    Query() {}
    Query(int lx, int rr, int ii)
    {
        l = lx;
        r = rr;
        idx = ii;
    }
};



inline void add(int i)
{
    //hacer algo
}

inline void remove(int i)
{
    //hacer algo
}

inline bool get_answer()
{
    return imp == 0;
}

inline vector<bool> Mo(vector<Query> &qs)
{
    const int szb = int(ceil(sqrt(N + .0)));
    sort(qs.begin(), qs.end(), [&](const Query &a, const Query &b)
    {
        if (a.l / szb == b.l / szb)
        {
            return ((a.l / szb) & 1) ? a.r < b.r : a.r > b.r;
        }
        return a.l < b.l; 
    });
    vector<bool> answers(Q);
    int c_l = 0, c_r = -1;
    for (auto &q : qs)
    {
        int ql = q.l;
        int qr = q.r;
        int qi = q.idx;
        while (c_l > ql)
        {
            c_l--;
            add(c_l);
        }
        while (c_r < qr)
        {
            c_r++;
            add(c_r);
        }
        while (c_l < ql)
        {
            remove(c_l);
            c_l++;
        }
        while (c_r > qr)
        {
            remove(c_r);
            c_r--;
        }
        answers[qi] = get_answer();
    }
    return answers;
}

int main()
{
    CRISTIANO_RONALDO_GANO_35_COPAS;

    int t;
    cin >> t;
    while (t--)
    {
        cin >> N >> Q;

        vec.assign(N, 0);
        
        for (int i = 0; i < N; i++)
            cin >> vec[i];

        vector<Query> qs(Q);
        for (int i = 0; i < Q; i++)
        {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            qs[i] = Query(l, r, i);
        }

        ans = 0;
        imp = 0;
        par = 0;
        vector<bool> ans = Mo(qs);

        for (int i = 0; i < Q; i++)
        {
            if (ans[i])
                cout << "YES\n";
            else
                cout << "NO\n";
        }
        // dbg(mp.size());
        for(int i=0;i<N;i++)mp[vec[i]]=0;
    }

    return 0;
}
