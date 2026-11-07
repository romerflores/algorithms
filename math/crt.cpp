using ll = long long;
using i128 = __int128_t;

ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

bool crt_merge(ll a, ll m, ll b, ll n, ll &res, ll &lcm) {
    ll x, y;
    ll g = ext_gcd(m, n, x, y);
    ll diff = b - a;

    if(diff % g != 0)
        return false;

    ll ng = n / g;
    ll k = (ll)((i128)(diff / g) * x % ng);
    k = mod(k, ng);

    i128 new_lcm = (i128)m / g * n;
    i128 new_res = (i128)a + (i128)m * k;

    lcm = (ll)new_lcm;
    res = (ll)(new_res % new_lcm);

    if(res < 0)
        res += lcm;

    return true;
}

bool crt(const vector<ll> &a, const vector<ll> &m, ll &res, ll &lcm) {
    res = 0;
    lcm = 1;

    for(int i = 0; i < (int)a.size(); i++) {
        if(m[i] <= 0)
            return false;

        ll next_res, next_lcm;

        if(!crt_merge(res, lcm, mod(a[i], m[i]), m[i],
                      next_res, next_lcm))
            return false;

        res = next_res;
        lcm = next_lcm;
    }

    return true;
}

int main() {
    vector<ll> a = {2, 3, 2};
    vector<ll> m = {3, 5, 7};

    ll res, lcm;

    if(crt(a, m, res, lcm))
        cout << res << ' ' << lcm << '\n';
    else
        cout << "No existe solucion\n";
}