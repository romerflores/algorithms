double mejordist;
double menordis;

//P x,y
//dist ditancia euclidana
//El kde tree nos puede ayudar a calcular el vecino mas cercano a un punto

struct KDTree
{
    struct Nodo
    {
        P p;
        Nodo* left;
        Nodo* rigth;
        int id;
        Nodo(P pt):p(pt),left(nullptr),rigth(nullptr){}
    };

    Nodo* raiz;


    Nodo* insertar(Nodo* nodo,P pt,int dep)
    {
        if(nodo==nullptr)return new Nodo(pt);
        int dim=dep%2;
        if(dim==0)
        {
            if(pt.x<nodo->p.x)nodo->left=insertar(nodo->left,pt,dep+1);
            else nodo->rigth=insertar(nodo->rigth,pt,dep+1);
        }
        else
        {
            if(pt.y<nodo->p.y)nodo->left=insertar(nodo->left,pt,dep+1);
            else nodo->rigth=insertar(nodo->rigth,pt,dep+1);
        }
        return nodo;
    }

    // void search(Nodo *nodo,P pt,int dep)
    // {
    //     if(nodo==nullptr)return;
    //     ans=nodo->p;
    //     int dim=dep%2;

    //     if(dim==0)
    //     {
    //         if(pt.x<nodo->p.x)search(nodo->left,pt,dep+1);
    //         else search(nodo->rigth,pt,dep+1);
    //     }
    //     else
    //     {
    //         if(pt.y<nodo->p.y)search(nodo->left,pt,dep+1);
    //         else search(nodo->rigth,pt,dep+1);
    //     }


    // }

    void search(Nodo* nodo,P pt,int dep,int mn=0)
    {
        if(nodo==nullptr)return;

        double d=dist(nodo->p,pt);

        if(d>mn and d<mejordist)
        {
            mejordist=d;
            ans=nodo->p;
        }

        int dim=dep%2;

        Nodo* first;
        Nodo* second;

        if((dim==0 && pt.x<nodo->p.x) || (dim==1 && pt.y<nodo->p.y))
        {
            first=nodo->left;
            second=nodo->rigth;
        }
        else
        {
            first=nodo->rigth;
            second=nodo->left;
        }

        search(first,pt,dep+1,mn);

        double planeDist;

        if(dim==0)planeDist=(pt.x-nodo->p.x)*(pt.x-nodo->p.x);
        else planeDist=(pt.y-nodo->p.y)*(pt.y-nodo->p.y);
        if(planeDist<mejordist)search(second,pt,dep+1,mn);
    }

    KDTree():raiz(nullptr){};
    
};
