struct SegmentTreeLazy
{
    void push(int nodo,int l_n, int r_n){
        
        /**
         * 1.Aplicar lazy del padre(nodo) a los hijos
         * 2.marcar el lazy a los hijos
         * 3.matar el lazy del padre */ 
            
    }
 
    long long query(int nodo, int l_n,int r_n,int l_q,int r_q){
        if(l_q<=l_n and r_n<=r_q) return st[nodo].sc;
        if(l_q>r_n or l_n>r_q) return 0;
        push(nodo,l_n,r_n);
        int m=(l_n+r_n)>>1;
        return (long long)((query(2*nodo,l_n,m,l_q,r_q)+query(2*nodo+1,m+1,r_n,l_q,r_q)));
    }
    void update(int nodo, int l_n,int r_n,int l_q,int r_q,ll val){
        if(l_q>r_n or l_n>r_q) return;
        if(l_q<=l_n and r_n<=r_q){
            //aplicar el lazy, osea si fuera suma sumarlo al nodo y guardar el lazy
            st[nodo].lazy_x+=val;
            return;
        }
        else{
            push(nodo,l_n,r_n);
            int m=(l_n+r_n)/2;
            update(2*nodo,l_n,m,l_q,r_q,val);
            update(2*nodo+1,m+1,r_n,l_q,r_q,val);
            st[nodo]=st[nodo*2]+st[nodo*2+1];
        }
    }
};