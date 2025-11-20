#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1'000'000'007;

struct Matrix {
    ll mat[2][2];
};

Matrix operator*(const Matrix &a, const Matrix &b){
    Matrix c{};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            __int128 tmp = 0;
            for (int k = 0; k < 2; k++)
                tmp += (__int128)a.mat[i][k] * b.mat[k][j];
            c.mat[i][j] = (ll)(tmp % MOD);
        }
    return c;
}

Matrix matpow(Matrix base, ll n) {
    Matrix ans{{ {1, 0}, {0, 1} }};
    while (n) {
        if (n & 1) ans = ans * base;
        base = base * base;
        n >>= 1;
    }
    return ans;
}

ll fib(ll n) {
    if (n == 0) return 0;
    Matrix base{{ {1,1}, {1,0} }};
    return matpow(base, n).mat[0][1];
}

int main(){
    ll n;
    cin >> n;
    cout << fib(n) << "\n";
}
