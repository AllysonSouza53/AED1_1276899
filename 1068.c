/* --------------------------------------------------------------------------
Disciplina  : Algoritmos e Estruturas de Dados 2026S1
Nome        : Allyson Kayk de Souza
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1068
Data        : 11/10/2026
Objetivo    : indicar se a quantidade de parênteses está correta ou não,
              sem levar em conta o restante da expressão
Dificuldade : Tratamento de erros, loop de n expressoes questões de linguagem
Uso de IA   : Interpretação do problema, consulta de linguagem e documentação
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/*
    Estrutura de um nó da lista encadeada.

    conteudo: armazena o caractere guardado no nó.
    seg: aponta para o próximo nó da lista.
*/
typedef struct listchar {
    char conteudo;
    struct listchar *seg;
} listchar;


/* Protótipos das funções utilizadas no programa. */
listchar *CreateList();
int Verificador(char *entrada);
int AddUnTopListChar(char conteudo, listchar *lista);
void RemoveUnTopListChar(listchar *lista);
void DestroyList(listchar *lista);


int main()
{
    /*
        Vetor que armazenará cada expressão lida.
        O tamanho permite armazenar até 1000 caracteres
        mais o caractere terminador '\0'.
    */
    char Expressao[1001];

    /*
        Lê uma linha por vez até que não haja mais entrada (EOF).
        fgets() retorna NULL quando não consegue realizar uma leitura.
    */
    while (fgets(Expressao, 1001, stdin) != NULL) {

        /*
            Verifica se os parênteses da expressão estão balanceados.

            Retorno 1: expressão correta quanto ao balanceamento.
            Retorno 0: expressão incorreta quanto ao balanceamento.
        */
        if (Verificador(Expressao) == 1) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }

    return 0;
}


/*
    Cria a lista encadeada utilizada como pilha.

    Aloca um nó cabeça, que não armazena um elemento da expressão.
    O campo seg começa como NULL, indicando que a pilha está vazia.

    Retorna o endereço do nó cabeça ou NULL se a alocação falhar.
*/
listchar *CreateList()
{
    listchar *cabeca = malloc(sizeof(listchar));

    if (cabeca == NULL) {
        return NULL;
    }

    cabeca->seg = NULL;

    return cabeca;
}


/*
    Libera toda a memória ocupada pela lista.

    Primeiro, remove todos os nós que armazenam elementos.
    Depois, libera o próprio nó cabeça.
*/
void DestroyList(listchar *lista)
{
    if (lista == NULL) {
        return;
    }

    while (lista->seg != NULL) {
        RemoveUnTopListChar(lista);
    }

    free(lista);
}


/*
    Verifica se os parênteses de uma expressão estão balanceados.

    A lógica utilizada é:
    - Ao encontrar '(', empilha um caractere.
    - Ao encontrar ')', remove um elemento da pilha.
    - Se encontrar ')' com a pilha vazia, retorna 0.
    - Ao terminar a leitura, verifica se a pilha está vazia.

    Retorna 1 se os parênteses estiverem balanceados.
    Retorna 0 caso contrário ou se houver falha de alocação.
*/
int Verificador(char *entrada)
{
    /* Verifica se o ponteiro recebido é válido. */
    if (entrada == NULL) {
        return 0;
    }

    /* Cria a pilha que armazenará os parênteses abertos. */
    listchar *Pilha = CreateList();

    if (Pilha == NULL) {
        return 0;
    }

    /*
        Percorre a expressão até encontrar '\0',
        que indica o fim da string.
    */
    for (int i = 0; entrada[i] != '\0'; i++) {

        /* Parêntese aberto: adiciona um elemento à pilha. */
        if (entrada[i] == '(') {

            /*
                Se a inserção falhar por falta de memória,
                libera a pilha e informa que a verificação falhou.
            */
            if (!AddUnTopListChar('(', Pilha)) {
                DestroyList(Pilha);
                return 0;
            }

        /* Parêntese fechado: precisa de uma abertura correspondente. */
        } else if (entrada[i] == ')') {

            /*
                Se houver elementos na pilha, remove o topo,
                associando o fechamento a uma abertura anterior.
            */
            if (Pilha->seg != NULL) {
                RemoveUnTopListChar(Pilha);

            } else {
                /*
                    Não existe abertura correspondente.
                    A expressão está desbalanceada.
                */
                DestroyList(Pilha);
                return 0;
            }
        }

        /*
            Os demais caracteres são ignorados, pois o objetivo
            é verificar exclusivamente o balanceamento de '(' e ')'.
        */
    }

    /*
        Se a pilha estiver vazia, todas as aberturas tiveram
        seus respectivos fechamentos.
        Se restarem elementos, há parênteses abertos sem fechamento.
    */
    int correto = (Pilha->seg == NULL);

    /* Libera a memória utilizada pela pilha. */
    DestroyList(Pilha);

    return correto;
}


/*
    Insere um caractere no topo da pilha.

    O novo nó passa a apontar para o antigo primeiro elemento.
    Em seguida, o nó cabeça passa a apontar para o novo nó.

    Retorna 1 se a inserção for realizada.
    Retorna 0 se a alocação de memória falhar.
*/
int AddUnTopListChar(char conteudo, listchar *lista)
{
    listchar *Novo = malloc(sizeof(listchar));

    if (Novo == NULL) {
        return 0;
    }

    Novo->conteudo = conteudo;

    /* O novo nó aponta para o antigo topo da pilha. */
    Novo->seg = lista->seg;

    /* O nó cabeça passa a apontar para o novo topo. */
    lista->seg = Novo;

    return 1;
}


/*
    Remove o elemento do topo da pilha.

    Guarda o endereço do primeiro nó, atualiza o ponteiro
    do nó cabeça e libera a memória do nó removido.

    Se a lista for NULL ou estiver vazia, não realiza nenhuma ação.
*/
void RemoveUnTopListChar(listchar *lista)
{
    if (lista == NULL || lista->seg == NULL) {
        return;
    }

    /* Guarda o endereço do elemento que será removido. */
    listchar *Descarte = lista->seg;

    /* O nó cabeça passa a apontar para o segundo elemento. */
    lista->seg = Descarte->seg;

    /* Libera a memória do antigo topo. */
    free(Descarte);
}
