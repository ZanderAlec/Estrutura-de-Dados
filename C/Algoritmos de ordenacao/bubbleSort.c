#include <stdio.h>
#include <stdlib.h>

//Algoritmo de ordenação de vetores:

//Bubble sort =>  Compara um índice do vetor com o próximo índice, se o atual for maior que o próximo troca a posição dos dois. 
                //O processo é repetido até o penultimo índice do vetor, pois o último ja foi comparado.
                //Depois o algorítimo é repetido novamente um numero x de vezes, sendo x o tamanho do vetor. 

int main(){

    int numeros[10];
    int i, aux, contador;

    for(i = 0; i < 10; i++){
        printf("Digite um numero: ");
        scanf("%d", &numeros[i]);
    }

    printf("Ordem atual dos itens no array:\n");

    for(i = 0; i < 10; i++){
        printf("%4d", numeros[i]);
    }   

    //Bubble Sort:

    //Repete o algoritmo de troca 9 vezes
    for(contador = 1; contador < 10; contador++){
        for(i = 0; i < 9; i++){ //Vai do primeiro item até o penultimo:
            if(numeros[i] > numeros[i+1]){ //Se a posição i tiver valor maior que i+1 realiza a troca: 
                aux = numeros[i];
                numeros[i] = numeros[i+1];
                numeros[i+1] = aux;
            }
        }
    }

     printf("\nVetor em ordem crescente:\n");

    for(i = 0; i < 10; i++){
        printf("%4d", numeros[i]);
    }   

    printf("%d\n");    

    return 0;
}