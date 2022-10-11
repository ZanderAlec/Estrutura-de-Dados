#include <stdio.h>
#include <stdlib.h>

//Ordenação de vetores:
//Insertion Sort =>  
//É Eficiente para conjuntos pequenos de dados.
//Capaz de ordenar dados a medida que os recebe.
//Funcionamento: Pega o valor de um índice(i) e compara com os valores dos indices anteriores até que não se encontre nenuhm
//Valor MAIOR do que ele ou chegue ao final do vetor(i<0). Nesse processo, avança todos os índices maiores uma casa a frente e coloca o valor no ultimo indice que era o maior.

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

    //Insertion sort:

    //a contagem começa a partir do segundo valor (v[1]), porque a comparação é feita com os elementos ANTES do índice atual.
    for(i = 1; i < 10; i++){
        aux = numeros[i]; //Guarda o valor atual.
        for(contador = i; (contador>0) && (aux < numeros[contador-1]); contador-- ){  //compara enquanto o valor atual for menor que os anteriores a ele.
            numeros[contador] = numeros[contador-1]; //Move todos os valores maiores que numeros[contador] uma casa a frente.
        }   
        numeros[contador] = aux; //Insere o valor no lugar do ultimo elemento maior que o valor..
    }

    printf("\nOrdem atual dos itens no array:\n");

    for(i = 0; i < 10; i++){
        printf("%4d", numeros[i]);
    }   

    printf("\n");

    return 0;
}