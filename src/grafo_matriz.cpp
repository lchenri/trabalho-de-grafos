#include "../include/grafo_matriz.h"
#include <fstream>
#include <sstream>
#include <iostream>

Grafo_Matriz::Grafo_Matriz() : num_vertices(0), num_arestas(0), direcionado(false),

                               peso_vertices(false), peso_arestas(false), completo(false), bipartido(false),

                               arvore(false), possui_ponte_flag(false), possui_articulacao_flag(false),

                               componentes_conexas(0) {
}

// Destructor
Grafo_Matriz::~Grafo_Matriz() {}

void Grafo_Matriz::inicializa_matriz() {
	// Inicializa a matriz quadrada de tamanho num_vertices e atribui 0 para cada posição.
	for (int i = 0; i <= num_vertices; ++i) {
		for (int j = 0; j <= num_vertices; ++j) {
			matriz_adjacencia[i][j] = 0;
			matriz_ligacoes[i][j] = false;
		}
	}
}

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

// Carrega o grafo a partir de um arquivo
void Grafo_Matriz::carrega_grafo(const std::string& arquivo) {
	std::ifstream arquivo_entrada(arquivo);

	if (!arquivo_entrada.is_open()) {
		std::cerr << "Não foi possível abrir o arquivo." << std::endl;
	}

	arquivo_entrada >> num_vertices >> direcionado >> peso_vertices >> peso_arestas;
	inicializa_matriz();

	if (peso_vertices) {
		std::string linha;
		std::getline(arquivo_entrada, linha); // lê até o final da linha
		std::getline(arquivo_entrada, linha); // lê a linha com os pesos dos vértices
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

// Cria um novo grafo a partir de uma descricao
void Grafo_Matriz::novo_grafo(const std::string& descricao, std::string& arquivo) {
	// TODO: Implementar
}

//----------------------------------------------------------------------------------------------------------------------

// Implementa��o das fun��es abstratas
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
					if (matriz_ligacoes[u][v]) {
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

void Grafo_Matriz::dfs(int v, bool visitado[]) {
    visitado[v] = true;
    for (int u = 1; u <= num_vertices; ++u) {
        if (matriz_ligacoes[v][u] && !visitado[u]) {
            dfs(u, visitado);
        }
    }
}

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


int Grafo_Matriz::get_grau() {
	// Retorna o grau máximo do grafo
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

int Grafo_Matriz::get_ordem() {

	return num_vertices;

}

bool Grafo_Matriz::eh_direcionado() {

	return direcionado;

}

bool Grafo_Matriz::vertice_ponderado() {

	return peso_vertices;

}

bool Grafo_Matriz::aresta_ponderada() {

	return peso_arestas;

}

bool Grafo_Matriz::eh_completo()
{
	for (int i = 1; i <= num_vertices; i++)
		for (int j = 1; j <= num_vertices; j++)
		{
			if (matriz_ligacoes[i][j] == false && i != j)
				return false;
		}

	return true;

}

bool Grafo_Matriz::eh_arvore() {
	return n_conexo() == 1 && num_arestas == num_vertices - 1;
}

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

}