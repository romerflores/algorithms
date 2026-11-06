struct Point{
    ll x,y;
    ll cross(const Point& o) const {return x*o.y-y*o.x;}
};
pair<ll,pair<ll,ll>> picks_theorem(vector<Point>&p){
    ll double_area=0, B=0;
    int n=p.size();
    for(int i=0,j=n-1;i<n;j=i++){
        double_area+=p[j].cross(p[i]);
        ll dx=abs(p[i].x-p[j].x);
        ll dy=abs(p[i].y-p[j].y);
        B+=gcd(dx,dy);
    }
    double_area=abs(double_area);
    ll I=(double_area-B+2)/2;
    //Real area = double_area/2.0
    return {double_area,{I,B}};
}