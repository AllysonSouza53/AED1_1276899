/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Allyson Kayk de Souza
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1383
Data        : 10/10/2026
Objetivo    : Verificar se uma entrada de Sudoku(matriz 9X9) está coerente as regras do jogo
Dificuldade : A parte dos grupos 3X3, onde tive que pensar mais na lógica
Uso de IA   : Interpretação do problema, consulta de linguagem e documentação
-------------------------------------------------------------------------- */


#include <stdio.h>

// Protótipo da função que verifica se o Sudoku é válido.
// Recebe uma matriz 9x9 e retorna:
// 1 se não encontrar números repetidos;
// 0 se encontrar alguma repetição.
int Verificar(int Matriz[9][9]);

int main()
{
    // NM armazena a quantidade de matrizes que serão verificadas.
    // sudoku armazena os 81 números de cada Sudoku.
    int NM, sudoku[9][9];

    // Lê a quantidade de instâncias (Sudokus) que serão analisadas.
    scanf("%d", &NM);

    // Repete o processo para cada Sudoku informado.
    for (int i = 0; i < NM; i++) {

        // Lê os 81 números da matriz, linha por linha.
        // j percorre as 9 linhas.
        // z percorre as 9 colunas de cada linha.
        for (int j = 0; j < 9; j++) {
            for (int z = 0; z < 9; z++) {
                scanf("%d", &sudoku[j][z]);
            }
        }

        // Imprime o número da instância que está sendo analisada.
        printf("Instancia %d\n", i + 1);

        // Chama a função que verifica linhas, colunas e grupos 3x3.
        // Se retornar 1, não foram encontradas repetições.
        if (Verificar(sudoku) == 1) {
            printf("SIM\n\n");
        } else {
            // Se retornar 0, foi encontrada alguma repetição.
            printf("NAO\n\n");
        }
    }

    return 0;
}

// Verifica se existem números repetidos nas linhas,
// nas colunas e nos nove grupos 3x3 do Sudoku.
int Verificar(int Matriz[9][9])
{
    // x controla a posição em que os elementos serão armazenados
    // no vetor auxiliar Linha3x3.
    // Linha3x3 armazenará temporariamente os 9 elementos de um grupo.
    int x, Linha3x3[9];

    // Percorre todas as linhas da matriz.
    for (int i = 0; i < 9; i++) {

        // Percorre todas as colunas da matriz.
        for (int j = 0; j < 9; j++) {

            // Compara o elemento atual com os elementos anteriores.
            // z começa em j-1 e percorre as posições anteriores.
            for (int z = j - 1; z >= 0; z--) {

                // VERIFICAÇÃO DAS LINHAS:
                // A linha i permanece fixa, enquanto j e z
                // representam colunas diferentes.
                // Se os valores forem iguais, existe repetição.
                if (Matriz[i][j] == Matriz[i][z]) {
                    return 0;
                }

                // VERIFICAÇÃO DAS COLUNAS:
                // A coluna i permanece fixa.
                // j e z representam linhas diferentes.
                // Se os valores forem iguais, existe repetição.
                if (Matriz[j][i] == Matriz[z][i]) {
                    return 0;
                }
            }

            // VERIFICAÇÃO DOS GRUPOS 3x3:
            // Os grupos começam nas linhas 0, 3 e 6
            // e nas colunas 0, 3 e 6.
            // Essa condição identifica o canto superior esquerdo
            // de cada um dos nove grupos.
            if ((i == 0 || i == 3 || i == 6) &&
                (j == 0 || j == 3 || j == 6)) {

                // Reinicia o índice para preencher o vetor
                // auxiliar desde a posição zero.
                x = 0;

                // Percorre as três linhas do grupo 3x3.
                for (int k = 0; k < 3; k++) {

                    // Percorre as três colunas do grupo 3x3.
                    for (int q = 0; q < 3; q++) {

                        // Copia cada elemento do grupo para o vetor.
                        // i+k percorre as linhas do grupo.
                        // j+q percorre as colunas do grupo.
                        // q+x determina a posição no vetor auxiliar.
                        Linha3x3[q + x] = Matriz[i + k][j + q];
                    }

                    // Avança três posições no vetor auxiliar
                    // para armazenar a próxima linha do grupo.
                    x = x + 3;
                }

                // Percorre os nove elementos armazenados no vetor.
                for (int y = 0; y < 9; y++) {

                    // Compara o elemento atual com todos os anteriores.
                    // Começa em y-1 para evitar comparar o elemento
                    // consigo mesmo e não repetir comparações.
                    for (int n = y - 1; n >= 0; n--) {

                        // Se dois elementos do mesmo grupo forem iguais,
                        // existe uma repetição e o Sudoku é inválido.
                        if (Linha3x3[y] == Linha3x3[n]) {
                            return 0;
                        }
                    }
                }
            }
        }
    }

    // Se todos os testes terminarem sem encontrar repetições,
    // a função retorna 1.
    return 1;
}
