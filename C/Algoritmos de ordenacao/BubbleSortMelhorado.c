#include <stdio.h>
#include <stdlib.h>

//Algoritmo de ordenação de vetores:

int main(){

    int numeros[10];

    for(int i = 0; i < 10; i++){
        printf("Digite um numero: ");
        scanf("%d", &numeros[i]);
    }

    printf("Ordem atual dos itens no array:\n");

    for(int i = 0; i < 10; i++){
        printf("%4d", numeros[i]);
    }   


    /*Bubble sort melhorado:
    
    //p/ Melhorar o bubble sort foram adotados duas estratégias:
        1 - Variável que verifica o número de trocas que ocorreram, se esse valor for 0, então encerra o algorítmo, pois o vetor está ordenado.
        2 - fazer com que cada loop interno percorra o vetor em sentidos opostos, comparando e trocando do começo para o final e do final para o começo.
            Dessa forma, os elementos de menor e de maior valor se deslocam mais rapido (com menos iterações do loopin) para perto de sua posição final.

    */
    for(int i = 0; i < 10; i++){

        //Verifica o numero de trocas
        int trocas = 0;

        for(int j = 0, k = 9; j < 9; j++, k--){

            int aux;

            //Verifica do inicio ao fim
            if(numeros[j] > numeros[j+1]){
                aux = numeros[j];
                numeros[j] = numeros[j+1];
                numeros[j+1] = aux;

                trocas++;
            }   


            //Verifica do fim ao começo
            if(numeros[k] < numeros[k-1]){
                aux = numeros[k];
                numeros[k] = numeros[k-1];
                numeros[k-1] = aux;

                trocas++;
            }
        }

        //encerra se o algoritmo ja está ordenado
        if(trocas == 0){
            break;
        }
    }

    printf("\nVetor em ordem crescente:\n");

    for(int i = 0; i < 10; i++){
        printf("%4d", numeros[i]);
    }   

    printf("%d\n");    

    return 0;
}