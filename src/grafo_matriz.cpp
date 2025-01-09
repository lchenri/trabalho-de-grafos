#include "../include/grafo_matriz.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

/**
* @file grafo_matriz.cpp
* @brief Função auxiliar do n_conexo para explorar um componente conexo de cada vez
*/

/**
* @brief Construtor padrão da classe grafo_matriz
*/
Grafo_Matriz::Grafo_Matriz() : num_vertices(0), num_arestas(0), direcionado(false),
                               peso_vertices(false), peso_arestas(false), completo(false), bipartido(false),
                               arvore(false), possui_ponte_flag(false), possui_articulacao_flag(false),
                               componentes_conexas(0) {
}

/**
* @brief Destrutor padrão da classe grafo_matriz
*/
Grafo_Matriz::~Grafo_Matriz() {}

/**
* @brief Função para inicializar a matriz de adjacência
*/
void Grafo_Matriz::inicializa_matriz() {
	for (int i = 0; i <= num_vertices; ++i) {
		for (int j = 0; j <= num_vertices; ++j) {
			matriz_adjacencia[i][j] = 0;
			matriz_ligacoes[i][j] = false;
		}
	}
}

/**
* @brief Função para adicionar uma aresta ao grafo
* @param origem Vértice de origem da aresta
* @param destino Vértice de destino da aresta
* @param peso Peso da aresta
*/
void Grafo_Matriz::adicionar_aresta(int origem, int destino, int peso) {
	if (eh_direcionado()) {
		matriz_adjacencia[origem][destino] = peso_arestas ? peso : 1;
		matriz_ligacoes[origem][destino] = true;
	} else {
		matriz_adjacencia[origem][destino] = peso_arestas ? peso : 1;
		matriz_adjacencia[destino][origem] = peso_arestas ? peso : 1;
		matriz_ligacoes[origem][destino] = true;
		matriz_ligacoes[destino][origem] = true;
	}
	num_arestas++;
}

/**
* @brief Função para carregar um grafo a partir de um arquivo
* @param arquivo Nome do arquivo de entrada
*/
void Grafo_Matriz::carrega_grafo(const std::string& arquivo) {
	std::ifstream arquivo_entrada(arquivo);

	if (!arquivo_entrada.is_open()) {
		std::cerr << "Nao foi possivel abrir o arquivo." << std::endl;
	}

	arquivo_entrada >> num_vertices >> direcionado >> peso_vertices >> peso_arestas;
	inicializa_matriz();

	if (peso_vertices) {
		std::string linha;
		std::getline(arquivo_entrada, linha);
		std::getline(arquivo_entrada, linha);
		std::istringstream iss(linha);
		int peso;
		size_t pesoCount = 0;
		while (iss >> peso) {
			this->pesos_vertices[0] = peso;
			pesoCount++;
		}
	}

	int origem, destino, peso;
	if (peso_arestas) {
		while (arquivo_entrada >> origem >> destino >> peso) {
			adicionar_aresta(origem, destino, peso);
		}
		return;
	}

	while (arquivo_entrada >> origem >> destino) {
		adicionar_aresta(origem, destino);
	}

}

/**
* @brief Função para verificar o grau do grafo
* @param vertice Vértice a ser verificado
* @param grau_max Grau máximo permitido
* @return Grau do vértice - true: grau menor que o máximo, false: caso contrário
*/
bool Grafo_Matriz::verifica_grau(int vertice, int grau_max) {
	int grau_atual = 0;
	for (int i = 1; i <= num_vertices; ++i) {
		if (matriz_ligacoes[vertice][i]) grau_atual++;
		if (direcionado && matriz_ligacoes[i][vertice]) grau_atual++;
	}
	return grau_atual < grau_max;
}

/**
* @brief Função para gerar um grafo bipartido
* @param grau_max Grau máximo permitido
* @return true: se foi possível criar o grafo bipartido, false: caso contrário
*/
bool Grafo_Matriz::gerar_bipartido(int grau_max) {
	int tamanho1 = (num_vertices + 1) / 2;
	int tamanho2 = num_vertices / 2;
	int* particao1 = new int[tamanho1];
	int* particao2 = new int[tamanho2];

	int indice1 = 0, indice2 = 0;

	for (int i = 1; i <= num_vertices; ++i) {
		if (i % 2 == 0) {
			particao1[indice1++] = i;
		} else {
			particao2[indice2++] = i;
		}
	}

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
void Grafo_Matriz::gerar_completo(int grau_max) {
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
void Grafo_Matriz::gerar_arvore(int grau_max) {
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
bool Grafo_Matriz::verifica_restricoes(int grau_max, int componentes, bool ponte_flag, bool articulacao_flag) {
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
void Grafo_Matriz::novo_grafo(const std::string &descricao, std::string &arquivo) {
    std::ifstream arquivo_descricao(descricao);
    if (!arquivo_descricao.is_open()) {
        std::cerr << "Nao foi possivel abrir o arquivo de descricao." << std::endl;
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

    inicializa_matriz();

	if (peso_vertices) {
		for (int i = 1; i <= num_vertices; ++i) {
			pesos_vertices[i] = rand() % 10 + 1;
		}
	}

    bool sucesso = false;
	if(arvore_flag){
		gerar_arvore(grau_max);
    	sucesso = eh_arvore();
	}
    else if (bipartido_flag) {
        sucesso = gerar_bipartido(grau_max);
    } else if (completo_flag) {
        gerar_completo(grau_max);
        sucesso = true;
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

    for (int i = 1; i <= num_vertices; ++i) {
        for (int j = 1; j <= num_vertices; ++j) {
            if (matriz_ligacoes[i][j]) {
                arquivo_saida << i << " " << j;
                if (peso_arestas) {
                    arquivo_saida << " " << matriz_adjacencia[i][j];
                }
                arquivo_saida << "\n";
            }
        }
    }
}

/**
* @brief Função para verificar se o grafo é bipartido
* @return true: se o grafo é bipartido, false: caso contrário
*/
bool Grafo_Matriz::eh_bipartido() {
	int cor[num_vertices + 1];
	for (int i = 0; i <= num_vertices; ++i) {
		cor[i] = -1;
	}

	int fila[num_vertices + 1];
	int inicio = 0, fim = 0;

	for (int i = 1; i <= num_vertices; ++i) {
		if (cor[i] == -1) {
			cor[i] = 0;
			fila[fim++] = i;

			while (inicio != fim) {
				int u = fila[inicio++];

				for (int v = 1; v <= num_vertices; ++v) {
					if (matriz_ligacoes[u][v] || (eh_direcionado() && matriz_ligacoes[v][u])) {
						if (cor[v] == -1) {
							cor[v] = 1 - cor[u];
							fila[fim++] = v;
						} else if (cor[v] == cor[u]) {
							bipartido = false;
							return bipartido;
						}
					}
				}
			}
		}
	}
	bipartido = true;
	return bipartido;
}

/**
* @brief Função auxiliar de busca por profundidade para o n_conexo
* @param v Vértice atual
* @param visitado Array de vértices visitados
 */
void Grafo_Matriz::dfs(int v, bool visitado[]) {
    visitado[v] = true;
    for (int u = 1; u <= num_vertices; ++u) {
        if (matriz_ligacoes[v][u] && !visitado[u]) {
            dfs(u, visitado);
        }
    }
}

/**
* @brief Função para verificar o número de componentes conexas do grafo
* @return Número de componentes conexas
*/
int Grafo_Matriz::n_conexo() {
	bool visitado[num_vertices + 1] = {false};
	int componentes = 0;

	for (int i = 1; i <= num_vertices; ++i) {
		if (!visitado[i]) {
			dfs(i, visitado);
			componentes++;
		}
	}

	componentes_conexas = componentes;
	return componentes_conexas;
}

/**
* @brief Função para verificar o grau do grafo
* @return Grau do grafo (grau máximo entre o grau de todos os vértices)
*/
int Grafo_Matriz::get_grau() {
	int grau_max = 0;
	for (int i = 1; i <= num_vertices; i++) {
		int grau = 0;
		for (int j = 1; j <= num_vertices; j++) {
			if (matriz_adjacencia[i][j] != 0)
				grau++;
		}
		grau_max = std::max(grau_max, grau);
	}
	return grau_max;
}

/**
* @brief Função para verificar a ordem do grafo
* @return Ordem do grafo (número de vértices)
*/
int Grafo_Matriz::get_ordem() {
	return num_vertices;
}

/**
* @brief Função para verificar se o grafo é direcionado
* @return true: se o grafo é direcionado, false: caso contrário
*/
bool Grafo_Matriz::eh_direcionado() {
	return direcionado;
}

/**
* @brief Função para verificar se o grafo possui vértices ponderados
* @return true: se o grafo possui vértices ponderados, false: caso contrário
*/
bool Grafo_Matriz::vertice_ponderado() {
	return peso_vertices;
}

/**
* @brief Função para verificar se o grafo possui arestas ponderadas
* @return true: se o grafo possui arestas ponderadas, false: caso contrário
*/
bool Grafo_Matriz::aresta_ponderada() {
	return peso_arestas;
}

/**
* @grief Função para verificar se o grafo é completo
* @return true: se o grafo é completo, false: caso contrário
*/
bool Grafo_Matriz::eh_completo() {
	for (int i = 1; i <= num_vertices; i++)
		for (int j = 1; j <= num_vertices; j++) {
			if (matriz_ligacoes[i][j] == false && i != j)
				return false;
		}
	return true;
}

/**
* @brief Função para verificar se o grafo é uma árvore
* @return true: se o grafo é uma árvore, false: caso contrário
*/
bool Grafo_Matriz::eh_arvore() {
	if (!direcionado) {
		return n_conexo() == 1 && num_arestas == (num_vertices - 1)*2;
	}
	return n_conexo() == 1 && num_arestas == num_vertices - 1;
}

/**
* @brief Função auxiliar para a busca em profundidade para verificar se o grafo possui vértices de articulação
* @param u Vértice atual
* @param visitado Array de vértices visitados
* @param discovery Array de descobertas
* @param low Array de valores low
* @param parent Array de pais
* @param tempo Tempo de descoberta
* @param possui_articulacao Flag para verificar se o grafo possui vértices de articulação
*/
void Grafo_Matriz::dfs(int u, bool visitado[], int discovery[], int low[], int parent[], int& tempo, bool& possui_articulacao) {
	visitado[u] = true;
	discovery[u] = low[u] = ++tempo;
	int filhos = 0;

	for (int v = 1; v <= num_vertices; ++v) {
		if (matriz_ligacoes[u][v]) {
			if (!visitado[v]) {
				filhos++;
				parent[v] = u;
				dfs(v, visitado, discovery, low, parent, tempo, possui_articulacao);

				low[u] = std::min(low[u], low[v]);

				if (parent[u] == -1 && filhos > 1)
					possui_articulacao = true;
				if (parent[u] != -1 && low[v] >= discovery[u])
					possui_articulacao = true;
			} else if (v != parent[u]) {
				low[u] = std::min(low[u], discovery[v]);
			}
		}
	}
}

/**
* @brief Função para verificar se o grafo possui vértices de articulação
* @return true: se o grafo possui vértices de articulação, false: caso contrário
*/
bool Grafo_Matriz::possui_articulacao() {
	bool visitado[num_vertices + 1] = {false};
	int discovery[num_vertices + 1];
	int low[num_vertices + 1];
	int parent[num_vertices + 1];

	for (int i = 0; i <= num_vertices; ++i) {
		discovery[i] = -1;
		low[i] = -1;
		parent[i] = -1;
	}

	bool possui_articulacao = false;
	int tempo = 0;

	for (int i = 1; i <= num_vertices; ++i) {
		if (!visitado[i]) {
			dfs(i, visitado, discovery, low, parent, tempo, possui_articulacao);
		}
	}

	possui_articulacao_flag = possui_articulacao;
	return possui_articulacao;
}

/**
* @brief Função para verificar se o grafo possui arestas pontes
* @return true: se o grafo possui arestas pontes, false: caso contrário
*/
bool Grafo_Matriz::possui_ponte() {
	int componentes_iniciais = n_conexo();
	for (int u = 1; u <= num_vertices; ++u) {
		for (int v = 1; v <= num_vertices; ++v) {
			if (matriz_ligacoes[u][v]) {
				matriz_ligacoes[u][v] = false;
				if (!eh_direcionado()) {
					matriz_ligacoes[v][u] = false;
				}
				int componentes_apos_remocao = n_conexo();
				matriz_ligacoes[u][v] = true;
				if (!eh_direcionado()) {
					matriz_ligacoes[v][u] = true;
				}
				if (componentes_apos_remocao > componentes_iniciais) {
					possui_ponte_flag = true;
					return true;
				}
			}
		}
	}
	possui_ponte_flag = false;
	return false;
}

/**
* @brief Função para exibir a descrição do grafo tanto em um documento quanto no console
*/
void Grafo_Matriz::exibe_descricao() {
	std::cout << "Grau: " << get_grau() << std::endl;
	std::cout << "Ordem: " << get_ordem() << std::endl;
	std::cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "Nao") << std::endl;
	std::cout << "Componentes conexas: " << n_conexo() << std::endl;
	std::cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Nao")<< std::endl;
	std::cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Nao") << std::endl;
	std::cout << "Completo: " << (eh_completo() ? "Sim" : "Nao") << std::endl;
	std::cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Nao") << std::endl;
	std::cout << "Arvore: " << (eh_arvore() ? "Sim" : "Nao") << std::endl;
	std::cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Nao") << std::endl;
	std::cout << "Vertice de Articulacao: " << (possui_articulacao() ? "Sim" : "Nao") << std::endl;

    std::ofstream arquivo_descricao("descricao_saida.txt");
    if (!arquivo_descricao.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo de descricao." << std::endl;
        return;
    }

    arquivo_descricao << "Grau: " << get_grau() << std::endl;
    arquivo_descricao << "Ordem: " << get_ordem() << std::endl;
    arquivo_descricao << "Direcionado: " << (eh_direcionado() ? "Sim" : "Nao") << std::endl;
    arquivo_descricao << "Componentes conexas: " << n_conexo() << std::endl;
    arquivo_descricao << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Nao") << std::endl;
    arquivo_descricao << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Nao") << std::endl;
    arquivo_descricao << "Completo: " << (eh_completo() ? "Sim" : "Nao") << std::endl;
    arquivo_descricao << "Bipartido: " << (eh_bipartido() ? "Sim" : "Nao") << std::endl;
    arquivo_descricao << "Arvore: " << (eh_arvore() ? "Sim" : "Nao") << std::endl;
    arquivo_descricao << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Nao") << std::endl;
    arquivo_descricao << "Vertice de Articulacao: " << (possui_articulacao() ? "Sim" : "Nao") << std::endl;

    arquivo_descricao.close();

}