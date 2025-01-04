#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H
#include <unordered_map>

#include "grafo.h"
#include "lista_encadeada.h"

class Grafo_Lista : public Grafo
{
    private:
        ListaVertices vertices;
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

    public:
        Grafo_Lista();
        ~Grafo_Lista();
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
        void adicionar_aresta(int origem, int destino, int peso = 0);
        void explorar_componente(int vertice_id, std::unordered_map<int, bool>& visitado);
        void dfs_articulacao(int u, std::unordered_map<int, bool>& visitado,
                                std::unordered_map<int, int>& discovery, std::unordered_map<int, int>& low,
                                std::unordered_map<int, int>& parent, bool& possui_articulacao, int& tempo);
        void dfs_ponte(int u, std::unordered_map<int, bool>& visitado,
                            std::unordered_map<int, int>& discovery,
                            std::unordered_map<int, int>& low,
                            std::unordered_map<int, int>& parent,
                            bool& possui_ponte, int& tempo);
};
#endif // GRAFO_LISTA_H