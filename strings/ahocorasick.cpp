#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    static constexpr int ALPHA = 26;
    static constexpr char BASE = 'a';

    struct Node {
        array<int, ALPHA> next;
        int link;
        int outputLink;
        vector<int> output;

        // Complejidad: O(ALPHA)
        Node() : link(0), outputLink(-1) {
            next.fill(-1);
        }
    };

    vector<Node> trie;
    vector<int> patternLength;
    bool built;

    // Complejidad: O(ALPHA)
    AhoCorasick() {
        init();
    }

    // Reinicia toda la estructura.
    // Complejidad: O(total de nodos)
    void init() {
        trie.clear();
        trie.emplace_back();
        patternLength.clear();
        built = false;
    }

    // Convierte un caracter valido en su indice.
    // Complejidad: O(1)
    int charId(char c) const {
        return c - BASE;
    }

    // Verifica si el caracter pertenece al alfabeto.
    // Complejidad: O(1)
    bool validChar(char c) const {
        int id = charId(c);
        return 0 <= id && id < ALPHA;
    }

    // Agrega un patron y retorna su identificador.
    // Los identificadores se asignan desde cero.
    // Complejidad: O(longitud del patron)
    int addPattern(const string& pattern) {
        int patternId = (int)patternLength.size();
        patternLength.push_back((int)pattern.size());

        int node = 0;

        for (char c : pattern) {
            int id = charId(c);

            assert(0 <= id && id < ALPHA);

            if (trie[node].next[id] == -1) {
                trie[node].next[id] = (int)trie.size();
                trie.emplace_back();
            }

            node = trie[node].next[id];
        }

        trie[node].output.push_back(patternId);
        built = false;

        return patternId;
    }

    // Construye failure links, output links y transiciones completas.
    // Debe ejecutarse despues de agregar todos los patrones.
    // Complejidad: O(numero de nodos * ALPHA)
    void build() {
        queue<int> q;

        trie[0].link = 0;
        trie[0].outputLink = -1;

        for (int c = 0; c < ALPHA; ++c) {
            int child = trie[0].next[c];

            if (child == -1) {
                trie[0].next[c] = 0;
            } else {
                trie[child].link = 0;
                trie[child].outputLink = trie[0].output.empty() ? -1 : 0;
                q.push(child);
            }
        }

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int c = 0; c < ALPHA; ++c) {
                int child = trie[node].next[c];

                if (child == -1) {
                    trie[node].next[c] = trie[trie[node].link].next[c];
                    continue;
                }

                int failure = trie[trie[node].link].next[c];
                trie[child].link = failure;

                if (!trie[failure].output.empty()) {
                    trie[child].outputLink = failure;
                } else {
                    trie[child].outputLink = trie[failure].outputLink;
                }

                q.push(child);
            }
        }

        built = true;
    }

    // Retorna el siguiente estado al procesar un caracter.
    // Requiere que build haya sido ejecutado.
    // Complejidad: O(1)
    int advance(int state, char c) const {
        assert(built);

        if (!validChar(c)) {
            return 0;
        }

        return trie[state].next[charId(c)];
    }

    // Ejecuta una funcion para cada patron que termina en el estado actual.
    // callback recibe patternId.
    // Complejidad: O(numero de coincidencias reportadas + cadena de outputs)
    template <class Callback>
    void forEachOutput(int state, Callback callback) const {
        for (int node = state; node != -1; node = trie[node].outputLink) {
            for (int patternId : trie[node].output) {
                callback(patternId);
            }
        }
    }

    // Retorna todas las coincidencias como pares:
    // {posicion inicial, patternId}.
    // Complejidad: O(longitud del texto + numero de coincidencias)
    vector<pair<int, int>> findAll(const string& text) const {
        assert(built);

        vector<pair<int, int>> matches;
        int state = 0;

        for (int i = 0; i < (int)text.size(); ++i) {
            state = advance(state, text[i]);

            forEachOutput(state, int patternId {
                int start = i - patternLength[patternId] + 1;
                matches.push_back({start, patternId});
            });
        }

        return matches;
    }

    // Retorna cuantas veces aparece cada patron en el texto.
    // Cuenta apariciones superpuestas.
    // Complejidad: O(longitud del texto + numero de coincidencias)
    vector<long long> countOccurrences(const string& text) const {
        assert(built);

        vector<long long> count(patternLength.size(), 0);
        int state = 0;

        for (char c : text) {
            state = advance(state, c);

            forEachOutput(state, int patternId {
                ++count[patternId];
            });
        }

        return count;
    }

    // Retorna la primera posicion de cada patron.
    // Retorna -1 para patrones que no aparecen.
    // Complejidad: O(longitud del texto + numero de coincidencias)
    vector<int> firstOccurrence(const string& text) const {
        assert(built);

        vector<int> first(patternLength.size(), -1);
        int state = 0;

        for (int i = 0; i < (int)text.size(); ++i) {
            state = advance(state, text[i]);

            forEachOutput(state, int patternId {
                if (first[patternId] == -1) {
                    first[patternId] = i - patternLength[patternId] + 1;
                }
            });
        }

        return first;
    }

    // Verifica si al menos un patron aparece en el texto.
    // Complejidad: O(longitud del texto) en el peor caso
    bool containsAny(const string& text) const {
        assert(built);

        int state = 0;

        for (char c : text) {
            state = advance(state, c);

            if (!trie[state].output.empty() || trie[state].outputLink != -1) {
                return true;
            }
        }

        return false;
    }

    // Verifica si un patron especifico aparece en el texto.
    // Complejidad: O(longitud del texto + numero de coincidencias)
    bool containsPattern(const string& text, int targetId) const {
        assert(built);
        assert(0 <= targetId && targetId < (int)patternLength.size());

        int state = 0;

        for (char c : text) {
            state = advance(state, c);

            bool found = false;

            forEachOutput(state, int patternId {
                if (patternId == targetId) {
                    found = true;
                }
            });

            if (found) {
                return true;
            }
        }

        return false;
    }

    // Retorna la cantidad de nodos del automata.
    // Complejidad: O(1)
    int nodeCount() const {
        return (int)trie.size();
    }

    // Retorna la cantidad de patrones agregados.
    // Complejidad: O(1)
    int patternCount() const {
        return (int)patternLength.size();
    }
};