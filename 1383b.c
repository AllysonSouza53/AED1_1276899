/* --------------------------------------------------------------------------
Disciplina  : Algoritmos e Estruturas de Dados 2026S1
Nome        : Allyson Kayk de Souza
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1383
Data        : 10/10/2026
Objetivo    : Verificar se uma entrada de Sudoku (matriz 9x9) está de
              acordo com as regras do jogo.
Dificuldade : A verificação dos grupos 3x3, cuja lógica exigiu maior
              reflexão e elaboração.
Uso de IA   : Interpretação do problema, consulta de linguagem,
              documentação e testes.
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

// Protótipo da função que verifica se o Sudoku é válido.
// Recebe um ponteiro para ponteiro de inteiros, que representa
// a matriz alocada dinamicamente, e retorna:
// 1 se não encontrar números repetidos;
// 0 se encontrar alguma repetição.
int Verificar(int **Matriz);

int main()
{
    // sudoku é um ponteiro para ponteiro de inteiros.
    // Será utilizado para armazenar dinamicamente os elementos
    // da matriz 9x9.
    // NM armazena a quantidade de Sudokus que serão verificados.
    int **sudoku;
    int NM;

    // Aloca dinamicamente espaço para nove ponteiros de inteiros,
    // sendo cada ponteiro destinado a representar uma linha da matriz.
    sudoku = malloc(9 * sizeof(int *));

    // Verifica se a alocação do vetor de ponteiros foi bem-sucedida.
    // Caso contrário, encerra o programa indicando uma falha.
    if (sudoku == NULL) {
        return 1;
    }

    // Aloca dinamicamente espaço para nove inteiros em cada linha.
    // Ao final, a matriz terá nove linhas com nove elementos cada.
    for (int i = 0; i < 9; i++) {
        sudoku[i] = malloc(9 * sizeof(int));

        // Verifica se a alocação da linha atual foi bem-sucedida.
        // Se falhar, libera as linhas que já foram alocadas
        // e, em seguida, libera o vetor de ponteiros.
        if (sudoku[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(sudoku[j]);
            }

            free(sudoku);
            return 1;
        }
    }

    // Lê a quantidade de instâncias (Sudokus) que serão analisadas.
    scanf("%d", &NM);

    // Repete o processo de leitura e verificação para cada Sudoku.
    for (int i = 0; i < NM; i++) {

        // Lê os 81 números da matriz, linha por linha.
        // j percorre as nove linhas.
        // z percorre as nove colunas de cada linha.
        for (int j = 0; j < 9; j++) {
            for (int z = 0; z < 9; z++) {
                scanf("%d", &sudoku[j][z]);
            }
        }

        // Imprime o número da instância que está sendo analisada.
        // i + 1 é utilizado para numerar as instâncias a partir de 1.
        printf("Instancia %d\n", i + 1);

        // Chama a função responsável por verificar as linhas,
        // as colunas e os nove grupos 3x3 do Sudoku.
        // Se retornar 1, nenhuma repetição foi encontrada.
        if (Verificar(sudoku) == 1) {
            printf("SIM\n\n");
        } else {
            // Se retornar 0, alguma repetição foi encontrada.
            printf("NAO\n\n");
        }
    }

    // Libera individualmente a memória alocada para cada linha.
    // A memória das linhas deve ser liberada antes do vetor
    // de ponteiros que armazena seus endereços.
    for (int i = 0; i < 9; i++) {
        free(sudoku[i]);
    }

    // Libera a memória alocada para o vetor de ponteiros.
    free(sudoku);

    return 0;
}

// Verifica se existem números repetidos nas linhas,
// nas colunas e nos nove grupos 3x3 do Sudoku.
// Recebe um ponteiro para ponteiro de inteiros, permitindo
// acessar os elementos da matriz por meio de Matriz[i][j].
int Verificar(int **Matriz)
{
    // x controla a posição utilizada para preencher o vetor auxiliar.
    // Linha3x3 armazena temporariamente os nove elementos
    // de um dos grupos 3x3 do Sudoku.
    int x, Linha3x3[9];

    // Percorre todas as linhas da matriz.
    for (int i = 0; i < 9; i++) {

        // Percorre todas as colunas da matriz.
        for (int j = 0; j < 9; j++) {

            // Compara o elemento atual com os elementos anteriores.
            // z começa em j - 1 e percorre as posições anteriores
            // da linha e da coluna que estão sendo verificadas.
            for (int z = j - 1; z >= 0; z--) {

                // VERIFICAÇÃO DAS LINHAS:
                // A linha i permanece fixa, enquanto j e z
                // representam duas colunas diferentes dessa linha.
                // Se os valores forem iguais, existe repetição.
                if (Matriz[i][j] == Matriz[i][z]) {
                    return 0;
                }

                // VERIFICAÇÃO DAS COLUNAS:
                // A coluna i permanece fixa.
                // j e z representam duas linhas diferentes da coluna.
                // Se os valores forem iguais, existe repetição.
                if (Matriz[j][i] == Matriz[z][i]) {
                    return 0;
                }
            }

            // VERIFICAÇÃO DOS GRUPOS 3x3:
            // Os grupos começam nas linhas 0, 3 e 6
            // e nas colunas 0, 3 e 6.
            // A condição identifica o canto superior esquerdo
            // de cada um dos nove grupos.
            if ((i == 0 || i == 3 || i == 6) &&
                (j == 0 || j == 3 || j == 6)) {

                // Reinicia o índice auxiliar para preencher
                // o vetor Linha3x3 a partir da posição zero.
                x = 0;

                // Percorre as três linhas do grupo 3x3.
                for (int k = 0; k < 3; k++) {

                    // Percorre as três colunas do grupo 3x3.
                    for (int q = 0; q < 3; q++) {

                        // Copia cada elemento do grupo para o vetor.
                        // i + k identifica a linha atual do grupo.
                        // j + q identifica a coluna atual do grupo.
                        // q + x determina a posição do elemento
                        // no vetor auxiliar Linha3x3.
                        Linha3x3[q + x] = Matriz[i + k][j + q];
                    }

                    // Avança três posições no vetor auxiliar
                    // para armazenar os elementos da próxima linha
                    // do grupo 3x3.
                    x = x + 3;
                }

                // Percorre os nove elementos armazenados no vetor.
                for (int y = 0; y < 9; y++) {

                    // Compara o elemento atual com todos os anteriores.
                    // n começa em y - 1, evitando comparar o elemento
                    // consigo mesmo e repetindo apenas as comparações
                    // necessárias para encontrar números duplicados.
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

    // Se todas as verificações terminarem sem encontrar repetições,
    // retorna 1, indicando que o Sudoku passou pelos testes.
    return 1;
}
