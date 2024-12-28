#pragma once
#ifndef GRAFO_H

#define GRAFO_H

#include <string>

class Grafo {

public:

	virtual ~Grafo() {}

	// Verifica se o grafo � bipartido

	virtual bool eh_bipartido() = 0;

	// Retorna o n�mero de componentes conexas

	virtual int n_conexo() = 0;

	// Retorna o grau do grafo

	virtual int get_grau() = 0;

	// Retorna a ordem do grafo

	virtual int get_ordem() = 0;

	// Verifica se o grafo � direcionado

	virtual bool eh_direcionado() = 0;

	// Verifica se os v�rtices possuem peso

	virtual bool vertice_ponderado() = 0;

	// Verifica se as arestas possuem peso

	virtual bool aresta_ponderada() = 0;

	// Verifica se o grafo � completo

	virtual bool eh_completo() = 0;

	// Verifica se o grafo � uma �rvore

	virtual bool eh_arvore() = 0;

	// Verifica se existe v�rtice de articula��o

	virtual bool possui_articulacao() = 0;

	// Verifica se existe aresta ponte

	virtual bool possui_ponte() = 0;

	// Carrega o grafo a partir de um arquivo

	virtual void carrega_grafo(const std::string& arquivo) = 0;

	// Cria um novo grafo a partir de uma descri��o

	virtual void novo_grafo(const std::string& descricao, const std::string& arquivo) = 0;

	// Exibe a descri��o do grafo

	virtual void exibe_descricao() = 0;

};

#endif // GRAFO_H