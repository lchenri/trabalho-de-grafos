#include "../include/grafo.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <climits>
#include <cstdlib>
#include <ctime>

/**
 * @file grafo.cpp
 * @brief Implementação da classe grafo.
 */

grafo::grafo() {}

struct Aresta {
    int origem;
    int destino;
    Aresta* next;
};

/**
 * @brief Constroi o grafo a partir de um arquivo.
 * @param arquivo O caminho para o arquivo contendo a descrição do grafo.
 */
void grafo::carrega_grafo(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) throw std::runtime_error("Arquivo não encontrado");

    int num_nos, dir, pond_vertices, pond_arestas;
    file >> num_nos >> dir >> pond_vertices >> pond_arestas;

    this->direcionado = dir;
    this->ponderado_vertices = pond_vertices;
    this->ponderado_arestas = pond_arestas;
    this->num_nos = num_nos;

    if (ponderado_vertices) {
        for (int i = 1; i <= num_nos; ++i) {
            int peso;
            file >> peso;
            add_no(i, peso);
        }
    } else {
        for (int i = 1; i <= num_nos; ++i) {
            add_no(i, 0);
        }
    }

    int origem, destino, peso = 0;
    while (file >> origem >> destino) {
        if (ponderado_arestas) file >> peso;
        add_aresta(origem, destino, peso);
    }
}

/**
 * @brief Verifica se o grafo é completo.
 * @return true se o grafo é completo, false caso contrário.
 */
bool grafo::eh_completo() {
    int n = get_ordem();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j && !existe_aresta(i, j)) {
                if (direcionado) return false;
                if (!existe_aresta(j, i)) return false;
            }
        }
    }
    return true;
}

/**
 * @brief Libera a memória alocada para as arestas temporárias.
 * @param cabeca O ponteiro para a primeira aresta.
 */
void liberar_arestas_temp(aresta_grafo* cabeca) {
    while (cabeca) {
        aresta_grafo* temp = cabeca;
        cabeca = cabeca->proxima;
        delete temp;
    }
}

/**
 * @brief Retorna o grau do grafo.
 * @return O grau do grafo.
 */
int grafo::get_grau() {
    int grau_maximo = 0;
    int n = get_ordem();
    for (int i = 1; i <= n; ++i) {
        int grau_atual = 0;
        aresta_grafo* vizinhos = get_vizinhos(i);
        aresta_grafo* atual = vizinhos;
        while (atual) {
            grau_atual++;
            atual = atual->proxima;
        }
        liberar_arestas_temp(vizinhos);

        if (direcionado) {
            for (int j = 1; j <= n; ++j) {
                if (existe_aresta(j, i)) grau_atual++;
            }
        }

        if (grau_atual > grau_maximo) grau_maximo = grau_atual;
    }
    return grau_maximo;
}

/**
 * @brief Calcula uma cobertura de vértices usando a estratégia gulosa.
 * @param tamanho Ponteiro para armazenar o tamanho da cobertura encontrada.
 * @return Um array com os vértices da cobertura.
 */
int* grafo::cobertura_gulosa(int* tamanho) {
    *tamanho = 0;
    int* cobertura = nullptr;
    int capacidade = 0;
    Aresta* lista_arestas = nullptr;
    int n = get_ordem();

    for (int i = 1; i <= n; ++i) {
        aresta_grafo* atual = get_vizinhos(i);
        aresta_grafo* temp;
        while (atual) {
            if (!direcionado && i > atual->destino) {
                temp = atual;
                atual = atual->proxima;
                delete temp;
                continue;
            }
            Aresta* nova = new Aresta;
            nova->origem = i;
            nova->destino = atual->destino;
            nova->next = lista_arestas;
            lista_arestas = nova;
            temp = atual;
            atual = atual->proxima;
            delete temp;
        }
    }

    int* graus = new int[n + 1];

    while (lista_arestas) {
        for (int i = 0; i <= n; i++)
            graus[i] = 0;

        Aresta* atual = lista_arestas;
        while (atual) {
            graus[atual->origem]++;
            graus[atual->destino]++;
            atual = atual->next;
        }

        int max_grau = -1;
        int escolhido = -1;
        for (int i = 1; i <= n; ++i) {
            if (graus[i] > max_grau) {
                max_grau = graus[i];
                escolhido = i;
            }
        }

        if (*tamanho >= capacidade) {
            capacidade = (capacidade > 0 ? capacidade * 2 : 1);
            int* nova = new int[capacidade];
            for (int i = 0; i < *tamanho; i++) {
                nova[i] = cobertura[i];
            }
            delete[] cobertura;
            cobertura = nova;
        }
        cobertura[(*tamanho)++] = escolhido;

        Aresta** ptr = &lista_arestas;
        while (*ptr) {
            if ((*ptr)->origem == escolhido || (*ptr)->destino == escolhido) {
                Aresta* temp = *ptr;
                *ptr = (*ptr)->next;
                delete temp;
            } else {
                ptr = &(*ptr)->next;
            }
        }
    }
    delete[] graus;
    return cobertura;
}

/**
 * @brief Calcula uma cobertura de vértices usando uma estratégia randomizada.
 * @param tamanho Ponteiro para armazenar o tamanho da cobertura encontrada.
 * @return Um array com os vértices da cobertura.
 */
int* grafo::cobertura_randomizada(int* tamanho) {
    *tamanho = 0;
    int* cobertura = nullptr;
    int capacidade = 0;
    Aresta* lista_arestas = nullptr;
    int n = get_ordem();

    srand((unsigned)time(nullptr));

    for (int i = 1; i <= n; ++i) {
        aresta_grafo* atual = get_vizinhos(i);
        aresta_grafo* temp;
        while (atual) {
            if (!direcionado && i > atual->destino) {
                temp = atual;
                atual = atual->proxima;
                delete temp;
                continue;
            }
            Aresta* nova = new Aresta;
            nova->origem = i;
            nova->destino = atual->destino;
            nova->next = lista_arestas;
            lista_arestas = nova;
            temp = atual;
            atual = atual->proxima;
            delete temp;
        }
    }

    int candidateCapacity = 0;
    int* candidatosBuffer = 0;

    while (lista_arestas) {
        int contador = 0;
        Aresta* atual = lista_arestas;
        while (atual) {
            contador += 2;
            atual = atual->next;
        }

        if (candidateCapacity < contador) {
            if (candidatosBuffer != 0) {
                delete[] candidatosBuffer;
            }
            candidatosBuffer = new int[contador];
            candidateCapacity = contador;
        }

        int pos = 0;
        atual = lista_arestas;
        while (atual) {
            candidatosBuffer[pos++] = atual->origem;
            candidatosBuffer[pos++] = atual->destino;
            atual = atual->next;
        }

        int escolhido = candidatosBuffer[rand() % contador];

        if (*tamanho >= capacidade) {
            capacidade = (capacidade > 0 ? capacidade * 2 : 1);
            int* nova = new int[capacidade];
            for (int i = 0; i < *tamanho; i++) {
                nova[i] = cobertura[i];
            }
            delete[] cobertura;
            cobertura = nova;
        }
        cobertura[(*tamanho)++] = escolhido;

        Aresta** ptr = &lista_arestas;
        while (*ptr) {
            if ((*ptr)->origem == escolhido || (*ptr)->destino == escolhido) {
                Aresta* temp = *ptr;
                *ptr = (*ptr)->next;
                delete temp;
            } else {
                ptr = &(*ptr)->next;
            }
        }
    }

    if (candidatosBuffer != 0) {
        delete[] candidatosBuffer;
    }
    return cobertura;
}

/**
 * @brief Verifica se a cobertura de vértices encontrada cobre todas as arestas.
 * @param cobertura Array com os vértices da cobertura.
 * @param tamanho Tamanho do array.
 * @return Número de arestas não cobertas.
 */
int grafo::verificar_erro(int* cobertura, int tamanho) {
    int erros = 0;
    int n = get_ordem();

    for (int i = 1; i <= n; ++i) { // IDs dos nós começam em 1
        aresta_grafo* vizinhos = get_vizinhos(i);
        aresta_grafo* atual = vizinhos;
        while (atual) {
            int u = i;
            int v = atual->destino;
            bool coberta = false;

            for (int j = 0; j < tamanho; ++j) {
                if (cobertura[j] == u || cobertura[j] == v) {
                    coberta = true;
                    break;
                }
            }

            if (!coberta) erros++;

            aresta_grafo* temp = atual;
            atual = atual->proxima;
            delete temp;
        }
    }
    return (direcionado) ? erros : erros / 2;
}

/**
 * @brief Calcula uma cobertura reativa de vértices combinando estratégias gulosa e randomizada.
 * @param tamanho Ponteiro para armazenar o tamanho da melhor cobertura encontrada.
 * @return Um array com os vértices da melhor cobertura.
 */
int* grafo::cobertura_reativa(int* tamanho) {
    const int MAX_ITER = 50;
    const double INITIAL_PROB = 0.5;
    double prob_guloso = INITIAL_PROB;
    int* melhor = 0;
    int menor = INT_MAX;
    int falhas_guloso = 0, falhas_random = 0;

    for (int iter = 0; iter < MAX_ITER; ++iter) {
        int* cobertura;
        int temp_size;
        bool estrategia_gulosa = ((double)rand() / RAND_MAX < prob_guloso);

        if (estrategia_gulosa) {
            cobertura = cobertura_gulosa(&temp_size);
        } else {
            cobertura = cobertura_randomizada(&temp_size);
        }

        int erros = verificar_erro(cobertura, temp_size);
        if (erros == 0) {
            if (temp_size < menor) {
                delete[] melhor;
                menor = temp_size;
                melhor = new int[menor];
                for (int i = 0; i < menor; i++) {
                    melhor[i] = cobertura[i];
                }
                *tamanho = menor;
            }
        } else {
            if (estrategia_gulosa) falhas_guloso++;
            else falhas_random++;
        }

        if (falhas_guloso + falhas_random > 0) {
            prob_guloso = 1.0 - ((double) falhas_guloso / (falhas_guloso + falhas_random));
        }

        delete[] cobertura;
    }

    return melhor;
}

/**
 * @brief Exibe a descrição do grafo.
 */
void grafo::exibe_descricao() {
    std::cout << "Grau: " << get_grau() << std::endl;
    std::cout << "Ordem: " << get_ordem() << std::endl;
    std::cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Nao") << std::endl;
    std::cout << "Completo: " << (eh_completo() ? "Sim" : "Nao") << std::endl;
}

/**
 * @brief Retorna as flags: direcionado, ponderado_vertices e ponderado_arestas.
 */
bool grafo::eh_direcionado() const { return direcionado; }
bool grafo::vertice_ponderado() const { return ponderado_vertices; }
bool grafo::aresta_ponderada() const { return ponderado_arestas; }
