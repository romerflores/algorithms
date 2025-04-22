#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

typedef long long ll;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forsn(i, s, n) for (int i = int(s); i < (int)(n); i++)

// rabin miller

ll potlog(ll a, ll b, const ll M)
{
    ll res = 1;
    while (b)
    {
        if (b % 2)
            res = (__int128(res) * a) % M;
        a = (__int128(a) * a) % M;
        b /= 2;
    }
    return res;
}

bool primo(ll n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    ll D = n - 1, S = 0;
    while (D % 2 == 0)
    {
        D /= 2;
        S++;
    }
    // n-1 = 2^S * D
    static const int STEPS = 16;
    forn(pasos, STEPS)
    {
        const ll A = 1 + rand() % (n - 1);
        ll M = potlog(A, D, n);
        if (M == 1 || M == (n - 1))
            goto next;
        forn(k, S - 1)
        {
            M = (__int128(M) * M) % n;
            if (M == (n - 1))
                goto next;
        }
        return false;
    next:;
    }
    return true;
}

// pollard's rho

ll mcd(ll a, ll b) { return (a == 0) ? b : mcd(b % a, a); }

ll factor(ll n)
{
    static ll A, B;
    A = 1 + rand() % (n - 1);
    B = 1 + rand() % (n - 1);
#define f(x) ((__int128(x) * (x + B)) % n + A)
    ll x = 2, y = 2, d = 1;
    while (d == 1 || d == -1)
    {
        x = f(x);
        y = f(f(y));
        d = mcd(x - y, n);
    }
    return abs(d);
}

map<ll, ll> fact;

void factorize(ll n)
{
    assert(n > 0);
    while (n > 1 && !primo(n))
    {
        ll f;
        do
        {
            f = factor(n);
        } while (f == n);
        n /= f;
        factorize(f);
        for (auto &it : fact)
            while (n % it.first == 0)
            {
                n /= it.first;
                it.second++;
            }
    }
    if (n > 1)
        fact[n]++;
}

int main()
{
    ll N;
    while (cin >> N && N)
    {
        fact.clear();
        factorize(N);
        for (const auto &it : fact)
            cout << it.first << "^" << it.second << " ";
        cout << endl;
    }
    return 0;
}
