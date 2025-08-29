struct cmp
{
    //mayor tiene prioridad
    bool operator()(const int& a, const int& b) const {
        return a<b;        
    }
};

//priority_queue<Data,vector<Data>,cmp> pq
