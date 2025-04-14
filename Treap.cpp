/*
  Treap Ordenado con Acceso por Índice
  ------------------------------------

  Este código implementa un Treap (árbol binario de búsqueda + heap aleatorio)
  que mantiene los elementos ordenados (como un multiset), permite elementos
  repetidos, e implementa acceso eficiente por índice (get_kth, erase_kth),
  todo en tiempo esperado O(log n).

  ✔️ Propiedades clave:
    - Los nodos están ordenados por valor (como en un BST).
    - Cada nodo tiene una prioridad aleatoria (como en un heap), para balanceo probabilístico.
    - Cada nodo almacena:
        - `val` = valor del elemento.
        - `cnt` = cuántas veces aparece ese valor (para admitir repetidos).
        - `sz`  = tamaño total del subárbol (contando repeticiones).
    - Soporta inserciones, borrados y consultas por índice en O(log n) esperado.

  📦 Funciones principales:
    - insert(t, x)       → Inserta el valor x.
    - erase(t, x)        → Borra una ocurrencia del valor x.
    - get_kth(t, k)      → Devuelve el valor en la posición k (0-indexado).
    - erase_kth(t, k)    → Borra el elemento en la posición k.

  🧠 Uso típico:
    - Para mantener una lista ordenada dinámicamente, con elementos repetidos.
    - Para encontrar el k-ésimo menor/mayor elemento en tiempo logarítmico.
    - Para estructuras de datos que necesitan multiset + indexación eficiente.

  🛠️ Tiempo esperado por operación: O(log n)

  Autor: [Tu Nombre]
  Fuente base: Estructura clásica de Treap + conteo de duplicados + índice implícito

*/



#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define CRISTIANO_RONALDO_GANO_35_COPAS \
	ios_base::sync_with_stdio(false);   \
	cin.tie(NULL);                      \
	cout.tie(nullptr);
#define hola cout << "hola" << endl;
#define YES cout << "YES" << endl;
#define NO cout << "NO" << endl;
#define printv(v)                      \
	for (int i = 0; i < v.size(); i++) \
	{                                  \
		cout << v[i] << " ";           \
	}                                  \
	cout << "\n";
#define printvii(v)                                       \
	for (int i = 0; i < v.size(); i++)                    \
	{                                                     \
		cout << v[i].first << " " << v[i].second << endl; \
	}                                                     \
	cout << endl;

#define RAYA cout << "----------------------------" << endl;

// #define debug1(A) if(debug) { cerr << "? " << #A << " : " << A << endl; }

const int MOD = 1000000007;
const int INFINITO_INT = INT_MAX;
#define dbg(x) cout << #x << " " << x << endl;

string toLower(string cad)
{
	for (int i = 0; i < int(cad.length()); i++)
		if (cad[i] <= 'Z')
			cad[i] += 32;
	return cad;
}
ll sumatoriall(ll n) { return ((n * (n + 1)) / 2); }
int sumatoriaint(int n) { return ((n * (n + 1)) / 2); }

bool cmp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
{
	return a.first > b.first;
}

ll binpow(ll b, ll e)
{
	if (e == 0)
		return 1;

	ll pot = binpow(b, e / 2);
	pot *= pot;

	if (e & 1)
		pot *= b;
	return pot;
}

ll factor(ll l, ll x)
{
	ll num = (l - 1) / x;
	num++;
	return num * x;
}

ll gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

void yesno(bool sw)
{
	if (sw)
	{
		YES;
	}
	else
		NO;
}

struct Node
{
	int val, prio, sz, cnt;
	Node *l, *r;
	Node(int v) : val(v), prio(rand()), sz(1), cnt(1), l(nullptr), r(nullptr) {}
};

int size(Node *t) { return t ? t->sz : 0; }

void update(Node *t)
{
	if (t)
		t->sz = t->cnt + size(t->l) + size(t->r);
}

void split(Node *t, int val, Node *&l, Node *&r)
{
	if (!t)
		return void(l = r = nullptr);
	if (val < t->val)
		split(t->l, val, l, t->l), r = t;
	else
		split(t->r, val, t->r, r), l = t;
	update(t);
}

Node *merge(Node *l, Node *r)
{
	if (!l || !r)
		return l ? l : r;
	if (l->prio > r->prio)
	{
		l->r = merge(l->r, r),update(l);return l;
	}
		
	else
		{r->l = merge(l, r->l), update(r); return r;}
}

void insert(Node *&t, int val)
{
	if (!t)
		t = new Node(val);
	else if (t->val == val)
		t->cnt++, update(t);
	else if (val < t->val)
		insert(t->l, val), update(t);
	else
		insert(t->r, val), update(t);
}

void erase(Node *&t, int val)
{
	if (!t)
		return;
	if (t->val == val)
	{
		if (t->cnt > 1)
			t->cnt--;
		else
		{
			Node *tmp = t;
			t = merge(t->l, t->r);
			delete tmp;
		}
	}
	else if (val < t->val)
		erase(t->l, val);
	else
		erase(t->r, val);
	update(t);
}

int get_kth(Node *t, int k)
{
	if (!t)
		return -1;
	if (size(t->l) >= k + 1)
		return get_kth(t->l, k);
	if (size(t->l) + t->cnt > k)
		return t->val;
	return get_kth(t->r, k - size(t->l) - t->cnt);
}

void erase_kth(Node *&t, int k)
{
	if (!t)
		return;
	if (size(t->l) > k)
		erase_kth(t->l, k);
	else if (size(t->l) + t->cnt > k)
	{
		if (t->cnt > 1)
			t->cnt--;
		else
		{
			Node *tmp = t;
			t = merge(t->l, t->r);
			delete tmp;
		}
	}
	else
		erase_kth(t->r, k - size(t->l) - t->cnt);
	update(t);
}

int main()
{
	int t = 1;
	// cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		int j;
		cin >> j;

		Node *treap = nullptr;

		vector<int> vec(n,0);for(int i=0;i<n;i++)cin>>vec[i];
		for (int i = 0; i < j; i++)
		{
			insert(treap, vec[i]);
		}
		

		cout << get_kth(treap, (j - 1) / 2) << endl;

		for(int i=j;i<n;i++)
		{
			erase(treap,vec[i-j]);
			insert(treap,vec[i]);
			cout << get_kth(treap, (j - 1) / 2) << endl;
		}
	}
}
