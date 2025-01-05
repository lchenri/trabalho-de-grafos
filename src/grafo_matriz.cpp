#include "../include/grafo_matriz.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>
#include <functional>
#include <random>

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

	// TODO: implementar caso da aresta nao ser ponderada e tambem de ter vertices ponderados
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

	int origem, destino;
	if (peso_arestas) {
		int peso;
		while (arquivo_entrada >> origem >> destino >> peso) {
			adicionar_aresta(origem, destino, peso);
		}
		return;
	}

	while (arquivo_entrada >> origem >> destino) {
		adicionar_aresta(origem, destino);
	}

}

int numero_aleatorio(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

bool aresta_existe(const std::vector<std::vector<int>> & matriz, int origem, int destino, bool direcionado) {
	// se destino menor que 1 ou maior que o tamanho da matriz, retorna falso
	if (destino < 1 || destino > matriz.size())
		return false;

	// se origem destino for diferente de 0, retorna verdadeiro (aresta existe)
	if (matriz[origem][destino] != 0) return true;

	if (!direcionado && matriz[destino][origem] != 0) return true;

	return false;

}

// Cria um novo grafo a partir de uma descricao
void Grafo_Matriz::novo_grafo(const std::string& descricao, std::string& arquivo) {
	int grau;
	int ordem;
	bool direcionado;
	int componentes_conexas;
	bool vertices_ponderados;
	bool arestas_ponderadas;
	bool completo;
	bool bipartido;
	bool arvore;
	bool possui_ponte;
	bool possui_articulacao;

	std::ifstream arquivo_descricao(descricao);

	if (!arquivo_descricao.is_open()) {
		std::cerr << "Não foi possível abrir o arquivo." << std::endl;
	}

	arquivo_descricao >> grau >> ordem >> direcionado >> componentes_conexas >> vertices_ponderados
	>> arestas_ponderadas >> completo >> bipartido >> arvore >> possui_ponte >> possui_articulacao;

	// instancia grafo
	this->num_vertices = ordem;
	this->direcionado = direcionado;
	this->peso_vertices = vertices_ponderados;
	this->peso_arestas = arestas_ponderadas;
	this->completo = completo;
	this->bipartido = bipartido;

	inicializa_matriz();

	// adiciona peso nos vértices caso a flag de peso seja verdadeira
	if (peso_vertices) {
		for (int i = 1; i <= num_vertices; i++) {
			int peso = numero_aleatorio(1,10);
			pesos_vertices.push_back(peso);
		}
	}

	// conexidade
	int componentes = componentes_conexas;
	if (componentes_conexas > ordem) {
		std::cerr << "Número de componentes conexas maior que a ordem do grafo." << std::endl;
		return;
	}

	// A ideia de conexidade é dividir os vértices em componentes conexas
	// e adicionar arestas entre os vértices de componentes conexas diferentes
	// para garantir que o grafo seja conexo.
	// A divisão dos vértices é feita de forma simples. Os vértices são divididos
	// de formas iguais entre as componentes conexas.


	// força as conexões para atender o grau máximo do grafo
	// TODO FIX ME - não está funcionando corretamente
	// for (size_t i = 1; i < componente.size(); i++) {
	// 	int tries = 0;
	// 	while (get_grau() < grau) {
	// 		int destino = numero_aleatorio(1, num_vertices);
	// 		if (destino != componente[i] && !aresta_existe(matriz_adjacencia, componente[i], destino, direcionado)) {
	// 			int peso = aresta_ponderada() ? numero_aleatorio(1,10) : 1;
	// 			adicionar_aresta(componente[i], destino, peso);
	// 		}
	// 		tries++;
	// 		if (get_grau() >= grau) break;
	// 		if (tries >10) break;
	// 	}
	// }
	std::vector<std::vector<int>> componentes_conexas_vertices(componentes_conexas+1, std::vector<int>());
	// int atual = 0;
	int atual = 1;
	for (int i = 1; i <= num_vertices; i++) {
		componentes_conexas_vertices[atual].push_back(i);
		// estratégia pra dividir
		atual = (atual + 1) % componentes_conexas;
	}

	for (const auto& componente : componentes_conexas_vertices) {
		// adiciona arestas entre os vértices da componente conexa
		for (size_t i = 1; i < componente.size(); i++) {
			int origem = componente[i-1];
			int destino = componente[i];
			int peso = aresta_ponderada() ? numero_aleatorio(1,10) : 1;
			adicionar_aresta(origem, destino, peso);
		}
	}

	if (possui_ponte) {
		// Precisa verificar se remover uma aresta desconecta o grafo
		// Se sim, a aresta é ponte
		// Se não, tenta outra aresta

		// Conectar dois componentes com uma única aresta se numero de componentes for maior que 1
		if (componentes_conexas > 1) {
			// cria uma ponte
			adicionar_aresta(componentes_conexas_vertices[1][1], componentes_conexas_vertices[2][1], aresta_ponderada() ? numero_aleatorio(1,10) : 1);

			//remove uma componente conexa já que foi conectado
			componentes_conexas--;
		}
	}

	if (possui_articulacao) {
		// Adiciona um vértice de articulação
		// Um vértice de articulação é um vértice que, se removido, aumenta o número de componentes conexas

		// Escolher o primeiro vértice e conectar várias partes a ele

		if (num_vertices >= 3) {
			int articulacao = componentes_conexas_vertices[1][0];

			// conectar o vértice a 2 outros não diretamente conectados?????
			adicionar_aresta(articulacao, componentes_conexas_vertices[1][1], aresta_ponderada() ? numero_aleatorio(1,10) : 1);
			adicionar_aresta(articulacao, componentes_conexas_vertices[2][1], aresta_ponderada() ? numero_aleatorio(1,10) : 1);
		}
	}

	// bipartição
	if (bipartido) {
		// Dividir os vértices em dois conjuntos

		std::vector<int> conjunto1;
		std::vector<int> conjunto2;

		for (int i = 1; i <= num_vertices; i++) {
			if (i % 2 == 0)
				conjunto1.push_back(i);
			else
				conjunto2.push_back(i);
		}

		// conectar vértices de conjuntos diferentes pra garantir bipartição
		for (const auto& u : conjunto1) {
			for (const auto& v : conjunto2) {
				if (aresta_existe(matriz_adjacencia, u, v, direcionado)) {
					if (numero_aleatorio(0,1)) {
						int peso = aresta_ponderada() ? numero_aleatorio(1,10) : 1;
						adicionar_aresta(u, v, peso);
					}
				}
			}
		}
	}


	// Arvore
	if (!arvore) {
		// adiciona arestas para evitar que seja árvore
		// Uma árvore tem n-1 arestas. Precisa ter mais que isso
		if (num_arestas < num_vertices) {
			while (num_arestas < num_vertices + 1) {
				int origem = numero_aleatorio(1, num_vertices);
				int destino = numero_aleatorio(1, num_vertices);

				if (origem != destino && !aresta_existe(matriz_adjacencia, origem, destino, direcionado)) {
					int peso = aresta_ponderada() ? numero_aleatorio(1,10) : 1;
					adicionar_aresta(origem, destino, peso);
				}
			}
		}
	}

	std::ofstream arquivo_saida(arquivo);

	if (!arquivo_saida.is_open()) {

		std::cerr << "Não foi possível abrir o arquivo para salvar o grafo." << std::endl;

		return;

	}

	// Escrever as propriedades básicas

	arquivo_saida << num_vertices << " "

	<< (direcionado ? "1" : "0") << " "

	<< (peso_vertices ? "1" : "0") << " "

	<< (aresta_ponderada() ? "1" : "0") << "\n";

	// Escrever os pesos dos vértices, se houver

	if (peso_vertices) {

		for (const auto& peso : pesos_vertices) {

			arquivo_saida << peso << " ";

		}

		arquivo_saida << "\n";

	}

	// Escrever as arestas

	for (int i = 1; i <= num_vertices; ++i) {

		for (int j = 1; j <= num_vertices; ++j) {

			if (matriz_ligacoes[i][j]) {

				if (aresta_ponderada())

					arquivo_saida << i << " " << j << " " << matriz_adjacencia[i][j] << "\n";

				else

					arquivo_saida << i << " " << j << "\n";

			}

		}

	}

	arquivo_saida.close();

	std::cout << "Novo grafo criado e salvo em " << arquivo << " usando matriz de adjacência" << std::endl;



	std::string foo = "foo";
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
	// Todo Revisar
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