void dijstra(int s)
{
    set<pair<int,int>> pq;
    dis.assign(n,INF);
    dis[s]=0;
    pq.insert({0,s});
    while(!pq.empty())
    {
        pair<int,int> top=*pq.begin();
        pq.erase(pq.begin());

        int v=top.second;
        int d=top.first;

        for(auto [v2,cost]:gf[v])
        {
            if(dis[v2]>dis[v]+cost)
            {
                if(dis[v2]<INF)
                {
                    pq.erase(pq.find(make_pair(dis[v2],v2)));
                }
                dis[v2]=dis[v]+cost;
                pq.insert(make_pair(dis[v2],v2));
            }
        }
    }
}
