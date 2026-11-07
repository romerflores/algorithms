#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 9;

struct SGTBeats {
    static constexpr ll INF = 1e18;

    int n, sz;
    ll mx[4 * N], smx[4 * N], cmx[4 * N];
    ll mn[4 * N], smn[4 * N], cmn[4 * N];
    ll sum[4 * N], len[4 * N];
    ll lazy_add[4 * N], lazy_set[4 * N];

    SGTBeats(int n, ll a[] = nullptr) : n(n), sz(1) {
        while(sz < n) sz <<= 1;

        fill(lazy_set, lazy_set + 2 * sz, INF);
        fill(lazy_add, lazy_add + 2 * sz, 0);

        len[0] = sz;

        for(int i = 0; i < sz - 1; i++)
            len[i * 2 + 1] = len[i * 2 + 2] = len[i] / 2;

        for(int i = 0; i < sz; i++) {
            int k = sz - 1 + i;

            if(i < n) {
                ll x = a ? a[i] : 0;

                mx[k] = mn[k] = sum[k] = x;
                smx[k] = -INF;
                smn[k] = INF;
                cmx[k] = cmn[k] = 1;
            } else {
                mx[k] = smx[k] = -INF;
                mn[k] = smn[k] = INF;
                sum[k] = cmx[k] = cmn[k] = 0;
            }
        }

        for(int i = sz - 2; i >= 0; i--)
            pull(i);
    }

    void apply_chmin(int k, ll x) {
        sum[k] += (x - mx[k]) * cmx[k];

        if(mx[k] == mn[k])
            mx[k] = mn[k] = x;
        else if(mx[k] == smn[k])
            mx[k] = smn[k] = x;
        else
            mx[k] = x;

        if(lazy_set[k] != INF)
            lazy_set[k] = min(lazy_set[k], x);
    }

    void apply_chmax(int k, ll x) {
        sum[k] += (x - mn[k]) * cmn[k];

        if(mx[k] == mn[k])
            mx[k] = mn[k] = x;
        else if(smx[k] == mn[k])
            mn[k] = smx[k] = x;
        else
            mn[k] = x;

        if(lazy_set[k] != INF)
            lazy_set[k] = max(lazy_set[k], x);
    }

    void apply_add(int k, ll x) {
        mx[k] += x;
        mn[k] += x;

        if(smx[k] != -INF) smx[k] += x;
        if(smn[k] != INF) smn[k] += x;

        sum[k] += len[k] * x;

        if(lazy_set[k] != INF)
            lazy_set[k] += x;
        else
            lazy_add[k] += x;
    }

    void apply_set(int k, ll x) {
        mx[k] = mn[k] = x;
        smx[k] = -INF;
        smn[k] = INF;
        cmx[k] = cmn[k] = len[k];
        sum[k] = x * len[k];
        lazy_set[k] = x;
        lazy_add[k] = 0;
    }

    void push(int k) {
        if(k >= sz - 1) return;

        int l = k * 2 + 1;
        int r = l + 1;

        if(lazy_set[k] != INF) {
            apply_set(l, lazy_set[k]);
            apply_set(r, lazy_set[k]);
            lazy_set[k] = INF;
            return;
        }

        if(lazy_add[k]) {
            apply_add(l, lazy_add[k]);
            apply_add(r, lazy_add[k]);
            lazy_add[k] = 0;
        }

        if(mx[l] > mx[k]) apply_chmin(l, mx[k]);
        if(mx[r] > mx[k]) apply_chmin(r, mx[k]);
        if(mn[l] < mn[k]) apply_chmax(l, mn[k]);
        if(mn[r] < mn[k]) apply_chmax(r, mn[k]);
    }

    void pull(int k) {
        int l = k * 2 + 1;
        int r = l + 1;

        sum[k] = sum[l] + sum[r];

        if(mx[l] == mx[r]) {
            mx[k] = mx[l];
            cmx[k] = cmx[l] + cmx[r];
            smx[k] = max(smx[l], smx[r]);
        } else if(mx[l] > mx[r]) {
            mx[k] = mx[l];
            cmx[k] = cmx[l];
            smx[k] = max(smx[l], mx[r]);
        } else {
            mx[k] = mx[r];
            cmx[k] = cmx[r];
            smx[k] = max(mx[l], smx[r]);
        }

        if(mn[l] == mn[r]) {
            mn[k] = mn[l];
            cmn[k] = cmn[l] + cmn[r];
            smn[k] = min(smn[l], smn[r]);
        } else if(mn[l] < mn[r]) {
            mn[k] = mn[l];
            cmn[k] = cmn[l];
            smn[k] = min(smn[l], mn[r]);
        } else {
            mn[k] = mn[r];
            cmn[k] = cmn[r];
            smn[k] = min(mn[l], smn[r]);
        }
    }

    void chmin(int a, int b, ll x, int k, int l, int r) {
        if(r <= a || b <= l || mx[k] <= x) return;

        if(a <= l && r <= b && smx[k] < x) {
            apply_chmin(k, x);
            return;
        }

        push(k);

        int m = (l + r) / 2;

        chmin(a, b, x, k * 2 + 1, l, m);
        chmin(a, b, x, k * 2 + 2, m, r);

        pull(k);
    }

    void chmax(int a, int b, ll x, int k, int l, int r) {
        if(r <= a || b <= l || x <= mn[k]) return;

        if(a <= l && r <= b && x < smn[k]) {
            apply_chmax(k, x);
            return;
        }

        push(k);

        int m = (l + r) / 2;

        chmax(a, b, x, k * 2 + 1, l, m);
        chmax(a, b, x, k * 2 + 2, m, r);

        pull(k);
    }

    void add(int a, int b, ll x, int k, int l, int r) {
        if(r <= a || b <= l) return;

        if(a <= l && r <= b) {
            apply_add(k, x);
            return;
        }

        push(k);

        int m = (l + r) / 2;

        add(a, b, x, k * 2 + 1, l, m);
        add(a, b, x, k * 2 + 2, m, r);

        pull(k);
    }

    void assign(int a, int b, ll x, int k, int l, int r) {
        if(r <= a || b <= l) return;

        if(a <= l && r <= b) {
            apply_set(k, x);
            return;
        }

        push(k);

        int m = (l + r) / 2;

        assign(a, b, x, k * 2 + 1, l, m);
        assign(a, b, x, k * 2 + 2, m, r);

        pull(k);
    }

    ll get_max(int a, int b, int k, int l, int r) {
        if(r <= a || b <= l) return -INF;
        if(a <= l && r <= b) return mx[k];

        push(k);

        int m = (l + r) / 2;

        return max(
            get_max(a, b, k * 2 + 1, l, m),
            get_max(a, b, k * 2 + 2, m, r)
        );
    }

    ll get_min(int a, int b, int k, int l, int r) {
        if(r <= a || b <= l) return INF;
        if(a <= l && r <= b) return mn[k];

        push(k);

        int m = (l + r) / 2;

        return min(
            get_min(a, b, k * 2 + 1, l, m),
            get_min(a, b, k * 2 + 2, m, r)
        );
    }

    ll get_sum(int a, int b, int k, int l, int r) {
        if(r <= a || b <= l) return 0;
        if(a <= l && r <= b) return sum[k];

        push(k);

        int m = (l + r) / 2;

        return get_sum(a, b, k * 2 + 1, l, m)
             + get_sum(a, b, k * 2 + 2, m, r);
    }

    void update_min(int l, int r, ll x) {
        chmin(l, r, x, 0, 0, sz);
    }

    void update_max(int l, int r, ll x) {
        chmax(l, r, x, 0, 0, sz);
    }

    void add_val(int l, int r, ll x) {
        add(l, r, x, 0, 0, sz);
    }

    void update_val(int l, int r, ll x) {
        assign(l, r, x, 0, 0, sz);
    }

    ll query_max(int l, int r) {
        return get_max(l, r, 0, 0, sz);
    }

    ll query_min(int l, int r) {
        return get_min(l, r, 0, 0, sz);
    }

    ll query_sum(int l, int r) {
        return get_sum(l, r, 0, 0, sz);
    }
};

ll a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for(int i = 0; i < n; i++)
        cin >> a[i];

    SGTBeats st(n, a);

    while(q--) {
        int type, l, r;
        cin >> type >> l >> r;

        if(type < 3) {
            ll x;
            cin >> x;

            if(type == 0) st.update_min(l, r, x);
            if(type == 1) st.update_max(l, r, x);
            if(type == 2) st.add_val(l, r, x);
        } else {
            cout << st.query_sum(l, r) << '\n';
        }
    }
}