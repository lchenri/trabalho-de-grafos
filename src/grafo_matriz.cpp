#include "../include/grafo_matriz.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>
#include <functional>
#include <random>
#include <algorithm>


Grafo_Matriz::Grafo_Matriz() : num_vertices(0), num_arestas(0), direcionado(false),

                               peso_vertices(false), peso_arestas(false), completo(false), bipartido(false),

                               arvore(false), possui_ponte_flag(false), possui_articulacao_flag(false),

                               componentes_conexas(0) {
}

// Destructor
Grafo_Matriz::~Grafo_Matriz() {}

void Grafo_Matriz::inicializa_matriz() {
	// Inicializa a matriz quadrada de tamanho num_vertices e atribui 0 para cada posição.
	matriz_adjacencia.resize(num_vertices+1, std::vector<int>(num_vertices+1, 0));
	matriz_ligacoes.resize(num_vertices+1, std::vector<bool>(num_vertices+1, false));
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
		while (iss >> peso) {
			this->pesos_vertices.push_back(peso);
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

// Função auxiliar para verificar grau
bool Grafo_Matriz::verifica_grau(int vertice, int grau_max) {
	int grau_atual = 0;
	for (int i = 1; i <= num_vertices; ++i) {
		if (matriz_ligacoes[vertice][i]) grau_atual++;
		if (direcionado && matriz_ligacoes[i][vertice]) grau_atual++;
	}
	return grau_atual < grau_max;
}

// Função auxiliar para criar um grafo bipartido
bool Grafo_Matriz::gerar_bipartido(int grau_max) {

	//TODO : nao verifica componente conexo nem arestas pontes e vertice articulacao
    std::vector<int> particao1, particao2;

    // Dividir vértices em duas partições
    for (int i = 1; i <= num_vertices; ++i) {
        if (i % 2 == 0) particao1.push_back(i);
        else particao2.push_back(i);
    }

    // Conectar vértices entre partições respeitando o grau máximo
    for (int u : particao1) {
        for (int v : particao2) {
            if (verifica_grau(u, grau_max) && verifica_grau(v, grau_max)) {
                adicionar_aresta(u, v, peso_arestas ? rand() % 20 - 10 : 1);
            	std::cout << "u: " << u << " v: " << v << std::endl;
            }
        }
    }
    return eh_bipartido();
}

// Função auxiliar para criar um grafo completo
void Grafo_Matriz::gerar_completo(int grau_max) {
    for (int i = 1; i <= num_vertices; ++i) {
        for (int j = i + 1; j <= num_vertices; ++j) {
            if (direcionado || (verifica_grau(i, grau_max) && verifica_grau(j, grau_max))) {
                adicionar_aresta(i, j, peso_arestas ? rand() % 20 - 10 : 1);
                if (!direcionado) adicionar_aresta(j, i, peso_arestas ? rand() % 20 - 10 : 1);
            }
        }
    }
}

bool Grafo_Matriz::verifica_restricoes(int grau_max, int componentes, bool ponte_flag, bool articulacao_flag) {
	if (n_conexo() != componentes) return false;
	if (ponte_flag && !possui_ponte()) return false;
	if (articulacao_flag && !possui_articulacao()) return false;
	for (int i = 1; i <= num_vertices; ++i) {
		if (!verifica_grau(i, grau_max)) return false;
	}
	return true;
}


// Função principal
void Grafo_Matriz::novo_grafo(const std::string &descricao, std::string &arquivo) {
    // Abre o arquivo de descrição
    std::ifstream arquivo_descricao(descricao);
    if (!arquivo_descricao.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo de descrição." << std::endl;
        return;
    }

    // Lê os parâmetros do arquivo
    int grau_max, ordem, direcionado_flag, componentes, vertices_ponderados_flag,
        arestas_ponderadas_flag, completo_flag, bipartido_flag, arvore_flag,
        ponte_flag, articulacao_flag;

    arquivo_descricao >> grau_max >> ordem >> direcionado_flag >> componentes;
    arquivo_descricao >> vertices_ponderados_flag >> arestas_ponderadas_flag;
    arquivo_descricao >> completo_flag >> bipartido_flag >> arvore_flag;
    arquivo_descricao >> ponte_flag >> articulacao_flag;

    // Inicializa atributos
    num_vertices = ordem;
    num_arestas = 0;
    direcionado = direcionado_flag;
    peso_vertices = vertices_ponderados_flag;
    peso_arestas = arestas_ponderadas_flag;

    inicializa_matriz();

    // Gera pesos dos vértices, se necessário
    if (peso_vertices) {
        pesos_vertices.resize(num_vertices + 1);
        for (int i = 1; i <= num_vertices; ++i) {
            pesos_vertices[i] = rand() % 10 + 1;
        }
    }

    // Gera o grafo com base nas restrições
    bool sucesso = false;
    if (bipartido_flag) {
        sucesso = gerar_bipartido(grau_max);
    } else if (completo_flag) {
        gerar_completo(grau_max);
        sucesso = true;
    } else if (arvore_flag) {
    	//TODO: passar isso para uma função a parte e tambem dar suporte a grafos nao direcionados eu acho

    	// Gera uma árvore conectada respeitando o grau máximo
    	for (int i = 2; i <= num_vertices; ++i) {
    		int origem;
    		do {
    			origem = rand() % (i - 1) + 1;
    		} while (!verifica_grau(origem, grau_max));
    		adicionar_aresta(origem, i, peso_arestas ? rand() % 20 - 10 : 1);
    	}
        sucesso = eh_arvore();
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
        std::cerr << "Não foi possível gerar o grafo com as restrições fornecidas." << std::endl;
        return;
    }

    // Salva o grafo no arquivo de saída
    std::ofstream arquivo_saida(arquivo);
    if (!arquivo_saida.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo de saída." << std::endl;
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


//----------------------------------------------------------------------------------------------------------------------

// Implementa��o das fun��es abstratas
bool Grafo_Matriz::eh_bipartido() {

	std::vector<int> cor(num_vertices + 1, -1);
	std::queue<int> fila;

	for (int i = 1; i <= num_vertices; ++i) {
		if (cor[i] == -1) {
			cor[i] = 0;
			fila.push(i);

			while (!fila.empty()) {
				int u = fila.front();
				fila.pop();

				for (int v = 1; v <= num_vertices; ++v) {
					if (matriz_ligacoes[u][v]) {
						if (cor[v] == -1) {
							cor[v] = 1 - cor[u];
							fila.push(v);
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

int Grafo_Matriz::n_conexo() {
	std::vector<bool> visitado(num_vertices + 1, false);
	std::function<void(int)> dfs = [&](int v) {
		visitado[v] = true;
		for (int u = 1; u <= num_vertices; ++u) {
			if (matriz_ligacoes[v][u] && !visitado[u]) {
				dfs(u);
			}
		}
	};

	int componentes = 0;
	for (int i = 1; i <= num_vertices; ++i) {
		if (!visitado[i]) {
			dfs(i);
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
	//TODO: nao está tratando casos de grafo nao direcionado, somente direcionado
	return n_conexo() == 1 && num_arestas == num_vertices - 1;
}

bool Grafo_Matriz::possui_articulacao() {
	std::vector<bool> visitado(num_vertices + 1, false);
	std::vector<int> discovery(num_vertices + 1, -1);
	std::vector<int> low(num_vertices + 1, -1);
	std::vector<int> parent(num_vertices + 1, -1);
	bool possui_articulacao = false;

	std::function<void(int, int&)> dfs = [&](int u, int& tempo) {
		visitado[u] = true;
		discovery[u] = low[u] = ++tempo;
		int filhos = 0;

		for (int v = 1; v <= num_vertices; ++v) {
			if (matriz_ligacoes[u][v]) {
				if (!visitado[v]) {
					filhos++;
					parent[v] = u;
					dfs(v, tempo);

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
	};

	int tempo = 0;
	for (int i = 1; i <= num_vertices; ++i) {
		if (!visitado[i]) {
			dfs(i, tempo);
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