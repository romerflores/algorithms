struct cmpST
{
    //de menor a mayor
    bool operator()(const int &a,const int &b)
    {
        return a<b;
    }
};

//set<int,cmpST> st;
