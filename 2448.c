/* --------------------------------------------------------------------------
Disciplina  : Algoritmos e Estruturas de Dados 2026S1
Nome        : Allyson Kayk de Souza
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/2448
Data        : 12/10/2026
Objetivo    : determinar quanto tempo o carteiro levará para entregar todas as encomendas
Dificuldade : Entender a busca binaria e contruir o laço para calcular o tempo
Uso de IA   : Interpretação do problema, consulta de linguagem, documentação e 
              coreção de erros de escrita
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

// Protótipos das funções utilizadas no programa.
int CalculateDeliveryTime(int *Casas, int *Entregas, int QtdEntregas, int QtdCasas);
int CalculateTimeVariation(int origem, int destino);
int FindingHome(int Entrega, int QtdCasas, int *Casas);

int main()
{
    int N, M;
    int *Casas, *Entregas;

    // Lê a quantidade de casas (N) e a quantidade de entregas (M).
    scanf("%d %d", &N, &M);

    // Aloca dinamicamente a memória necessária para os dois vetores.
    Casas = (int *)malloc(N * sizeof(int));
    Entregas = (int *)malloc(M * sizeof(int));

    // Verifica se a alocação de memória foi realizada corretamente.
    // Caso alguma alocação falhe, libera a memória e encerra o programa.
    if (Casas == NULL || Entregas == NULL) {
        free(Casas);
        free(Entregas);
        return 1;
    }

    // Lê os números das casas em ordem crescente.
    for (int i = 0; i < N; i++) {
        scanf("%d", &Casas[i]);
    }

    // Lê os números das casas onde as entregas serão realizadas,
    // respeitando a ordem em que o carteiro deve executá-las.
    for (int i = 0; i < M; i++) {
        scanf("%d", &Entregas[i]);
    }

    // Calcula o tempo total necessário para realizar as entregas.
    int TempoPercurso = CalculateDeliveryTime(Casas, Entregas, M, N);

    // Exibe o tempo total do percurso.
    printf("%d\n", TempoPercurso);

    // Libera a memória alocada dinamicamente antes de encerrar.
    free(Casas);
    free(Entregas);

    return 0;
}

/*
 * Calcula o tempo total necessário para realizar todas as entregas.
 *
 * Casas: vetor com os números das casas, ordenados crescentemente.
 * Entregas: vetor com os destinos das entregas, na ordem de execução.
 * QtdEntregas: quantidade de entregas.
 * QtdCasas: quantidade de casas existentes.
 *
 * Retorna o tempo total do percurso.
 */
int CalculateDeliveryTime(int *Casas, int *Entregas, int QtdEntregas, int QtdCasas)
{
    // Encontra a posição da primeira casa de entrega.
    // O +1 converte o índice do vetor (iniciado em zero)
    // para a posição do percurso (iniciada em um).
    int CasaInc = FindingHome(Entregas[0], QtdCasas, Casas) + 1;

    // Calcula o tempo desde a primeira casa do percurso (posição 1)
    // até o primeiro destino.
    int TempoPercurso = CalculateTimeVariation(1, CasaInc);

    // Percorre as entregas restantes, começando pela segunda,
    // pois a primeira já foi contabilizada.
    for (int i = 1; i < QtdEntregas; i++) {

        // Encontra a posição da casa correspondente à entrega atual.
        int CasaFim = FindingHome(Entregas[i], QtdCasas, Casas) + 1;

        // Soma o tempo de deslocamento entre a posição atual
        // e a posição do próximo destino.
        TempoPercurso += CalculateTimeVariation(CasaInc, CasaFim);

        // Atualiza a posição atual do carteiro para o próximo destino.
        CasaInc = CasaFim;
    }

    // Retorna a soma dos tempos de todos os deslocamentos.
    return TempoPercurso;
}

/*
 * Calcula o tempo necessário para deslocar-se entre duas posições.
 *
 * origem: posição atual do carteiro.
 * destino: posição da próxima entrega.
 *
 * Como cada movimento entre casas adjacentes custa uma unidade de tempo,
 * o tempo é igual à diferença absoluta entre as posições.
 */
int CalculateTimeVariation(int origem, int destino)
{
    int t;

    // Se o destino estiver à direita da origem, subtrai origem de destino.
    if (destino >= origem) {
        t = destino - origem;
    }
    // Se o destino estiver à esquerda, subtrai destino de origem.
    else {
        t = origem - destino;
    }

    return t;
}

/*
 * Encontra a posição de uma casa usando busca binária.
 *
 * Entrega: número da casa que deve ser encontrada.
 * QtdCasas: quantidade de elementos do vetor.
 * Casas: vetor ordenado com os números das casas.
 *
 * Retorna o índice da primeira posição cujo valor é maior ou igual
 * a Entrega. Como as casas de entrega existem no vetor, esse índice
 * corresponde à posição da casa procurada.
 */
int FindingHome(int Entrega, int QtdCasas, int *Casas)
{
    // PosEs representa o limite esquerdo da busca.
    // PosDi representa o limite direito da busca.
    // Os valores -1 e QtdCasas são limites externos ao vetor.
    int PosEs = -1, PosDi = QtdCasas, PontoMedio;

    // Continua enquanto houver posições entre os dois limites.
    while (PosEs < PosDi - 1) {

        // Calcula o índice central do intervalo de busca.
        PontoMedio = (PosEs + PosDi) / 2;

        // Se o valor central for menor que a entrega,
        // a casa procurada deve estar à direita desse índice.
        if (Casas[PontoMedio] < Entrega) {
            PosEs = PontoMedio;
        }
        // Caso contrário, mantém o meio como limite direito,
        // procurando uma posição válida mais à esquerda.
        else {
            PosDi = PontoMedio;
        }
    }

    // Retorna o índice encontrado.
    return PosDi;
}
