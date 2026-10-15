/* --------------------------------------------------------------------------
Disciplina  : Algoritmos e Estruturas de Dados 2026S1
Nome        : Allyson Kayk de Souza
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1077
Data        : 14/10/2026
Objetivo    : Passar do formato infixo para posfixo uma expressão.
Dificuldade : Tratamento de erros, entendimento do posfixo e trabalho com as listas
Uso de IA   : Interpretação do problema, consulta de linguagem e documentação
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/*
 * Estrutura de um nó da lista encadeada.
 *
 * Conteudo: armazena um caractere da expressão.
 * Seg: aponta para o próximo nó da lista.
 *
 * A lista utiliza um nó cabeça, que não armazena um
 * caractere válido da expressão, mas facilita as operações.
 */
typedef struct listChar {
    char Conteudo;
    struct listChar *Seg;
} listChar;


/* Protótipos das funções utilizadas no programa. */

// Converte uma expressão infixa para a forma pós-fixa.
listChar *ToPostfix(char *Expressao);

// Retorna a prioridade de um operador.
int Precedence(char Operador);

// Identifica se um caractere é operando ou operador.
int Identifier(char Caracter);

// Cria uma lista encadeada com um nó cabeça.
listChar *CreateList();

// Insere um caractere no final da lista.
void AddUnderneathListChar(char Conteudo, listChar *Lista);

// Insere um caractere no início da lista, após o nó cabeça.
void AddUnTopListChar(char Conteudo, listChar *Lista);

// Remove o primeiro elemento real da lista.
void RemoveUnTopListChar(listChar *Lista);

// Procura um caractere na lista e retorna seu nó.
listChar *SearchCellForContent(char Conteudo, listChar *Lista);

// Transfere o primeiro elemento de uma lista para o final de outra.
void MoveCellDown(listChar *Origem, listChar *Destino);

// Imprime os caracteres armazenados na lista.
void PrintList(listChar *lista);

// Libera a memória ocupada pela lista.
void DestroyList(listChar *lista);


int main()
{
    int N;

    // Lê a quantidade de expressões que serão processadas.
    scanf("%d", &N);

    // Consome o caractere de quebra de linha deixado pelo scanf.
    getchar();

    // Processa cada expressão informada na entrada.
    for (int i = 0; i < N; i++) {
        char Expressao[301];

        // Lê uma expressão, incluindo possíveis espaços.
        if (fgets(Expressao, 301, stdin) == NULL) {
            break;
        }

        // Converte a expressão para a notação pós-fixa.
        listChar *Saida = ToPostfix(Expressao);

        // Encerra o programa caso a conversão falhe.
        if (Saida == NULL) {
            return 1;
        }

        // Imprime a expressão convertida.
        PrintList(Saida);

        // Libera a memória da lista que contém a saída.
        DestroyList(Saida);
    }

    return 0;
}


// ============================================================
// FUNÇÕES ESPECÍFICAS DO PROBLEMA
// ============================================================

/*
 * Converte uma expressão da notação infixa para a pós-fixa.
 *
 * Na notação infixa, os operadores ficam entre os operandos:
 *     a + b
 *
 * Na notação pós-fixa, os operadores ficam após os operandos:
 *     ab+
 *
 * FilaSaida:
 *     Armazena os caracteres da expressão pós-fixa.
 *
 * PilhaOperadores:
 *     Armazena temporariamente os operadores e os parênteses.
 *     O primeiro elemento real da lista representa o topo.
 *
 * Regras utilizadas:
 *     1. Operandos são enviados diretamente para a saída.
 *     2. Operadores são empilhados respeitando a precedência.
 *     3. '(' é empilhado para delimitar uma subexpressão.
 *     4. ')' provoca a transferência dos operadores até '('.
 *     5. Ao final, os operadores restantes são enviados à saída.
 */
listChar *ToPostfix(char *Expressao) {

    // Cria a lista que armazenará a expressão pós-fixa.
    listChar *FilaSaida = CreateList();

    // Cria a pilha utilizada para organizar os operadores.
    listChar *PilhaOperadores = CreateList();

    // Verifica se as listas foram criadas corretamente.
    if (PilhaOperadores == NULL || FilaSaida == NULL) {
        DestroyList(FilaSaida);
        DestroyList(PilhaOperadores);
        return NULL;
    }

    // Percorre a expressão até o fim da string ou a quebra de linha.
    for (int j = 0;
         Expressao[j] != '\0' && Expressao[j] != '\n';
         j++) {

        // Ignora espaços em branco.
        if (Expressao[j] == ' ') {
            continue;
        }

        /*
         * Caso 1: operando.
         *
         * Letras e algarismos são enviados diretamente para
         * o final da lista de saída.
         */
        if (Identifier(Expressao[j]) == 1) {

            AddUnderneathListChar(Expressao[j], FilaSaida);

        /*
         * Caso 2: operador aritmético.
         *
         * Enquanto houver um operador no topo da pilha com
         * prioridade maior que a do operador atual, ele será
         * transferido para a saída.
         *
         * Se as prioridades forem iguais, também transferimos
         * o operador do topo, exceto quando o operador atual
         * for '^', pois a exponenciação é associativa à direita.
         *
         * O parêntese '(' interrompe a comparação de prioridade.
         */
        } else if (Identifier(Expressao[j]) == 2) {

            while (
                PilhaOperadores->Seg != NULL &&
                PilhaOperadores->Seg->Conteudo != '(' &&
                (
                    Precedence(PilhaOperadores->Seg->Conteudo)
                        > Precedence(Expressao[j]) ||

                    (
                        Precedence(PilhaOperadores->Seg->Conteudo)
                            == Precedence(Expressao[j]) &&
                        Expressao[j] != '^'
                    )
                )
            ) {

                // Retira o operador do topo e o envia para a saída.
                MoveCellDown(PilhaOperadores, FilaSaida);
            }

            // Empilha o operador atual.
            AddUnTopListChar(Expressao[j], PilhaOperadores);

        /*
         * Caso 3: parêntese de abertura.
         *
         * É colocado no topo da pilha para indicar o início
         * de uma subexpressão entre parênteses.
         */
        } else if (Expressao[j] == '(') {

            AddUnTopListChar('(', PilhaOperadores);

        /*
         * Caso 4: parêntese de fechamento.
         *
         * Transfere os operadores para a saída até encontrar
         * o parêntese de abertura correspondente.
         *
         * O próprio '(' é removido da pilha, mas não é enviado
         * para a expressão pós-fixa.
         */
        } else if (Expressao[j] == ')') {

            while (
                PilhaOperadores->Seg != NULL &&
                PilhaOperadores->Seg->Conteudo != '('
            ) {
                MoveCellDown(PilhaOperadores, FilaSaida);
            }

            // Remove o '(' encontrado, sem transferi-lo à saída.
            if (PilhaOperadores->Seg != NULL) {
                RemoveUnTopListChar(PilhaOperadores);
            }

        /*
         * Caso 5: caractere não reconhecido.
         *
         * Libera as listas e indica que a conversão falhou.
         */
        } else {

            DestroyList(FilaSaida);
            DestroyList(PilhaOperadores);
            return NULL;
        }
    }

    /*
     * Após percorrer a expressão, transfere os operadores
     * restantes para a saída.
     *
     * Se ainda houver '(' na pilha, a expressão contém um
     * parêntese de abertura sem fechamento correspondente.
     */
    while (PilhaOperadores->Seg != NULL) {

        if (PilhaOperadores->Seg->Conteudo == '(') {

            DestroyList(FilaSaida);
            DestroyList(PilhaOperadores);
            return NULL;
        }

        MoveCellDown(PilhaOperadores, FilaSaida);
    }

    // A pilha não é mais necessária após a conversão.
    DestroyList(PilhaOperadores);

    // Retorna a lista que contém a expressão pós-fixa.
    return FilaSaida;
}


/*
 * Determina a precedência dos operadores aritméticos.
 *
 * Maior valor significa maior prioridade:
 *
 *     ^       prioridade 3
 *     * e /   prioridade 2
 *     + e -   prioridade 1
 *
 * O valor 0 é retornado para caracteres que não correspondem
 * aos operadores reconhecidos pela função.
 */
int Precedence(char Operador) {

    if (Operador == '^') {
        return 3;
    }

    if (Operador == '*' || Operador == '/') {
        return 2;
    }

    if (Operador == '+' || Operador == '-') {
        return 1;
    }

    return 0;
}


/*
 * Classifica os caracteres da expressão.
 *
 * Retornos:
 *     1: letra ou algarismo, tratado como operando.
 *     2: operador aritmético reconhecido.
 *     0: caractere não reconhecido.
 *
 * Os parênteses são tratados separadamente em ToPostfix().
 */
int Identifier(char Caracter) {

    // Verifica se o caractere é uma letra maiúscula,
    // uma letra minúscula ou um algarismo.
    if (
        (Caracter >= 'A' && Caracter <= 'Z') ||
        (Caracter >= 'a' && Caracter <= 'z') ||
        (Caracter >= '0' && Caracter <= '9')
    ) {
        return 1;

    // Verifica se o caractere é um operador aritmético.
    } else if (
        Caracter == '+' ||
        Caracter == '-' ||
        Caracter == '*' ||
        Caracter == '/' ||
        Caracter == '^'
    ) {
        return 2;
    }

    // Caractere não reconhecido.
    return 0;
}


// ============================================================
// FUNÇÕES DE MANIPULAÇÃO DA LISTA ENCADEADA
// ============================================================

/*
 * Cria uma lista encadeada vazia.
 *
 * O nó cabeça é criado separadamente e não armazena um
 * caractere válido da expressão.
 *
 * Inicialmente, Seg é NULL, indicando que não há elementos.
 */
listChar *CreateList() {

    listChar *Cabeca = malloc(sizeof(listChar));

    // Se a alocação falhar, retorna NULL.
    if (Cabeca == NULL) {
        return NULL;
    }

    // Inicializa a lista sem elementos reais.
    Cabeca->Seg = NULL;

    return Cabeca;
}


/*
 * Insere um novo caractere no final da lista.
 *
 * Percorre os nós a partir do nó cabeça até encontrar
 * o último nó, cujo ponteiro Seg é NULL.
 *
 * O novo nó é conectado após esse último elemento.
 */
void AddUnderneathListChar(char Conteudo, listChar *Lista) {

    // Reserva memória para o novo nó.
    listChar *Nova = malloc(sizeof(listChar));

    // Se a alocação falhar, a inserção não é realizada.
    if (Nova == NULL) {
        return;
    }

    // Inicializa o conteúdo e o ponteiro do novo nó.
    Nova->Conteudo = Conteudo;
    Nova->Seg = NULL;

    // Percorre a lista até alcançar seu último nó.
    while (Lista->Seg != NULL) {
        Lista = Lista->Seg;
    }

    // Conecta o novo nó ao final da lista.
    Lista->Seg = Nova;
}


/*
 * Insere um novo caractere no início da lista,
 * imediatamente após o nó cabeça.
 *
 * Como a inserção acontece no topo da pilha, os elementos
 * mais recentemente inseridos são os primeiros a serem
 * acessados ou removidos.
 */
void AddUnTopListChar(char Conteudo, listChar *Lista) {

    // Reserva memória para o novo nó.
    listChar *Nova = malloc(sizeof(listChar));

    // Se a alocação falhar, a inserção não é realizada.
    if (Nova == NULL) {
        return;
    }

    // Armazena o caractere no novo nó.
    Nova->Conteudo = Conteudo;

    // Faz o novo nó apontar para o antigo primeiro elemento.
    Nova->Seg = Lista->Seg;

    // Atualiza o nó cabeça para que Nova seja o primeiro.
    Lista->Seg = Nova;
}


/*
 * Remove o primeiro elemento real da lista.
 *
 * O nó cabeça é preservado. O primeiro nó real é
 * desconectado e sua memória é liberada.
 *
 * Se a lista não existir ou estiver vazia, nada acontece.
 */
void RemoveUnTopListChar(listChar *Lista) {

    if (Lista == NULL || Lista->Seg == NULL) {
        return;
    }

    // Guarda o endereço do primeiro nó real.
    listChar *Descarte = Lista->Seg;

    // Faz o nó cabeça apontar para o segundo elemento.
    Lista->Seg = Descarte->Seg;

    // Libera a memória do nó removido.
    free(Descarte);
}


/*
 * Procura um caractere na lista e retorna o endereço
 * do primeiro nó que contém esse caractere.
 *
 * A busca começa após o nó cabeça.
 *
 * Se a lista for inexistente ou vazia, retorna NULL.
 *
 * Observação: se o caractere não for encontrado, esta
 * implementação retorna o último nó visitado. Portanto,
 * o chamador deve verificar o Conteudo do nó retornado.
 */
listChar *SearchCellForContent(char Conteudo, listChar *Lista) {

    if (Lista == NULL || Lista->Seg == NULL) {
        return NULL;
    }

    // Ignora o nó cabeça e começa pelo primeiro elemento real.
    Lista = Lista->Seg;

    // Percorre a lista enquanto o caractere não for encontrado
    // e ainda houver um próximo nó.
    while (Lista->Conteudo != Conteudo && Lista->Seg != NULL) {
        Lista = Lista->Seg;
    }

    // Retorna o nó encontrado ou o último nó visitado.
    return Lista;
}


/*
 * Transfere o primeiro elemento real da lista Origem
 * para o final da lista Destino.
 *
 * Na conversão para pós-fixa, essa operação permite retirar
 * operadores do topo da pilha e colocá-los na saída.
 *
 * A função preserva o caractere, mas cria um novo nó na
 * lista de destino e remove o nó original da lista de origem.
 */
void MoveCellDown(listChar *Origem, listChar *Destino) {

    // Verifica se as listas existem e se Origem possui elemento.
    if (
        Origem == NULL ||
        Destino == NULL ||
        Origem->Seg == NULL
    ) {
        return;
    }

    // Copia o caractere do topo de Origem para o final de Destino.
    AddUnderneathListChar(Origem->Seg->Conteudo, Destino);

    // Remove o elemento do topo da lista de origem.
    RemoveUnTopListChar(Origem);
}


/*
 * Imprime todos os caracteres armazenados na lista.
 *
 * A impressão começa no primeiro nó real, ignorando o nó
 * cabeça, e termina ao alcançar o fim da lista.
 *
 * Ao final, imprime uma quebra de linha.
 */
void PrintList(listChar *lista) {

    // Evita acessar uma lista inexistente.
    if (lista == NULL) {
        return;
    }

    // Percorre e imprime cada caractere da lista.
    for (listChar *p = lista->Seg; p != NULL; p = p->Seg) {
        printf("%c", p->Conteudo);
    }

    // Finaliza a linha da saída.
    printf("\n");
}


/*
 * Libera toda a memória ocupada pela lista encadeada.
 *
 * Primeiro libera cada nó real. Para isso, guarda o endereço
 * do próximo nó antes de liberar o nó atual.
 *
 * Por último, libera o nó cabeça.
 */
void DestroyList(listChar *lista) {

    // Não há nada a liberar se a lista não existir.
    if (lista == NULL) {
        return;
    }

    listChar *x;

    /*
     * Guarda o próximo nó antes de liberar o atual.
     * Assim, o percurso pode continuar sem acessar memória
     * que já foi liberada.
     */
    for (listChar *p = lista->Seg; p != NULL; p = x) {
        x = p->Seg;
        free(p);
    }

    // Libera o nó cabeça após liberar os nós reais.
    free(lista);
}
