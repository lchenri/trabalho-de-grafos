#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H
#include "grafo.h"
#define MAX_VERTICES 100

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
    int matriz_adjacencia[MAX_VERTICES][MAX_VERTICES];
    int matriz_ligacoes[MAX_VERTICES][MAX_VERTICES];
    int pesos_vertices[MAX_VERTICES];

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
    bool verifica_grau(int vertice, int grau_max) override;
    bool gerar_bipartido(int grau_max) override;
    void gerar_completo(int grau_max) override;
    void gerar_arvore(int grau_max) override;
    bool verifica_restricoes(int grau_max, int componentes, bool ponte_flag, bool articulacao_flag) override;
    void exibe_descricao() override;
    // Funções auxiliares
    void inicializa_matriz();
    void adicionar_aresta(int origem, int destino, int peso = 0);
    void dfs(int v, bool visitado[]);
    void dfs(int u, bool visitado[], int discovery[], int low[], int parent[], int& tempo, bool& possui_articulacao);
};
#endif //GRAFO_MATRIZ_H
