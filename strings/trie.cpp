#include <bits/stdc++.h>
using namespace std;

struct Trie {
    static constexpr int ALPHABET = 26;

    struct Node {
        int next[ALPHABET];
        int prefixCount;
        int wordCount;

        Node() {
            fill(next, next + ALPHABET, -1);
            prefixCount = 0;
            wordCount = 0;
        }
    };

    vector<Node> trie;

    Trie(int maxNodes = 1) {
        trie.reserve(maxNodes);
        trie.emplace_back(); // Nodo 0: raiz
    }

    // Reinicia completamente el Trie
    void clear() {
        trie.clear();
        trie.emplace_back();
    }

    // Crea un nuevo nodo y devuelve su indice
    int newNode() {
        trie.emplace_back();
        return (int)trie.size() - 1;
    }

    // Inserta una palabra
    // Supone que contiene solamente letras entre 'a' y 'z'
    void insert(const string& word) {
        int node = 0;
        trie[node].prefixCount++;

        for (char ch : word) {
            int c = ch - 'a';

            if (trie[node].next[c] == -1) {
                trie[node].next[c] = newNode();
            }

            node = trie[node].next[c];
            trie[node].prefixCount++;
        }

        trie[node].wordCount++;
    }

    // Devuelve el nodo donde termina la cadena
    // Devuelve -1 si la cadena no existe como camino en el Trie
    int findNode(const string& word) const {
        int node = 0;

        for (char ch : word) {
            int c = ch - 'a';

            if (c < 0 || c >= ALPHABET)
                return -1;

            if (trie[node].next[c] == -1)
                return -1;

            node = trie[node].next[c];
        }

        return node;
    }

    // Devuelve cuantas veces se inserto exactamente una palabra
    int countWord(const string& word) const {
        int node = findNode(word);

        if (node == -1)
            return 0;

        return trie[node].wordCount;
    }

    // Indica si una palabra fue insertada al menos una vez
    bool contains(const string& word) const {
        return countWord(word) > 0;
    }

    // Devuelve cuantas palabras insertadas comienzan con prefix
    int countPrefix(const string& prefix) const {
        int node = findNode(prefix);

        if (node == -1)
            return 0;

        return trie[node].prefixCount;
    }

    // Elimina una aparicion de la palabra
    // Devuelve false si la palabra no estaba insertada
    bool erase(const string& word) {
        if (!contains(word))
            return false;

        int node = 0;
        trie[node].prefixCount--;

        for (char ch : word) {
            int c = ch - 'a';
            node = trie[node].next[c];
            trie[node].prefixCount--;
        }

        trie[node].wordCount--;
        return true;
    }

    // Devuelve la cantidad de nodos utilizados
    int size() const {
        return (int)trie.size();
    }
};
