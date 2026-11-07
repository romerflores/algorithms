vector<char> sums(vector<int>&a,vector<int>&p){
    int S=accumulate(a.begin(),a.end(),0);
    vector<char>d(S+1); p.assign(S+1,-1); d[0]=1;
    for(int i=0;i<a.size();i++)
        for(int s=S-a[i];s>=0;s--)
            if(d[s]&&!d[s+a[i]])
                d[s+a[i]]=1,p[s+a[i]]=i;
    return d;
}

vector<int> rec(int x,vector<int>&a,vector<int>&p){
    vector<int>r;
    while(x) r.push_back(p[x]),x-=a[p[x]];
    reverse(r.begin(),r.end());
    return r;
}