/* --------------------------------------------------------------------------
Disciplina  : Algoritmos e Estruturas de Dados 2026S1
Nome        : Allyson Kayk de Souza
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1110
Data        : 11/10/2026
Objetivo    : Encontrar a sequência de cartas descartadas e a última carta
              remanescente em um jogo de cartas.
Dificuldade : Entender a inserção, a remoção de elementos em listas
              encadeadas e a implementação da lógica de transporte.
Uso de IA   : Interpretação do problema, consulta de linguagem e documentação
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/*
 * Estrutura de um nó de uma lista simplesmente encadeada.
 *
 * conteudo: armazena o valor inteiro da carta.
 * seg: ponteiro para o próximo nó da lista.
 */
typedef struct listint {
    int conteudo;
    struct listint *seg;
} listint;

/* Protótipos das funções utilizadas no programa. */
listint *CreateListInt(void);
void AddListInt(int conteudo, listint *p);
void Remove(listint *p);
int TransportCell(listint *origem, listint *destino);
void Imprima(listint *lista);
void DeployList(listint *lista);

int main() {
    int n;

    /*
     * Lê e processa vários jogos.
     * A leitura termina quando o valor 0 é encontrado
     * ou quando não há mais dados disponíveis na entrada.
     */
    while (scanf("%d", &n) == 1 && n != 0) {

        /*
         * Cria as duas listas do jogo atual:
         * FilaInic: armazena as cartas que permanecem no jogo.
         * FilaDesc: armazena as cartas que foram descartadas.
         *
         * Ambas possuem um nó cabeça, que não representa
         * uma carta.
         */
        listint *FilaInic = CreateListInt();
        listint *FilaDesc = CreateListInt();

        /*
         * Verifica se a criação das listas foi bem-sucedida.
         * DeployList também aceita NULL, permitindo liberar
         * a lista que eventualmente tenha sido criada.
         */
        if (FilaInic == NULL || FilaDesc == NULL) {
            DeployList(FilaInic);
            DeployList(FilaDesc);
            return 1;
        }

        /*
         * Inicializa a fila com as cartas numeradas de 1 até n,
         * inserindo cada carta no final da lista.
         */
        for (int i = 0; i < n; i++) {
            AddListInt(i + 1, FilaInic);
        }

        /*
         * Executa o procedimento enquanto houver pelo menos
         * duas cartas na fila inicial.
         *
         * FilaInic->seg aponta para a primeira carta.
         * FilaInic->seg->seg aponta para a segunda carta.
         *
         * Em cada repetição:
         * 1. Transfere a primeira carta para a lista de descartadas.
         * 2. Move a nova primeira carta para o final da própria fila.
         *
         * Quando resta apenas uma carta, o laço termina.
         */
        while (FilaInic->seg != NULL &&
               FilaInic->seg->seg != NULL) {

            // Descarta a primeira carta da fila inicial.
            TransportCell(FilaInic, FilaDesc);

            // Move a próxima carta para o final da própria fila.
            TransportCell(FilaInic, FilaInic);
        }

        // Imprime a sequência de cartas descartadas.
        printf("Discarded cards:");
        Imprima(FilaDesc);

        // Imprime a única carta que restou no jogo.
        printf("\nRemaining card:");
        Imprima(FilaInic);

        printf("\n");

        /*
         * Libera a memória das duas listas antes de iniciar
         * o próximo jogo, evitando acúmulo de memória alocada.
         */
        DeployList(FilaDesc);
        DeployList(FilaInic);
    }

    return 0;
}

/*
 * Cria uma lista vazia com um nó cabeça.
 *
 * Retorna:
 * - O endereço do nó cabeça, se a alocação for bem-sucedida.
 * - NULL, se não houver memória disponível.
 */
listint *CreateListInt(void) {
    listint *cabeca = malloc(sizeof(listint));

    if (cabeca == NULL) {
        return NULL;
    }

    // Indica que a lista não possui elementos.
    cabeca->seg = NULL;

    return cabeca;
}

/*
 * Insere um novo elemento no final da lista.
 *
 * conteudo: valor que será armazenado no novo nó.
 * p: ponteiro para o nó cabeça da lista.
 */
void AddListInt(int conteudo, listint *p) {
    // Aloca memória para o novo nó.
    listint *nova = malloc(sizeof(listint));

    // Se a alocação falhar, encerra a função.
    if (nova == NULL) {
        return;
    }

    // Define o valor do novo nó.
    nova->conteudo = conteudo;

    // O novo nó será o último da lista.
    nova->seg = NULL;

    /*
     * Percorre a lista até encontrar o último nó.
     * O último nó é aquele cujo ponteiro seg é NULL.
     */
    while (p->seg != NULL) {
        p = p->seg;
    }

    // Faz o último nó apontar para o novo elemento.
    p->seg = nova;
}

/*
 * Remove o nó imediatamente posterior ao nó apontado por p.
 *
 * Quando p é o nó cabeça, remove o primeiro elemento
 * efetivo da lista.
 */
void Remove(listint *p) {
    // Verifica se existe um elemento que possa ser removido.
    if (p == NULL || p->seg == NULL) {
        return;
    }

    // Guarda o endereço do nó que será removido.
    listint *Descarte = p->seg;

    /*
     * Faz o nó anterior apontar para o sucessor
     * do elemento que será removido.
     */
    p->seg = Descarte->seg;

    // Libera a memória do nó removido.
    free(Descarte);
}

/*
 * Transfere o primeiro elemento da lista de origem
 * para o final da lista de destino.
 *
 * origem: lista da qual o elemento será retirado.
 * destino: lista na qual o valor será inserido.
 *
 * Retorna:
 * 1, se a transferência for considerada realizada.
 * 0, se os ponteiros forem inválidos ou a origem estiver vazia.
 */
int TransportCell(listint *origem, listint *destino) {
    // Verifica se a transferência pode ser iniciada.
    if (origem == NULL || destino == NULL ||
        origem->seg == NULL) {
        return 0;
    }

    /*
     * Insere no destino uma cópia do valor da primeira
     * carta da origem.
     */
    AddListInt(origem->seg->conteudo, destino);

    // Remove o nó original da lista de origem.
    Remove(origem);

    return 1;
}

/*
 * Imprime todos os elementos efetivos da lista,
 * separados por vírgulas.
 *
 * O nó cabeça não é impresso.
 */
void Imprima(listint *lista) {
    listint *p;

    // Começa no primeiro elemento após o nó cabeça.
    for (p = lista->seg; p != NULL; p = p->seg) {

        // Imprime o primeiro elemento sem vírgula anterior.
        if (p == lista->seg) {
            printf(" %d", p->conteudo);
        } else {
            // Separa os elementos seguintes por vírgulas.
            printf(", %d", p->conteudo);
        }
    }
}

/*
 * Libera toda a memória ocupada pela lista.
 *
 * Primeiro libera os nós que armazenam as cartas.
 * Por último, libera o nó cabeça.
 *
 * Se lista for NULL, nenhuma operação é realizada.
 */
void DeployList(listint *lista) {
    if (lista == NULL) {
        return;
    }

    listint *x;

    /*
     * Guarda o endereço do próximo nó antes de liberar
     * o nó atual, permitindo continuar a percorrer a lista.
     */
    for (listint *p = lista->seg; p != NULL; p = x) {
        x = p->seg;
        free(p);
    }

    // Libera o nó cabeça após liberar os demais elementos.
    free(lista);
}
