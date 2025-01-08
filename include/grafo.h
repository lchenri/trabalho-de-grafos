#ifndef GRAFO_H
#define GRAFO_H
#include <string>

class Grafo{
public:
    virtual ~Grafo() {}
    virtual bool eh_bipartido() = 0;
    virtual int n_conexo() = 0;
    virtual int get_grau() = 0;
    virtual int get_ordem() = 0;
    virtual bool eh_direcionado() = 0;
    virtual bool vertice_ponderado() = 0;
    virtual bool aresta_ponderada() = 0;
    virtual bool eh_completo() = 0;
    virtual bool eh_arvore() = 0;
    virtual bool possui_articulacao() = 0;
    virtual bool possui_ponte() = 0;
    virtual void carrega_grafo(const std::string &arquivo) = 0;
    virtual void novo_grafo(const std::string& descricao, std::string& arquivo) = 0;
    virtual void exibe_descricao() = 0;
    virtual bool verifica_grau(int vertice, int grau_max) = 0;
    virtual bool gerar_bipartido(int grau_max) = 0;
    virtual void gerar_completo(int grau_max) = 0;
    virtual bool verifica_restricoes(int grau_max, int componentes, bool ponte_flag, bool articulacao_flag) = 0;
    virtual void gerar_arvore(int grau_max) = 0;
};

#endif //GRAFO_H
