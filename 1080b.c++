/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Allyson Kayk de Souza
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1383
Data        : 10/10/2026
Objetivo    : Encontrar entre 100 valores e a posição do maior e o maior, usando malloc
Dificuldade : A parte da atualização das variaveis e o uso do malloc em si
Uso de IA   : Interpretação do problema, consulta de linguagem e documentação
-------------------------------------------------------------------------- */

#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    // Declaração das variáveis
    int *V, T, maior, posicao;

    // Leitura da quantidade de posições do vetor
    cout << "Digite a quantidade de posições desejadas: ";
    cin >> T;

    // Verifica se a quantidade informada é válida
    if (T <= 0) {
        cout << "Quantidade inválida";
        return 1;
    }

    // Aloca dinamicamente memória para T números inteiros
    V = (int *) malloc(T * sizeof(int));

    // Verifica se a alocação de memória foi bem-sucedida
    if (V == NULL) {
        cout << "Erro no malloc";
        return 1;
    }

    // Lê o primeiro elemento e inicializa o maior valor
    cout << "Digite o número desejado na posição 0: ";
    cin >> V[0];

    maior = V[0];
    posicao = 0;

    // Lê os elementos restantes e procura o maior número
    for (int n = 1; n < T; n++) {
        cout << "Digite o número desejado na posição " << n << ": ";
        cin >> V[n];

        // Compara o elemento atual com o maior encontrado até agora
        if (V[n] > maior) {
            maior = V[n];
            posicao = n;
        }
    }

    // Exibe o maior número e sua posição
    cout << "O maior número da sequência é: " << maior
         << "\nE sua posição é: " << posicao << "\n";

    // Libera a memória alocada dinamicamente
    free(V);

    return 0;
}
