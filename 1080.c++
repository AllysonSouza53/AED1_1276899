/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Allyson Kayk de Souza
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1383
Data        : 10/10/2026
Objetivo    : Encontrar entre 100 valores e a posição do maior e o maior
Dificuldade : A parte da atualização das variaveis
Uso de IA   : Interpretação do problema, consulta de linguagem e documentação
-------------------------------------------------------------------------- */

#include <iostream>
using namespace std;

int main() {
    int V[100], maior, posicao;

    // Lê o primeiro número e inicializa o maior valor.
    cin >> V[0];
    maior = V[0];
    posicao = 0;

    // Lê os outros 99 números.
    for (int n = 1; n < 100; n++) {
        cin >> V[n];

        // Atualiza o maior valor e sua posição, se necessário.
        if (V[n] > maior) {
            maior = V[n];
            posicao = n+1;
        }
    }

    // Exibe o maior valor e sua posição.
    cout << maior << "\n";
    cout << posicao << "\n";

    return 0;
}
