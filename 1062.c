/* --------------------------------------------------------------------------
Disciplina  : Algoritmos e Estruturas de Dados 2026S1
Nome        : Allyson Kayk de Souza
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1062
Data        : 14/10/2026
Objetivo    : Verificar se uma sequência de saída de vagões
              é possível utilizando uma pilha.
Dificuldade : Saída e entrada do beecrowd, entendimento do processo dos vagoes.
Uso de IA   : Interpretação do problema, consulta de linguagem e documentação
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/*
 * Estrutura de um nó da lista encadeada.
 *
 * Conteudo: armazena o número de um vagão.
 * Seg: ponteiro para o próximo nó da lista.
 *
 * A lista utiliza um nó cabeça, que não armazena um vagão.
 * Esse nó facilita as operações de inserção e remoção.
 * Os nós seguintes representam os elementos da pilha.
 */
typedef struct listInt {
    int Conteudo;
    struct listInt *Seg;
} listInt;

/* Protótipos das funções responsáveis pelas operações da lista. */
listInt *CreateList(void);
int RemoveUnTopList(listInt *Lista);
int AddUnTopList(int Conteudo, listInt *Lista);
void DestroyList(listInt *Lista);


int main(){

    /*
     * Laço externo responsável por processar os diferentes
     * conjuntos de testes fornecidos pela entrada.
     */
    while(1){

        /* N representa a quantidade de vagões.
         * SaidaDesejada armazena a ordem em que devem sair.
         */
        int N, SaidaDesejada[1001];

        /* Lê a quantidade de vagões do conjunto atual. */
        scanf("%d", &N);

        /* Se N for zero, encerra a execução do programa. */
        if(N == 0)return 0;
        
        /*
         * Laço interno responsável por processar diferentes
         * sequências de saída para a mesma quantidade de vagões.
         */
        while(1){

            /*
             * possivel indica se a sequência pode ser realizada.
             * Começa como verdadeira e muda para zero caso
             * alguma saída não possa ser executada.
             *
             * Vagao indica o próximo vagão que ainda deve entrar
             * na estação. Os vagões chegam na ordem 1, 2, ..., N.
             */
            int possivel = 1, Vagao = 1;

            /*
             * Lê o primeiro número da sequência separadamente,
             * pois zero indica o fim das sequências deste conjunto.
             */
            scanf("%d", &SaidaDesejada[0]);

            if (SaidaDesejada[0] == 0) {

                /* Imprime a linha em branco exigida pelo problema
                 * e encerra o conjunto atual de sequências.
                 */
                printf("\n");
                break;
            }

            /* Lê os N - 1 números restantes da sequência desejada. */
            for (int i = 1; i < N; i++) {
                scanf("%d", &SaidaDesejada[i]);
            }

            /*
             * Cria uma lista vazia que será utilizada como pilha.
             * Se a alocação falhar, encerra o programa indicando erro.
             */
            listInt *PilhaVagoes = CreateList();

            if(PilhaVagoes == NULL)return 1;

            /*
             * Processa cada vagão da sequência desejada.
             *
             * Para cada posição, tenta colocar vagões na pilha
             * até que o vagão desejado esteja no topo ou que
             * todos os vagões disponíveis já tenham entrado.
             */
            for(int i = 0; i < N; i++){

                /*
                 * Enquanto ainda houver vagões para entrar e
                 * o topo da pilha não for o vagão desejado,
                 * insere o próximo vagão no topo da pilha.
                 *
                 * PilhaVagoes->Seg aponta para o primeiro nó
                 * com conteúdo, que representa o topo da pilha.
                 *
                 * O teste Seg == NULL verifica se a pilha está vazia.
                 */
                while(Vagao<=N &&
                      (PilhaVagoes->Seg == NULL ||
                       PilhaVagoes->Seg->Conteudo != SaidaDesejada[i])){

                    /*
                     * Insere o próximo vagão no topo.
                     * Se a alocação do novo nó falhar, libera a pilha
                     * e encerra o programa.
                     */
                    if(AddUnTopList(Vagao, PilhaVagoes)== 0){
                        DestroyList(PilhaVagoes);
                        return 1;
                    }

                    /* Avança para o próximo vagão que ainda não entrou. */
                    Vagao++;
                }

                /*
                 * Se o topo da pilha corresponder ao vagão desejado,
                 * remove esse vagão da pilha, simulando sua saída.
                 */
                if(PilhaVagoes->Seg != NULL &&
                   PilhaVagoes->Seg->Conteudo == SaidaDesejada[i]){

                    /*
                     * Remove o elemento do topo.
                     * Se a remoção falhar, libera a pilha e encerra.
                     */
                    if(RemoveUnTopList(PilhaVagoes)==0){
                        DestroyList(PilhaVagoes);
                        return 1;
                    }

                }else{

                    /*
                     * Se não houver vagões disponíveis para inserir
                     * e o topo não for o vagão desejado, a sequência
                     * é impossível utilizando uma pilha.
                     */
                    possivel = 0;
                    break;
                }
            }

            /* Libera todos os nós da pilha após analisar a sequência. */
            DestroyList(PilhaVagoes);

            /*
             * Imprime o resultado da análise:
             * Yes: a sequência pode ser realizada.
             * No: a sequência não pode ser realizada.
             */
            if(possivel != 0)printf("Yes\n");
            else printf("No\n");
        }

    }

    return 0;
}


/* --------------------------------------------------------------------------
   FUNÇÕES DE MANIPULAÇÃO DA LISTA ENCADEADA
   -------------------------------------------------------------------------- */

/*
 * Cria uma lista vazia com um nó cabeça.
 *
 * O nó cabeça não armazena um vagão; seu ponteiro Seg começa
 * como NULL, indicando que não existem elementos na lista.
 *
 * Retorno:
 * - Endereço do nó cabeça, caso a alocação seja bem-sucedida.
 * - NULL, caso não haja memória disponível.
 */
listInt *CreateList(){

    /* Reserva memória para o nó cabeça da lista. */
    listInt *Cabeca = malloc(sizeof(listInt));

    if(Cabeca == NULL)return NULL;

    /* Inicializa a lista como vazia. */
    Cabeca->Seg = NULL;

    return Cabeca;
}


/*
 * Remove o elemento que está no topo da pilha.
 *
 * Como a lista utiliza um nó cabeça, o topo corresponde ao nó
 * apontado por Lista->Seg.
 *
 * Parâmetro:
 * Lista: endereço do nó cabeça da pilha.
 *
 * Retorno:
 * - 1, se um elemento for removido.
 * - 0, se a lista for inválida ou estiver vazia.
 */
int RemoveUnTopList(listInt *Lista){

    /* Não é possível remover elementos de uma lista vazia. */
    if(Lista == NULL || Lista->Seg == NULL ){
        return 0;
    }

    /* Descarte guarda o endereço do nó que será removido. */
    listInt *Descarte;

    Descarte = Lista->Seg;

    /*
     * O nó cabeça passa a apontar para o segundo elemento.
     * Assim, o segundo elemento torna-se o novo topo da pilha.
     */
    Lista->Seg = Descarte->Seg;

    /* Libera a memória do nó removido. */
    free(Descarte);

    return 1;
}


/*
 * Insere um novo elemento no topo da pilha.
 *
 * Parâmetros:
 * Conteudo: número do vagão a ser inserido.
 * Lista: endereço do nó cabeça da pilha.
 *
 * A inserção ocorre no início da lista:
 * 1. Aloca memória para um novo nó.
 * 2. Faz o novo nó apontar para o antigo topo.
 * 3. Faz o nó cabeça apontar para o novo nó.
 *
 * Retorno:
 * - 1, se a inserção for bem-sucedida.
 * - 0, se a lista for inválida ou a alocação falhar.
 */
int AddUnTopList(int Conteudo, listInt *Lista){
    
    /* Verifica se o endereço da lista é válido. */
    if(Lista == NULL)return 0;

    /* Reserva memória para o novo nó. */
    listInt *Nova = malloc(sizeof(listInt));

    if(Nova == NULL)return 0;

    /* Armazena o número do vagão no novo nó. */
    Nova->Conteudo = Conteudo;

    /* O novo nó passa a apontar para o antigo topo. */
    Nova->Seg = Lista->Seg;

    /* O nó cabeça passa a apontar para o novo topo. */
    Lista->Seg = Nova;

    return 1;
}


/*
 * Destrói a lista e libera toda a memória alocada.
 *
 * Percorre os nós que armazenam os vagões, liberando cada um.
 * Guardador salva o endereço do próximo nó antes que o atual
 * seja liberado, permitindo continuar a travessia com segurança.
 *
 * Ao final, libera também o nó cabeça.
 *
 * Parâmetro:
 * Lista: endereço do nó cabeça da lista.
 */
void DestroyList(listInt *Lista){

    /* Se a lista não existir, não há memória a liberar. */
    if(Lista == NULL)return;

    listInt *Guardador;

    /*
     * Percorre todos os nós que contêm vagões.
     * O nó cabeça não faz parte dessa travessia.
     */
    if(Lista->Seg != NULL){
        for(listInt *i = Lista->Seg; i != NULL; i = Guardador){

            /* Guarda o próximo nó antes de liberar o atual. */
            Guardador = i->Seg;

            /* Libera a memória do nó atual. */
            free(i);
        }
    }

    /* Libera o nó cabeça e finaliza a destruição da lista. */
    free(Lista);
}
