#include <iostream>
using namespace std;

int main(){
    //Declaração de Variveis
    int *V, T, maior, posicao;

    //Leitura da quantidade de espaços do vetor V
    cin>>T;

    //Alocamento de memoria de T espaços de tamanho int [T.TamanhoDe(int)]
    V = (int *)malloc(T*sizeof(int));

    //Verificação de erro
    if( V == NULL){
        cout<<"Erro no MALLOC";
        return 1;
    }

    //Laço de Leitura e Verificação
    for(int n=0;n<0;n++){
        cin>>V[n];

        // (V[n-1]<=V[n]) -> maior = V[n] ^ posicao = n, ∀ V[n] ^ n ∈ Z.
        if(n>0){
            if(V[n-1]<= V[n]){
                maior = V[n];
                posicao = n;
            }else{
                maior = V[n-1];
                posicao = n-1;
            }
        }
    }

    //Liberação do vertor V
    free(V);

    //Mostra de Resultados
    cout<<maior <<"\n"<<posicao<<"\n";

    return 0;
}