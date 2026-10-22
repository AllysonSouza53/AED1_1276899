#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int Conteudo;
    struct tree *pai;
    struct tree *dir;
    struct tree *esq;
}tree;

int main()
{
    tree *Raiz = CreateTree();//Cria uma lista sem conteudo na raiz
    int n;

    if(Raiz == NULL)return 1;

    for(int i = 0; i<5;i++){
        scanf("%d", &n);

        if(i == 0){
            Raiz->Conteudo = n;
            continue;
        }



    }

    return 0;
}

tree *CreateTree(){
    tree *Raiz = (arvore *)malloc(sizeof(arvore));

    if(Raiz == NULL){
        printf("ERROR 00");//ERROR 00: Não foi possivel criar a arvore
        return NULL;
    }

    Raiz->pai = NULL;
    Raiz->dir = NULL;
    Raiz->esq = NULL;
    Raiz->Conteudo = NULL;

    return Raiz;
}

tree *AddNewNode(tree *Raiz, int Conteudo){
    tree *New = (arvore *)malloc(sizeof(arvore));

    if(Raiz == NULL || New == NULL || Raiz->Conteudo == NULL){
        printf("ERROR 01");//ERROR 01: Não foi possivel criar o novo nó
        return NULL;
    }

    New->Conteudo = Conteudo;
    New->esq = NULL;
    New->dir = NULL;

    while(Raiz != NULL){
        if(Raiz->Conteudo <= Conteudo){
            Raiz = Raiz->esq;
        }else{
            Raiz =Raiz->dir;
        }
    }

    
}
