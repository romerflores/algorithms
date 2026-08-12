#include <bits/stdc++.h>
using namespace std;

struct StrHash {
    using ull = unsigned long long;

    static const ull MOD = (1ULL << 61) - 1;
    
    // Generación de base aleatoria segura
    static ull get_base() {
        static ull B = 0;
        if (B == 0) {
            mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
            B = rng() % (MOD - 300) + 256;
            if (B % 2 == 0) B++; // Es mejor que la base sea impar
        }
        return B;
    }

    vector<ull> h, p;

    // Multiplicación modular rápida O(1) sin %
    static inline ull mul(ull a, ull b) {
        unsigned __int128 prod = (unsigned __int128)a * b;
        ull r = (ull)(prod & MOD) + (ull)(prod >> 61);
        if (r >= MOD) r -= MOD;
        return r;
    }

    // Suma modular rápida
    static inline ull add(ull a, ull b) {
        ull res = a + b;
        if (res >= MOD) res -= MOD;
        return res;
    }

    // Resta modular rápida
    static inline ull sub(ull a, ull b) {
        ull res = a - b;
        if (a < b) res += MOD;
        return res;
    }

    StrHash(const string& s) {
        int n = s.size();
        h.resize(n + 1);
        p.resize(n + 1);
        p[0] = 1;
        
        ull B = get_base();

        for (int i = 0; i < n; i++) {
            h[i + 1] = add(mul(h[i], B), s[i]);
            p[i + 1] = mul(p[i], B);
        }
    }

    ull get(int l, int len) const {
        return sub(h[l + len], mul(h[l], p[len]));
    }
};