#define <stdio.h>
#define <stlib.h>

typedef struct NodoArvore{
    struct NodoArvore *Pai;
    int Conteudo;
    struct NodoArvore *Direita;
    struct NodoArvore *Esquerda;
}

NodoArvore *CreateTree(int Conteudo){
    if(Conteudo < 0)return 0;

    NodoArvore *Raiz = malloc(sizeof(NodoArvore));
    if(Raiz == NULL)return 0;

    Raiz->Pai = NULL;
    Raiz->Direita = NULL;
    Raiz->Esquerda = NULL;
    Raiz->Conteudo = Conteudo;

    return Raiz;
}

int AddNodo(NodoArvore *Arvore, int Conteudo){
    if(Arvore == NULL || Conteudo < 0)return 0;

    NodoArvore *Novo = malloc(sizeof(NodoArvore));
    if(Novo == NULL)return 0;

    Novo->Conteudo = Conteudo;
    Novo->Direita = NULL;
    Novo->Esquerda = NULL;

    while(1){
        if(Arvore->Conteudo >= Conteudo){
            if(Arvore->Direita == NULL){
                Arvore->Direita = Novo;
                break;
            }
            Arvore = Arvore->Direita;
        }else{
            if(Arvore->Esquerda == NULL){
                Arvore->Esquerda = Novo;
                break;
            }
            Arvore = Arvore->Esquerda;
        }
    }

    Novo->Pai = Arvore;

    return 1;
}



int main(){
    int QtdCasos, QtdNodos;
    scanf("%d", &QtdCasos);

    for(int i = 0; i < QtdCasos; i++){

        scanf("%d", &QtdNodos);
        if(QtdNodos <= 0) continue;

        scanf("%d", &Conteudo);
        NodoArvore *Arvore = CreateTree(Conteudo);

        for(int j = 0; j < QtdNodos - 1; j++){

        }
    }
    return 0;
}
