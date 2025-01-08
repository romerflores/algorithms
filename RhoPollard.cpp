#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

/*
    *Rho de Pollar, copiado de elsantodel90 siuu
 */


ll gcd(ll a,ll b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}

ll prodlog(ll A, ll B, ll n)
{
    ll ret=0;
    while(B!=0)
    {
        if(B%2 !=0) ret= (ret+A)%n;
        A=(2*A)%n;
        B/=2;
    }   
    return ret;
}

ll potlog(ll A, ll B, ll n)
{
    ll ret=1;
    while(B!=0)
    {
        if(B&1)ret= prodlog(ret,A,n);
        A=prodlog(A,A,n);
        B/=2;
    }
    return ret;
}

bool esprimo(ll n)
{
    if(n<2)return false;
    if(n==2)return true;
    ll D=n-1, S=0;
    while(D%2==0){D/=2;S++;}
    
    for(const ll A:{2,325,9375,28178,450775,9780504,1795265022})
    {
        if(A%n==0)continue;
        ll M = potlog(A,D,n);

        if(M==1 || M==(n-1)) goto next;
        for(int i=0;i<S-1;i++)
        {
            M=prodlog(M,M,n);
            if(M==(n-1))goto next;
        }
        return false;
        next:;
    }
    return true;
    
}

ll factor(ll n)
{
    static ll A,B;
    A=1+rand()%(n-1);
    B=1+rand()%(n-1);
    #define f(x) (prodlog(x,x+B,n)+A)
    ll x=2,y=2,d=1;
    while(d==1 || d==-1)
    {
        x=f(x);
        y=f(f(y));
        d=gcd(x-y,n);
    }
    return abs(d);
}

map<ll,ll> factorizacion(ll n)
{
    assert(n>=1);
    map<ll,ll> ans;
    vector<ll> pending={n};

    while (!pending.empty())
    {
        ll x = pending.back(); pending.pop_back();
        if(esprimo(x))
        {
            ans[x]++;
        }
        else
        {
            ll d=x;
            while(d==x) d=factor(x);

            pending.push_back(d);
            pending.push_back(x/d);
        }
    }
    return ans;
    
}


int main()
{
    ll numero=1290985902348905;
    map<ll,ll> desc=factorizacion(numero);
    /*
    la funcion factorizacion devuelve mapa, donde first el el primo
    y second es la cantidad de repeticiones que tiene
    */

    return 0;
}