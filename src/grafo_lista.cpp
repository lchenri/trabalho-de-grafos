#include "../include/grafo_lista.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

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
bool Grafo_Lista::eh_bipartido()
{
    // Implementar
    return true;
}

int Grafo_Lista::n_conexo()
{
    // Implementar
    return 1;
}

int Grafo_Lista::get_grau()
{
    // Implementar
    return 1;
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
    // Implementar
    return true;
}

bool Grafo_Lista::eh_arvore()
{
    // Implementar
    return true;
}

bool Grafo_Lista::possui_articulacao()
{
    // Implementar
    return false;
}

bool Grafo_Lista::possui_ponte()
{
    // Implementar
    return false;
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
