#include <bits/stdc++.h>

using namespace std;

int n, m;//nodos, links
vector<int> h;//altura del nodo
vector<int> primera;//primera aparicion
// set<int> st;
vector<bool> vis;
vector<vector<int>> gf;
vector<int> nodo;//nodo 

void dfs(int currt, int alt)
{
    if (!vis[currt])
    {
        primera[currt] = h.size();
    }
    vis[currt] = 1;
    h.push_back(alt);
    nodo.push_back(currt);

    for (int hijo : gf[currt])
    {
        if (!vis[hijo])
        {
            dfs(hijo, alt + 1);
            h.push_back(alt);
            nodo.push_back(currt);
        }
    }
}

int main()
{
    vis.assign(n, 0);
    primera.assign(n, -1);
    gf.assign(n, vector<int>());
    // st.clear();
    h.clear();
    nodo.clear();
    //0i
    dfs(0, 0);

    //hacer un segmet tree sobre h que es la altura, y responder cout<<nodo[res] donde res es el indice del minimo en el rango, para minimo en rango, donde l y r son los dos nodos
    return 0;
}