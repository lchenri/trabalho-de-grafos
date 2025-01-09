#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

/**
* @file lista_encadeada.h
* @brief O arquivo lista_encadeada.h contém as definições das classes ListaVertices e ListaArestas e das estruturas NoVertice e NoAresta.
*/

/**
* @brief Estrutura para um nó de aresta.
* @details Cada nó de aresta possui um ponteiro para o vértice de origem, um inteiro para o destino e um inteiro para o peso.
* @details Além disso, possui um ponteiro para o próximo nó de aresta.
* @details A estrutura é utilizada para a lista de arestas de um vértice.
*/
struct NoAresta {
    NoAresta *head;
    int destino;
    int peso;
    NoAresta *prox;
    NoAresta(int dest, int p = 0) : destino(dest), peso(p), prox(nullptr) {}
};

/**
* @brief Estrutura para um nó de vértice.
* @details Cada nó de vértice possui um inteiro para o id, um inteiro para o peso e um ponteiro para o próximo nó de vértice.
* @details Além disso, possui um ponteiro para a lista de arestas do vértice.
* @details A estrutura é utilizada para a lista de vértices de um grafo.
*/
struct NoVertice {
    int id;
    int peso;
    NoVertice *prox;
    NoAresta *arestas;
    NoVertice(int identificacao, int p = 0) : id(identificacao), peso(p), prox(nullptr), arestas(nullptr) {}
};

/**
* @brief Classe para lista de vértices.
* @details A classe possui um ponteiro para o primeiro nó de vértice da lista.
* @details Possui métodos para adicionar um vértice à lista e para buscar um vértice na lista.
* @details Além disso, possui um destrutor que libera a memória alocada para a lista.
* @details A classe é utilizada para a lista de vértices de um grafo.
*/
class ListaVertices {
    public:
        NoVertice *head;
        ListaVertices() : head(nullptr) {}
        ~ListaVertices();
        void adicionar_vertice(int id, int peso = 0);
        NoVertice *buscar_vertice(int id);
};

/**
* @brief Classe para lista de arestas.
* @details A classe possui um ponteiro para o primeiro nó de aresta da lista.
* @details Possui um método para adicionar uma aresta à lista.
* @details Além disso, possui um destrutor que libera a memória alocada para a lista.
* @details A classe é utilizada para a lista de arestas de um vértice.
*/
class ListaArestas {
    public:
        NoAresta *head;
        ListaArestas() : head(nullptr) {}
        ~ListaArestas();
        void adicionar_aresta(int destino, int peso = 0);
};
#endif // LISTA_ENCADEADA_H
