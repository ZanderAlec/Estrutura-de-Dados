#include <stdio.h>

//Algoritimo de ordenação:
//Shell Sort=====

//É um extensão do InsertionSort. Contudo, a base para o shell sort é quebrar o vetor em vetores menores.
//As comparações são feitas por distâncias diferentes.
//A distância é dada por um valor h, assim a posição x é comparada com a posição x-h, a poiscao x+1 é comparada com a posição (x+1)-h e assim por diante.;
//Os valores de h mudam ao longo da execução do looping.
//Quando h = 1, shell sort funcionará igual o insertion, porém será mais rápido, pois o vetor ja está mais ou menos ordenado.


int main(){

    int numeros[10];
    int i, j, h, aux;

    for(i = 0; i < 10; i++){
        printf("Digite um numero: ");
        scanf("%d", &numeros[i]);
    }

    printf("Ordem atual dos itens no array:\n");

    for(i = 0; i < 10; i++){
        printf("%4d", numeros[i]);
    }   

    //Shel sort:

    //Primeiro passo é calcular o h
    //Valor inicial de h.
    h=1;
    
    //Faz essa operação até que h seja maior que comprimento/3.
    while(h < 10/3){
        h = h * 3 + 1;
    }


    while(h > 0){

        //Começa na posição h, e vai avançando de 1 em 1, comparando os valores do indice atual (x) com o índice de x-h até chegar ao final do vetor
        for(i = h; i < 10; i++){

            //Guarda o valor atual.
            aux = numeros[i]; 

            //compara enquanto o valor atual for menor que os anteriores a ele e não for o fim do vetor.
            for(j = i; (j>=h) && (aux < numeros[j - h]); j - h ){  

               //troco a posição dos elementos:
                numeros[j] = numeros[j-h]; 
            }   

            //Insere o valor no lugar do ultimo elemento maior que o valor..
            numeros[j] = aux; 
        }

        //Calcula os valores anteriores de h
        h = (h-1)/3; 
    }

    return 0;
}