#include "../include/grafo_lista.h"

/**
 * @file grafo_lista.cpp
 * @brief Implementação da classe grafo_lista.
 */

/**
 * @brief Construtor da classe grafo_lista.
 * @details O ponteiro para o primeiro nó é inicializado como nullptr.
 */
grafo_lista::grafo_lista() : primeiro_no(nullptr) {}

/**
 * @brief Destrutor da classe grafo_lista.
 * @details Deleta todos os nós e arestas do grafo.
 */
grafo_lista::~grafo_lista() {
    no_grafo* atual = primeiro_no;
    while (atual) {
        no_grafo* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}

/**
 * @brief Retorna um nó do grafo.
 * @param id O id do nó a ser retornado.
 * @return O nó com o id especificado, ou nullptr se ele não existir.
 */
no_grafo* grafo_lista::get_no(int id) {
    no_grafo* atual = primeiro_no;
    while (atual) {
        if (atual->id == id) return atual;
        atual = atual->proximo;
    }
    return nullptr;
}

/**
 * @brief Retorna uma aresta do grafo.
 * @param origem O id do nó de origem da aresta.
 * @param destino O id do nó de destino da aresta.
 * @return A aresta que vai do nó de origem para o nó de destino, ou nullptr se ela não existir.
 */
aresta_grafo* grafo_lista::get_aresta(int origem, int destino) {
    no_grafo* no_origem = get_no(origem);
    if (!no_origem) return nullptr;

    aresta_grafo* atual = no_origem->primeira_aresta;
    while (atual) {
        if (atual->destino == destino) return atual;
        atual = atual->proxima;
    }
    return nullptr;
}

/**
 * @brief Retorna as arestas que saem de um nó.
 * @param id O id do nó.
 * @return Um ponteiro para a primeira aresta que sai do nó, ou nullptr se ele não existir.
 */
aresta_grafo* grafo_lista::get_vizinhos(int id) {
    no_grafo* no = get_no(id);
    if (!no) return nullptr;

    aresta_grafo* cabeca = nullptr;
    aresta_grafo* atual = nullptr;

    aresta_grafo* aresta_original = no->primeira_aresta;
    while (aresta_original) {
        // Cria uma cópia da aresta original
        aresta_grafo* copia = new aresta_grafo(aresta_original->destino, aresta_original->peso);

        if (!cabeca) {
            cabeca = copia;
            atual = cabeca;
        } else {
            atual->proxima = copia;
            atual = atual->proxima;
        }

        aresta_original = aresta_original->proxima;
    }

    return cabeca;
}

/**
 * @brief Retorna a ordem do grafo.
 * @return O número de nós do grafo.
 */
int grafo_lista::get_ordem() {
    int count = 0;
    no_grafo* atual = primeiro_no;
    while (atual) {
        count++;
        atual = atual->proximo;
    }
    return count;
}

/**
 * @brief Verifica se uma aresta existe no grafo.
 * @param origem O id do nó de origem da aresta.
 * @param destino O id do nó de destino da aresta.
 * @return true se a aresta existe, false caso contrário.
 */
bool grafo_lista::existe_aresta(int origem, int destino) {
    return get_aresta(origem, destino) != nullptr;
}

/**
 * @brief Adiciona um nó ao grafo.
 * @param id O id do nó.
 * @param peso O peso do nó.
 */
void grafo_lista::add_no(int id, int peso) {
    if (get_no(id)) return;

    no_grafo* novo_no = new no_grafo(id, peso);
    novo_no->proximo = primeiro_no;
    primeiro_no = novo_no;
}

/**
 * @brief Adiciona uma aresta ao grafo.
 * @param origem O id do nó de origem da aresta.
 * @param destino O id do nó de destino da aresta.
 * @param peso O peso da aresta.
 */
void grafo_lista::add_aresta(int origem, int destino, int peso) {
    if (origem == destino) return;

    no_grafo* no_origem = get_no(origem);
    no_grafo* no_destino = get_no(destino);

    if (!no_origem || !no_destino) return;

    if (existe_aresta(origem, destino)) return;

    aresta_grafo* nova_aresta = new aresta_grafo(destino, peso);
    nova_aresta->proxima = no_origem->primeira_aresta;
    no_origem->primeira_aresta = nova_aresta;

    if (!direcionado) {
        aresta_grafo* aresta_inversa = new aresta_grafo(origem, peso);
        aresta_inversa->proxima = no_destino->primeira_aresta;
        no_destino->primeira_aresta = aresta_inversa;
    }
}

