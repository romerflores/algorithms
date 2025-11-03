vector<int> prefix_function(string s)
{
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

inline void solve()
{
    string texto, sub;
    cin >> texto >> sub;
    int n = texto.size();
    int m = sub.size();
    vector<int> vec = prefix_function(sub + "$" + texto);
    cout << count(vec.begin(), vec.end(), m) << endl;
}