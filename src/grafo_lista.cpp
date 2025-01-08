#include "../include/grafo_lista.h"
#include <fstream>
#include <sstream>
#include <iostream>

Grafo_Lista::Grafo_Lista() : num_vertices(0), num_arestas(0),
                             direcionado(false),
                             peso_vertices(false), peso_arestas(false), completo(false), bipartido(false),
                             arvore(false), possui_ponte_flag(false), possui_articulacao_flag(false),
                             componentes_conexas(0) {}

// Destructor
Grafo_Lista::~Grafo_Lista() {}

// Adiciona uma aresta à lista
void Grafo_Lista::adicionar_aresta(int origem, int destino, int peso)
{
    // Localiza ou cria o vértice de origem
    NoVertice *verticeOrigem = vertices.buscar_vertice(origem);
    if (!verticeOrigem)
    {
        vertices.adicionar_vertice(origem);
        verticeOrigem = vertices.buscar_vertice(origem);
    }

    // Verifica se a aresta já existe
    NoAresta *arestaAtual = verticeOrigem->arestas;
    while (arestaAtual)
    {
        if (arestaAtual->destino == destino)
        {
            // Aresta já existe, não adiciona novamente
            return;
        }
        arestaAtual = arestaAtual->prox;
    }

    // Adiciona a nova aresta
    NoAresta *novaAresta = new NoAresta(destino, peso);
    novaAresta->prox = verticeOrigem->arestas;
    verticeOrigem->arestas = novaAresta;

    // Se o grafo não é direcionado, adiciona a aresta inversa
    if (!direcionado)
    {
        NoVertice *verticeDestino = vertices.buscar_vertice(destino);
        if (!verticeDestino)
        {
            vertices.adicionar_vertice(destino);
            verticeDestino = vertices.buscar_vertice(destino);
        }

        // Verifica se a aresta inversa já existe
        arestaAtual = verticeDestino->arestas;
        while (arestaAtual)
        {
            if (arestaAtual->destino == origem)
            {
                // Aresta inversa já existe, não adiciona novamente
                return;
            }
            arestaAtual = arestaAtual->prox;
        }

        // Adiciona a nova aresta inversa
        NoAresta *novaArestaInversa = new NoAresta(origem, peso);
        novaArestaInversa->prox = verticeDestino->arestas;
        verticeDestino->arestas = novaArestaInversa;
    }

    ++num_arestas;
}


// Carrega o grafo a partir de um arquivo
void Grafo_Lista::carrega_grafo(const std::string &arquivo)
{
    std::ifstream inputFile(arquivo);
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Erro ao abrir o arquivo: " + arquivo);
    }

    std::string linha;

    // Lendo os metadados
    if (std::getline(inputFile, linha))
    {
        std::istringstream metaStream(linha);
        metaStream >> num_vertices >> direcionado >> peso_vertices >> peso_arestas;
    }

    // Se os vértices são ponderados, ler os pesos dos vértices
    if (peso_vertices && std::getline(inputFile, linha))
    {
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
    else
    {
        for (int i = 1; i <= num_vertices; ++i)
        {
            vertices.adicionar_vertice(i);
        }
    }

    // Lendo as arestas
    while (std::getline(inputFile, linha))
    {
        std::istringstream arestaStream(linha);
        int origem, destino, peso = 0;
        arestaStream >> origem >> destino;
        if (peso_arestas)
        {
            arestaStream >> peso;
        }
        adicionar_aresta(origem, destino, peso);
    }

    inputFile.close();
}

// Cria um novo grafo a partir de uma descrição
void Grafo_Lista::novo_grafo(const std::string &descricao, std::string &arquivo)
{
    // Implementação futura
}

// Implementação das funções abstratas
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

            while (inicio != fim) {
                int atual = fila[inicio++];
                int corAtual = cores[atual];
                NoVertice* verticeAtual = vertices.buscar_vertice(atual);

                for (NoAresta* aresta = verticeAtual->arestas; aresta; aresta = aresta->prox) {
                    int destino = aresta->destino;

                    if (cores[destino] == -1) {
                        cores[destino] = 1 - corAtual;
                        fila[fim++] = destino;
                    } else if (cores[destino] == corAtual) {
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

void Grafo_Lista::explorar_componente(int vertice_id, bool visitado[]) {
    visitado[vertice_id] = true;
    NoVertice* verticeAtual = vertices.buscar_vertice(vertice_id);
    if (!verticeAtual) return;

    for (NoAresta* aresta = verticeAtual->arestas; aresta; aresta = aresta->prox) {
        if (!visitado[aresta->destino]) {
            explorar_componente(aresta->destino, visitado);
        }
    }
}

int Grafo_Lista::n_conexo() {
    bool* visitado = new bool[num_vertices + 1]();
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

int Grafo_Lista::get_ordem()
{
    return num_vertices;
}

bool Grafo_Lista::eh_direcionado()
{
    return direcionado;
}

bool Grafo_Lista::vertice_ponderado()
{
    return peso_vertices;
}

bool Grafo_Lista::aresta_ponderada()
{
    return peso_arestas;
}

bool Grafo_Lista::eh_completo()
{
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

bool Grafo_Lista::eh_arvore() {
    return n_conexo() == 1 && num_arestas == num_vertices - 1;
}

void Grafo_Lista::dfs_articulacao(int u, bool visitado[], int discovery[], int low[], int parent[], bool& possui_articulacao, int& tempo) {
    visitado[u] = true;
    discovery[u] = low[u] = ++tempo;
    int filhos = 0;

    NoVertice* verticeAtual = vertices.buscar_vertice(u);
    if (!verticeAtual) {
        std::cerr << "Vértice " << u << " não encontrado durante a DFS.\n";
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

            // Verificar se a aresta (u-v) é uma ponte
            if (low[v] > discovery[u]) {
                possui_ponte = true;
            }
        }
        else if (v != parent[u]) {
            low[u] = std::min(low[u], discovery[v]);
        }
    }
}

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

void Grafo_Lista::exibe_descricao()
{
    std::cout << "Grau: " << get_grau() << std::endl;
    std::cout << "Ordem: " << get_ordem() << std::endl;
    std::cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Componentes conexas: " << n_conexo() << std::endl;
    std::cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Nao")
              << std::endl;
    std::cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Nao") << std::endl;
    std::cout << "Completo: " << (eh_completo() ? "Sim" : "Nao") << std::endl;
    std::cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Nao") << std::endl;
    std::cout << "Arvore: " << (eh_arvore() ? "Sim" : "Nao") << std::endl;
    std::cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Nao") << std::endl;
    std::cout << "Vertice de Articulacao: " << (possui_articulacao() ? "Sim" : "Nao") << std::endl;
}
