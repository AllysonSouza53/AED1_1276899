#include <iostream>
using namespace std;

int main(){
    //Declaração de Variveis
    int V[100], maior, posicao;
    
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

    //Mostra de resultados
    cout<<maior <<"\n"<<posicao<<"\n";

    return 0;
}