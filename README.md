# Trabalho de Teoria dos Grafos

## Integrantes do Grupo

- Nome do integrante 1: Lucas Henrique de Araujo Cardoso - 202135038
- Nome do integrante 2: Pedro Lucas Botelho Freitas - 202135040
- Nome do integrante 3: Julia Borges Beccari - 202135007

## Resumo do Projeto

Este repositório contém o trabalho da disciplina DCC059 - Teoria dos Grafos ministrada pelo Prof. Gabriel Souza no Departamento de Ciência da Computação da UFJF. O objetivo principal do projeto é implementar soluções gulosas, randomizadas e reativas que tentam solucionar 10 instâncias do problema da Cobertura de Vértices Mínima.

### Estruturas de Armazenamento
- **grafo_matriz**: Utiliza matriz de adjacência para representar arestas. Em grafos não direcionados, é utilizada a representação linear de uma matriz triangular. Tanto vértices quanto arestas são estáticos.
- **grafo_lista**: Utiliza lista encadeada tanto para vértices quanto para arestas, utilizando alocação dinâmica.

### Funcionalidades Implementadas
As seguintes funções são implementadas na classe abstrata:
- `cobertura_gulosa`: Verifica a cobertura de vértices mínima utilizando uma abordagem gulosa.
- `cobertura_randomizada`: Verifica a cobertura de vértices mínima utilizando uma abordagem randomizada.
- `cobertura_reativa`: Verifica a cobertura de vértices mínima utilizando uma abordagem reativa, mesclando entre gulosa e randomizada para obter o melhor resultado possível.

### Requisitos e Restrições
- O código deve seguir os princípios de Programação Orientada a Objetos, especialmente herança e encapsulamento.
- Bibliotecas permitidas são `fstream`, `iostream`, `iomanip`, `cmath`, `cstdlib`, `cstdarg`, `ctime`, `string`.
- Não são permitidas arestas múltiplas ou laços nos grafos.
- Documentação completa do código é exigida.

### Execução do Código
A aplicação deve ser compilada e executada via terminal com as seguintes linhas de comando:

#### Para compilar
`g++ -o main.out main.cpp src/*.cpp -I/.include/ -g -Wall -Werror`: Compila o projeto

#### Para executar
1. `time main.out -p -m grafo.txt`: Carrega o grafo usando matriz de adjacência.
2. `time main.out -p -l grafo.txt`: Carrega o grafo usando lista encadeada.

#### Para verificar vazamento de memória:
1. `valgrind main.out -p -m grafo.txt`: Verifica o vazamento de memória do grafo usando matriz de adjacência.
2. `valgrind main.out -p -l grafo.txt`: Verifica o vazamento de memória do grafo usando lista encadeada.

### Envios e Apresentação
O trabalho deve ser enviado em um arquivo zip contendo o código fonte, link para o projeto no GitHub, uma apresentação em PDF, documentação do código, e a identificação dos integrantes com suas contribuições. Haverá uma apresentação individual de 1 minuto por integrante na forma de elevator pitch, seguida por uma sessão de perguntas do professor.

### Avaliação
A avaliação do trabalho será realizada com base nos seguintes critérios:

1. **Apresentação (`A`)**: Avaliação da clareza, organização e objetividade na exposição do trabalho, incluindo explicação dos conceitos implementados e justificativa das escolhas feitas no código.
2. **Avaliação Geral do Trabalho (`T`)**: Considera a correta implementação dos algoritmos, a eficiência do código, a organização da estrutura do projeto e a aderência aos requisitos do trabalho.
3. **Participação no Desenvolvimento (`P`)**: Cada aluno será avaliado individualmente com base em sua contribuição no desenvolvimento do código, resolução de problemas e envolvimento no projeto.

A nota final será calculada utilizando a seguinte fórmula:
`Nota Final = A * T * P`

Onde:
- `A` → Nota da apresentação
- `T` → Nota geral do trabalho
- `P` → Nota da participação individual no desenvolvimento

##
**Departamento de Ciência da Computação - UFJF**
**DCC059 - Teoria dos Grafos**
**Prof. Gabriel Souza**
