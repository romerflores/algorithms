vector<vector<int>> gf;
vector<bool> vis;
set<int> st;
bool sw = 1;
int n;

void isDAG(int nodo)
{
    // no olvidar recorrer con un for todo
    //ya que no siempre estan conectados
    if (!sw)return;
    vis[nodo] = 1;
    st.insert(nodo);
    for (auto hijo : gf[nodo])
    {
        if (st.count(hijo) == 1)
        {
            sw = 0;
            return;
        }
        if (!vis[hijo])
        {
            vis[hijo] = 1;
            isDAG(hijo);
        }
    }
    st.erase(nodo);
}