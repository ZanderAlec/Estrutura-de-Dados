#include <stdio.h>
#include <stdlib.h>

//QuickSort=>   A idéia é dividir e conquistar. 
        //    Funcionamento: Um elemento é escolhido como pivô e os dados são rearranjados de forma que,
    //          os valores menores que o pivô fiquem antes e os maiores, depois.
    //         Depois, recursivamente, ordenado as duas partições.

//O problema do quick está em como escolher o pivô, pois esta afeta o desempenho do algorítmo.

//retorna o índice que divirá o vetor (pivô).
int particiona(int *v, int inicio, int fim){
    int esq, dir, pivo, aux;

    esq = inicio;
    dir = fim;
    pivo = v[inicio];

    //enquanto direita for diferente de esquerda
    while(esq < dir){

        //Avança as posições da esquerda até achar um elemento que não seja menor que pivô
        while(v[esq] <= pivo){
            esq++;
        }

        //Avança as posições da direita  até achar um elemento que não seja maior que pivô
        while(v[dir] > pivo){
            dir--;
        }

        //troca direita e esquerda de lugar
        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
        }
    }

    //direita é o novo pivor, pois onde parou na direita todos antes são menores e todos depois são maiores.
    v[inicio]  = v[dir];
    v[dir] = pivo;
    return dir;
} 

void quickSort(int *v, int inicio, int fim){
    int pivo;

    //Verifica se "fim" e "inicio" do vetor são diferentes:
    if(fim>inicio){

        //Calcula a posição do pivô / Separa os dados em 2 partes(maiores e menores que o pivô):
        pivo = particiona(v, inicio, fim);

        //Ordena as partes recursivamente:

        //Chama a função pra metade menor que o pivô:
        quickSort(v, inicio, pivo-1);

         //Chama a função pra metade maior que o pivô:
        quicksort(v, pivo+1, fim);
    }
}


int main(){

    int numeros[10];
    int i;

    for(i = 0; i < 10; i++){
        printf("Digite um numero: ");
        scanf("%d", &numeros[i]);
    }

    printf("Ordem atual dos itens no array:\n");

    for(i = 0; i < 10; i++){
        printf("%4d", numeros[i]);
    }  

    quickSort(numeros, 0, 9);

    printf("\nOrdem atual dos itens no array:\n");

    for(i = 0; i < 10; i++){
        printf("%4d", numeros[i]);
    }  

    return 0;   
}