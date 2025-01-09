#include "../include/grafo_lista.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

/**
* @file grafo_lista.cpp
* @brief Implementação das funções referente à classe grafo_lista
*/

/**
* @brief Construtor padrão da classe grafo_lista
*/
Grafo_Lista::Grafo_Lista() : num_vertices(0), num_arestas(0),
                             direcionado(false),
                             peso_vertices(false), peso_arestas(false), completo(false), bipartido(false),
                             arvore(false), possui_ponte_flag(false), possui_articulacao_flag(false),
                             componentes_conexas(0) {}

/**
* @brief Destrutor padrão da classe grafo_lista
*/
Grafo_Lista::~Grafo_Lista() {}

/**
* @brief Função para adicionar uma aresta ao grafo
* @param origem Vértice de origem da aresta
* @param destino Vértice de destino da aresta
* @param peso Peso da aresta
*/
void Grafo_Lista::adicionar_aresta(int origem, int destino, int peso) {
    NoVertice *verticeOrigem = vertices.buscar_vertice(origem);
    if (!verticeOrigem) {
        vertices.adicionar_vertice(origem);
        verticeOrigem = vertices.buscar_vertice(origem);
    }

    NoAresta *arestaAtual = verticeOrigem->arestas;

    while (arestaAtual) {
        if (arestaAtual->destino == destino) {
            // Aresta já existe
            return;
        }
        arestaAtual = arestaAtual->prox;
    }

    // Adiciona a nova aresta
    NoAresta *novaAresta = new NoAresta(destino, peso);
    novaAresta->prox = verticeOrigem->arestas;
    verticeOrigem->arestas = novaAresta;

    // Se o grafo não é direcionado, adiciona a aresta inversa
    if (!direcionado) {
        NoVertice *verticeDestino = vertices.buscar_vertice(destino);
        if (!verticeDestino)
        {
            vertices.adicionar_vertice(destino);
            verticeDestino = vertices.buscar_vertice(destino);
        }

        arestaAtual = verticeDestino->arestas;

        while (arestaAtual) {
            if (arestaAtual->destino == origem) {
                // Não adiciona novamente
                return;
            }
            arestaAtual = arestaAtual->prox;
        }

        NoAresta *novaArestaInversa = new NoAresta(origem, peso);
        novaArestaInversa->prox = verticeDestino->arestas;
        verticeDestino->arestas = novaArestaInversa;
    }

    ++num_arestas;
}


/**
* @brief Função para carregar um grafo a partir de um arquivo
* @param arquivo Nome do arquivo a ser carregado
*/
void Grafo_Lista::carrega_grafo(const std::string &arquivo) {
    std::ifstream inputFile(arquivo);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Erro ao abrir o arquivo: " + arquivo);
    }

    std::string linha;

    if (std::getline(inputFile, linha)) {
        std::istringstream metaStream(linha);
        metaStream >> num_vertices >> direcionado >> peso_vertices >> peso_arestas;
    }

    // Se os vértices são ponderados, ler os pesos
    if (peso_vertices && std::getline(inputFile, linha)) {
        std::istringstream pesoVerticeStream(linha);
        for (int i = 1; i <= num_vertices; ++i)
        {
            int peso;
            if (pesoVerticeStream >> peso)
            {
                vertices.adicionar_vertice(i, peso);
            }
        }
    }
    else {
        for (int i = 1; i <= num_vertices; ++i)
        {
            vertices.adicionar_vertice(i);
        }
    }

    // Lendo as arestas
    while (std::getline(inputFile, linha)) {
        std::istringstream arestaStream(linha);
        int origem, destino, peso = 0;
        arestaStream >> origem >> destino;
        if (peso_arestas) {
            arestaStream >> peso;
        }
        adicionar_aresta(origem, destino, peso);
    }

    inputFile.close();
}

/**
* @brief Função para verificar o grau de um vértice
* @param vertice Vértice a ser verificado
* @param grau_max Grau máximo permitido
* @return Grau do vértice - true: grau menor que o máximo, false: caso contrário
*/
bool Grafo_Lista::verifica_grau(int vertice, int grau_max) {
    int grau_atual = 0;
    NoVertice* verticeAtual = vertices.buscar_vertice(vertice);
    if (!verticeAtual) return false;

    for (NoAresta* aresta = verticeAtual->arestas; aresta; aresta = aresta->prox) {
        grau_atual++;
    }

    return grau_atual < grau_max;
}

/**
* @brief Função para gerar um grafo bipartido
* @param grau_max Grau máximo permitido
* @return true: se foi possível criar o grafo bipartido, false: caso contrário
*/
bool Grafo_Lista::gerar_bipartido(int grau_max) {
    int tamanho1 = (num_vertices + 1) / 2;
    int tamanho2 = num_vertices / 2;
    int* particao1 = new int[tamanho1];
    int* particao2 = new int[tamanho2];

    int indice1 = 0, indice2 = 0;

    // Dividir vértices em duas partições
    for (int i = 1; i <= num_vertices; ++i) {
        if (i % 2 == 0) {
            particao1[indice1++] = i;
        } else {
            particao2[indice2++] = i;
        }
    }

    // Conectar vértices entre partições respeitando o grau máximo
    for (int i = 0; i < indice1; ++i) {
        for (int j = 0; j < indice2; ++j) {
            int u = particao1[i];
            int v = particao2[j];
            if (verifica_grau(u, grau_max) && verifica_grau(v, grau_max)) {
                adicionar_aresta(u, v, peso_arestas ? rand() % 20 - 10 : 1);
            }
        }
    }

    delete[] particao1;
    delete[] particao2;

    return eh_bipartido();
}

/**
* @brief Função para gerar um grafo completo
* @param grau_max Grau máximo permitido
*/
void Grafo_Lista::gerar_completo(int grau_max) {
    for (int i = 1; i <= num_vertices; ++i) {
        for (int j = 1; j <= num_vertices; ++j) {
            if (i != j)
                adicionar_aresta(i, j, peso_arestas ? rand() % 20 - 10 : 1);
        }
    }
}

/**
* @brief Função para gerar uma árvore
* @param grau_max Grau máximo permitido
*/
void Grafo_Lista::gerar_arvore(int grau_max) {
    for (int i = 2; i <= num_vertices; ++i) {
        int origem;
        do {
            origem = rand() % (i - 1) + 1;
        } while (!verifica_grau(origem, grau_max));
        adicionar_aresta(origem, i, peso_arestas ? rand() % 21 - 10 : 1);
        if (!direcionado)
            adicionar_aresta(i, origem, peso_arestas ? rand() % 21 - 10 : 1);
    }
}

/**
* @brief Função para verificar se o grafo atende às restrições
* @param grau_max Grau máximo permitido
* @param componentes Número de componentes conexas
* @param ponte_flag Flag para verificar se o grafo possui pontes
* @param articulacao_flag Flag para verificar se o grafo possui vértices de articulação
* @return true: se o grafo atende às restrições, false: caso contrário
*/
bool Grafo_Lista::verifica_restricoes(int grau_max, int componentes, bool ponte_flag, bool articulacao_flag) {
    if (n_conexo() != componentes) return false;
    if (ponte_flag && !possui_ponte()) return false;
    if (articulacao_flag && !possui_articulacao()) return false;
    for (int i = 1; i <= num_vertices; ++i) {
        if (!verifica_grau(i, grau_max)) return false;
    }
    return true;
}

/**
* @brief Função para gerar um novo grafo com base em um arquivo de descrição e salvar em um arquivo de saída
* @param descricao Arquivo de descrição do grafo
* @param arquivo Arquivo de saída
* @warning O caso trivial, diferente dos demais, usa força bruta para gerar um grafo que atenda às restrições, o que pode fazer a geração demorar mais tempo
*/
void Grafo_Lista::novo_grafo(const std::string &descricao, std::string &arquivo) {
    std::ifstream arquivo_descricao(descricao);
    if (!arquivo_descricao.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo de descrição." << std::endl;
        return;
    }

    int grau_max, ordem, direcionado_flag, componentes, vertices_ponderados_flag,
        arestas_ponderadas_flag, completo_flag, bipartido_flag, arvore_flag,
        ponte_flag, articulacao_flag;

    arquivo_descricao >> grau_max >> ordem >> direcionado_flag >> componentes;
    arquivo_descricao >> vertices_ponderados_flag >> arestas_ponderadas_flag;
    arquivo_descricao >> completo_flag >> bipartido_flag >> arvore_flag;
    arquivo_descricao >> ponte_flag >> articulacao_flag;

    num_vertices = ordem;
    num_arestas = 0;
    direcionado = direcionado_flag;
    peso_vertices = vertices_ponderados_flag;
    peso_arestas = arestas_ponderadas_flag;

    for (int i = 1; i <= num_vertices; ++i) {
        vertices.adicionar_vertice(i);
    }

    if (peso_vertices) {
        for (int i = 1; i <= num_vertices; ++i) {
            pesos_vertices[i] = rand() % 10 + 1;
        }
    }

    bool sucesso = false;

    if (completo_flag) {
        gerar_completo(grau_max);
        sucesso = eh_completo();
    } else if (arvore_flag) {
        gerar_arvore(grau_max);
        sucesso = eh_arvore();
    } else if (bipartido_flag) {
        sucesso = gerar_bipartido(grau_max);
    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, num_vertices);
        std::uniform_int_distribution<> peso_dist(-10, 10);

        while (!verifica_restricoes(grau_max, componentes, ponte_flag, articulacao_flag)) {
            int origem = dist(gen);
            int destino = dist(gen);
            if (origem != destino && verifica_grau(origem, grau_max) && verifica_grau(destino, grau_max)) {
                int peso = peso_arestas ? peso_dist(gen) : 1;
                adicionar_aresta(origem, destino, peso);
            }
        }
        sucesso = true;
    }

    if (!sucesso) {
        std::cerr << "Nao foi possivel gerar o grafo com as restricoes fornecidas." << std::endl;
        return;
    }

    std::ofstream arquivo_saida(arquivo);
    if (!arquivo_saida.is_open()) {
        std::cerr << "Nao foi possivel abrir o arquivo de saida." << std::endl;
        return;
    }

    arquivo_saida << num_vertices << " " << direcionado << " " << peso_vertices << " " << peso_arestas << "\n";

    if (peso_vertices) {
        for (int i = 1; i <= num_vertices; ++i) {
            arquivo_saida << pesos_vertices[i] << " ";
        }
        arquivo_saida << "\n";
    }

    for (NoVertice* vertice = vertices.head; vertice; vertice = vertice->prox) {
        for (NoAresta* aresta = vertice->arestas; aresta; aresta = aresta->prox) {
            arquivo_saida << vertice->id << " " << aresta->destino;
            if (peso_arestas) {
                arquivo_saida << " " << aresta->peso;
            }
            arquivo_saida << "\n";
        }
    }
}

/**
* @brief Função que verifica se um grafo é bipartido
* @return true: se o grafo é bipartido, false: caso contrário
*/
bool Grafo_Lista::eh_bipartido() {
    if (num_vertices == 0)
        return true;

    int* cores = new int[num_vertices + 1];
    int* fila = new int[num_vertices + 1];
    int inicio = 0, fim = 0;

    for (int i = 0; i <= num_vertices; ++i) {
        cores[i] = -1;
    }

    for (NoVertice* vertice = vertices.head; vertice; vertice = vertice->prox) {
        if (cores[vertice->id] == -1) {
            cores[vertice->id] = 0;
            fila[fim++] = vertice->id;

            while (inicio < fim) {
                int atual = fila[inicio++];
                NoVertice* verticeAtual = vertices.buscar_vertice(atual);
                if (!verticeAtual) continue;

                for (NoAresta* aresta = verticeAtual->arestas; aresta; aresta = aresta->prox) {
                    int destino = aresta->destino;

                    if (cores[destino] == -1) {
                        cores[destino] = 1 - cores[atual];
                        fila[fim++] = destino;
                    } else if (cores[destino] == cores[atual]) {
                        delete[] cores;
                        delete[] fila;
                        return false;
                    }
                }
            }
        }
    }

    delete[] cores;
    delete[] fila;
    return true;
}

/**
* @brief Função auxiliar do n_conexo para explorar um componente conexo de cada vez
* @param vertice_id Vértice a ser explorado
* @param visitado Array de vértices visitados
*/
void Grafo_Lista::explorar_componente(int vertice_id, bool visitado[]) {
    visitado[vertice_id] = true;

    NoVertice* verticeAtual = vertices.buscar_vertice(vertice_id);
    if (!verticeAtual) return;

    for (NoAresta* aresta = verticeAtual->arestas; aresta; aresta = aresta->prox) {
        if (!visitado[aresta->destino]) {
            explorar_componente(aresta->destino, visitado);
        }
    }

    for (NoVertice* v = vertices.head; v; v = v->prox) {
        for (NoAresta* aresta = v->arestas; aresta; aresta = aresta->prox) {
            if (aresta->destino == vertice_id && !visitado[v->id]) {
                explorar_componente(v->id, visitado);
            }
        }
    }
}

/**
* @brief Função para verificar o número de componentes conexas do grafo
* @return Número de componentes conexas
*/
int Grafo_Lista::n_conexo() {
    bool* visitado = new bool[num_vertices]();
    int componentes = 0;

    for (NoVertice* vertice = vertices.head; vertice; vertice = vertice->prox) {
        if (!visitado[vertice->id]) {
            componentes++;
            explorar_componente(vertice->id, visitado);
        }
    }

    delete[] visitado;
    return componentes;
}

/**
* @brief Função para verificar o grau do grafo
* @return Grau do grafo (grau máximo entre o grau de todos os vértices)
*/
int Grafo_Lista::get_grau() {
    int grau_max = 0;

    NoVertice* verticeAtual = vertices.head;
    while (verticeAtual) {
        int grau_atual = 0;

        NoAresta* arestaAtual = verticeAtual->arestas;
        while (arestaAtual) {
            ++grau_atual;
            arestaAtual = arestaAtual->prox;
        }

        grau_max = std::max(grau_max, grau_atual);

        verticeAtual = verticeAtual->prox;
    }

    return grau_max;
}

/**
* @brief Função para verificar a ordem do grafo
* @return Ordem do grafo (número de vértices)
*/
int Grafo_Lista::get_ordem() {
    return num_vertices;
}

/**
* @brief Função para verificar se o grafo é direcionado
* @return true: se o grafo é direcionado, false: caso contrário
*/
bool Grafo_Lista::eh_direcionado() {
    return direcionado;
}

/**
* @brief Função para verificar se os vértices são ponderados
* @return true: se os vértices são ponderados, false: caso contrário
*/
bool Grafo_Lista::vertice_ponderado() {
    return peso_vertices;
}

/**
* @brief Função para verificar se as arestas são ponderadas
* @return true: se as arestas são ponderadas, false: caso contrário
*/
bool Grafo_Lista::aresta_ponderada() {
    return peso_arestas;
}

/**
* @brief Função para verificar se o grafo é completo
* @return true: se o grafo é completo, false: caso contrário
*/
bool Grafo_Lista::eh_completo() {
    for (NoVertice* vertice = vertices.head; vertice; vertice = vertice->prox) {
        int grau = 0;
        for (NoAresta* aresta = vertice->arestas; aresta; aresta = aresta->prox) {
            grau++;
        }
        if (grau != num_vertices - 1) {
            return false;
        }
    }
    return true;
}

/**
* @brief Função para verificar se o grafo é uma árvore
* @return true: se o grafo é uma árvore, false: caso contrário
*/
bool Grafo_Lista::eh_arvore() {
    return n_conexo() == 1 && num_arestas == num_vertices - 1;
}

/**
* @brief Função auxiliar para a função de verificação de vértices de articulação
* @param u Vértice atual
* @param visitado Array de vértices visitados
* @param discovery Array de descobertas
* @param low Array de valores low
* @param parent Array de pais
* @param possui_articulacao Flag para verificar se o grafo possui vértices de articulação
* @param tempo Tempo de descoberta
*/
void Grafo_Lista::dfs_articulacao(int u, bool visitado[], int discovery[], int low[], int parent[], bool& possui_articulacao, int& tempo) {
    visitado[u] = true;
    discovery[u] = low[u] = ++tempo;
    int filhos = 0;

    NoVertice* verticeAtual = vertices.buscar_vertice(u);
    if (!verticeAtual) {
        std::cerr << "Vertice " << u << " nao encontrado durante a DFS.\n";
        return;
    }

    for (NoAresta* aresta = verticeAtual->arestas; aresta != nullptr; aresta = aresta->prox) {
        int v = aresta->destino;

        if (!visitado[v]) {
            filhos++;
            parent[v] = u;
            dfs_articulacao(v, visitado, discovery, low, parent, possui_articulacao, tempo);

            low[u] = std::min(low[u], low[v]);

            if (parent[u] == -1 && filhos > 1) {
                possui_articulacao = true;
            }

            if (parent[u] != -1 && low[v] >= discovery[u]) {
                possui_articulacao = true;
            }
        }
        else if (v != parent[u]) {
            low[u] = std::min(low[u], discovery[v]);
        }
    }
}

/**
* @brief Função para verificar se o grafo possui vértices de articulação
* @return true: se o grafo possui vértices de articulação, false: caso contrário
*/
bool Grafo_Lista::possui_articulacao() {
    bool* visitado = new bool[num_vertices + 1];
    int* discovery = new int[num_vertices + 1];
    int* low = new int[num_vertices + 1];
    int* parent = new int[num_vertices + 1];

    for (int i = 0; i <= num_vertices; ++i) {
        visitado[i] = false;
        discovery[i] = -1;
        low[i] = -1;
        parent[i] = -1;
    }

    bool possui_articulacao_flag = false;
    int tempo = 0;


    for (NoVertice* vertice = vertices.head; vertice != nullptr; vertice = vertice->prox) {
        int u = vertice->id;
        if (!visitado[u]) {
            dfs_articulacao(u, visitado, discovery, low, parent, possui_articulacao_flag, tempo);
        }
    }

    delete[] visitado;
    delete[] discovery;
    delete[] low;
    delete[] parent;

    return possui_articulacao_flag;
}

/**
* @brief Função auxiliar para a função de verificação de arestas pontes
* @param u Vértice atual
* @param visitado Array de vértices visitados
* @param discovery Array de descobertas
* @param low Array de valores low
* @param parent Array de pais
* @param possui_ponte Flag para verificar se o grafo possui arestas pontes
* @param tempo Tempo de descoberta
*/
void Grafo_Lista::dfs_ponte(int u, bool visitado[], int discovery[], int low[], int parent[], bool& possui_ponte, int& tempo) {
    visitado[u] = true;
    discovery[u] = low[u] = ++tempo;

    NoVertice* verticeAtual = vertices.buscar_vertice(u);
    if (!verticeAtual) return;

    for (NoAresta* aresta = verticeAtual->arestas; aresta != nullptr; aresta = aresta->prox) {
        int v = aresta->destino;

        if (!visitado[v]) {
            parent[v] = u;
            dfs_ponte(v, visitado, discovery, low, parent, possui_ponte, tempo);

            low[u] = std::min(low[u], low[v]);

            if (low[v] > discovery[u]) {
                possui_ponte = true;
            }
        }
        else if (v != parent[u]) {
            low[u] = std::min(low[u], discovery[v]);
        }
    }
}

/**
* @brief Função para verificar se o grafo possui arestas pontes
* @return true: se o grafo possui arestas pontes, false: caso contrário
*/
bool Grafo_Lista::possui_ponte() {
    bool* visitado = new bool[num_vertices + 1];
    int* discovery = new int[num_vertices + 1];
    int* low = new int[num_vertices + 1];
    int* parent = new int[num_vertices + 1];

    for (int i = 0; i <= num_vertices; ++i) {
        visitado[i] = false;
        discovery[i] = -1;
        low[i] = -1;
        parent[i] = -1;
    }

    bool possui_ponte = false;
    int tempo = 0;

    for (NoVertice* vertice = vertices.head; vertice; vertice = vertice->prox) {
        int u = vertice->id;
        if (!visitado[u]) {
            dfs_ponte(u, visitado, discovery, low, parent, possui_ponte, tempo);
        }
    }

    delete[] visitado;
    delete[] discovery;
    delete[] low;
    delete[] parent;

    return possui_ponte;
}

/**
* @brief Função para exibir a descrição do grafo tanto em um documento quanto no console
*/
void Grafo_Lista::exibe_descricao()
{
    std::cout << "Grau: " << get_grau() << std::endl;
    std::cout << "Ordem: " << get_ordem() << std::endl;
    std::cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Componentes conexas: " << n_conexo() << std::endl;
    std::cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Nao") << std::endl;
    std::cout << "Completo: " << (eh_completo() ? "Sim" : "Nao") << std::endl;
    std::cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Nao") << std::endl;
    std::cout << "Arvore: " << (eh_arvore() ? "Sim" : "Nao") << std::endl;
    std::cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Nao") << std::endl;
    std::cout << "Vertice de Articulacao: " << (possui_articulacao() ? "Sim" : "Nao") << std::endl;
}
