#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H
#include "grafo.h"
#include <vector>

class Grafo_Matriz : public Grafo
{
private:
    int num_vertices;
    int num_arestas;
    bool direcionado;
    bool peso_vertices;
    bool peso_arestas;
    bool completo;
    bool bipartido;
    bool arvore;
    bool possui_ponte_flag;
    bool possui_articulacao_flag;
    int componentes_conexas;
    std::vector<std::vector<int>> matriz_adjacencia;
    std::vector<int> pesos_vertices;

public:
    Grafo_Matriz();
    ~Grafo_Matriz();
    // Implementação das funções abstratas
    bool eh_bipartido() override;
    int n_conexo() override;
    int get_grau() override;
    int get_ordem() override;
    bool eh_direcionado() override;
    bool vertice_ponderado() override;
    bool aresta_ponderada() override;
    bool eh_completo() override;
    bool eh_arvore() override;
    bool possui_articulacao() override;
    bool possui_ponte() override;
    void carrega_grafo(const std::string &arquivo) override;
    void novo_grafo(const std::string& descricao, std::string& arquivo) override;
    void exibe_descricao() override;
    // Funções auxiliares
    void inicializa_matriz();
    void adicionar_aresta(int origem, int destino, int peso = 0);
};
#endif //GRAFO_MATRIZ_H
