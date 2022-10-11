#include <stdio.h>
#include <stdlib.h>

//Ordenação de vetores:
//Selection sort => É uma versão melhorada do bubble sort.
        //          Seu funcionamento consiste em: passar o menor valor para o primeiro índice, o segundo menor para o segundo e assim por diante.


int main()
{

    int vet[10];
    int i, j, menor;
   
    int num, temp;
   
    for(i = 0; i < 10; i++){
        printf("Digite o %d numero: ", i+1);
        scanf("%d", &vet[i]);
    }
   
    printf("\nPrimeira ordenacao:\n");
   
    for(i = 0; i < 10; i++){
        printf("%d ", vet[i]);
       
    }


    //Selection sort:
   
    for(i = 0; i < 10; i++){ //Índice atual
        menor = i; //Assume que o índice atual possui o menor valor
       
        for(j = i; j <10 ; j++){ //Percorre todo o vetor a partir de i
            if(vet[menor] > vet[j]){
                menor = j;
            }
        }
       
        //Faz a troca do menor p/ o "primeiro" índice
       
        temp = vet[i];
        vet[i] = vet[menor];
        vet[menor] = temp;
         
    }
   
   
    printf("\nNova Ordencacao:\n");
   
    for(i = 0; i < 10; i++){
        printf("%d ", vet[i]);
    }
   
    printf("\n");

    return 0;
}