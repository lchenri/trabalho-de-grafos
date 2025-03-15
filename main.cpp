#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <climits>

#include "include/grafo_lista.h"
#include "include/grafo_matriz.h"

/**
 * @file main.cpp
 * @brief Programa principal.
 */

using namespace std;

/*
* @brief Exibe a mensagem de uso do programa.
*/
void exibir_uso() {
    cout << "Uso:\n";
    cout << "Descrição do grafo:\n";
    cout << "  main.out -d -m grafo.txt\n";
    cout << "  main.out -d -l grafo.txt\n";
    cout << "Resolver problema de cobertura:\n";
    cout << "  main.out -p -m grafo.txt\n";
    cout << "  main.out -p -l grafo.txt\n";
}

/**
 * @brief Valida os argumentos passados para o programa.
 * @param argc Número de argumentos.
 * @param argv Array de argumentos.
 * @return true se os argumentos são válidos, false caso contrário.
 */
bool validar_argumentos(int argc, char *argv[]) {
    if (argc != 4) {
        exibir_uso();
        return false;
    }

    const string modo = argv[1];
    if (modo != "-d" && modo != "-p") {
        exibir_uso();
        return false;
    }

    const string estrutura = argv[2];
    if (estrutura != "-m" && estrutura != "-l") {
        exibir_uso();
        return false;
    }

    return true;
}

/**
 * @brief Executa o algoritmo de cobertura selecionado.
 * @param g Ponteiro para o grafo.
 */
void executar_cobertura(grafo* g) {
    int escolha;
    cout << "\nSelecione o algoritmo:\n";
    cout << "1 - Guloso\n";
    cout << "2 - Randomizado\n";
    cout << "3 - Reativo\n";
    cout << "Digite sua escolha (1-3): ";
    cin >> escolha;

    int tamanho;
    int* cobertura = nullptr;
    clock_t inicio = clock();

    switch(escolha) {
        case 1:
            cobertura = g->cobertura_gulosa(&tamanho);
        break;
        case 2:
            cobertura = g->cobertura_randomizada(&tamanho);
        break;
        case 3:
            cobertura = g->cobertura_reativa(&tamanho);
        break;
        default:
            cout << "Opção inválida!\n";
        return;
    }

    double tempo = double(clock() - inicio) / CLOCKS_PER_SEC;

    cout << "\nCobertura encontrada\n";
    for(int i = 0; i < tamanho; i++) {
        cout << cobertura[i] << " ";
    }
    cout << "\n\nTamanho da cobertura: " << tamanho;
    cout << "\nTempo de execução: " << tempo << "s\n\n";

    delete[] cobertura;
}

/**
 * @brief Função principal.
 * @param argc Número de argumentos.
 * @param argv Array de argumentos.
 * @return 0 se o programa foi executado com sucesso, 1 caso contrário.
 */
int main(int argc, char *argv[]) {
    if (!validar_argumentos(argc, argv)) {
        return 1;
    }

    const string modo = argv[1];
    const string estrutura = argv[2];
    const string arquivo = argv[3];

    grafo* g = nullptr;

    try {
        if(estrutura == "-m") {
            g = new grafo_matriz();
        } else {
            g = new grafo_lista();
        }

        g->carrega_grafo(arquivo);

        if(modo == "-d") {
            g->exibe_descricao();
        } else {
            executar_cobertura(g);
        }

        delete g;
    }
    catch(const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        if(g) delete g;
        return 1;
    }

    return 0;
}