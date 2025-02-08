#include <iostream>
#include <string>
#include <fstream>

#include "include/grafo_lista.h"
#include "include/grafo_matriz.h"
/**
* @file main.cpp
* @brief Arquivo principal do programa
*/

/**
* @brief Função para exibir como utilizar o programa
* @details Caso o usuário não forneça argumentos válidos, exibe como utilizar o programa
*/
void exibir_uso() {
    std::cout << "Uso:\n";
    std::cout << "Caso 1: main.out -d -m grafo.txt\n";
    std::cout << "Caso 2: main.out -d -l grafo.txt\n";
    std::cout << "Caso 3: main.out -c -m descricao.txt grafo.txt\n";
    std::cout << "Caso 4: main.out -c -l descricao.txt grafo.txt\n";
}

/**
* @brief Função para validar os argumentos fornecidos pelo usuário
* @param argc Número de argumentos
* @param argv Vetor de argumentos
* @return true: se os argumentos são válidos, false: caso contrário
*/
bool validar_argumentos(int argc, char *argv[]) {
    if (argc < 4) {
        exibir_uso();
        return false;
    }

    if (const std::string modo = argv[1];modo == "-c" && argc < 5) {
        exibir_uso();
        return false;
    }

    return true;
}

/**
 * @brief Função principal do programa
 * @param argc Número de argumentos
 * @param argv Vetor de argumentos
 * @return 0 se o programa foi executado com sucesso, 1 caso contrário
 */
int main(int argc, char *argv[]) {
    if (!validar_argumentos(argc, argv)) {
        return 1;
    }

    const std::string modo = argv[1];
    const std::string estrutura = argv[2];

    if (modo == "-d") {
        const std::string arquivo = argv[3];
        if (estrutura == "-m") {
            grafo_matriz grafo;
            grafo.carrega_grafo(arquivo);
            grafo.exibe_descricao();
        } else if (estrutura == "-l") {
            grafo_lista grafo;
            grafo.carrega_grafo(arquivo);
            grafo.exibe_descricao();
        } else {
            exibir_uso();
            return 1;
        }
    }
    else {
        exibir_uso();
        return 1;
    }
    return 0;
}