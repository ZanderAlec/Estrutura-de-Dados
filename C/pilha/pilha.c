#include <stdio.h>
#include <stdlib.h>

//push é o processo de empurrar elementos para o tipo de estrutura de dados pilha.
//Ou seja, é como os elementos são colocados no topo da pilha

//Empilhar
//A construção da pilha será feita sempre usando struct, porque além do elemento em si, qualquer elemento da pilha precisa ter um ponteiro que aponta para o próximo elemento ("está embaixo" dele).
//Além disso, também serão usados ponteiros p/ apontarem para esses elementos.
//O ponteiro que marca o topo da pilha será inicialmente apontado para NULL se a pilha estiver vazia.
//O ponteiro do ultimo elemento sempre será NULL.


//P/ desempilhar
//1- É preciso ter um ponteiro auxiliar que apontará para o elemento que está no topo da pilha.
//2- Depois, o ponteiro que guarda o topo, aponta para o próximo elemento.
//3 - Depois, utiliza a informação como precisa e libera a memória, excluindo aquela informação. 


typedef struct {
    int dia, mes, ano;
}Data;

typedef struct{
    char nome[50];
    Data data;
}Pessoa;

typedef struct no{
    Pessoa p;
    //o ponteiro criado é do tipo no, porque o ponteiro precisa ter o mesmo tipo de dado para o qual ele irá apontar.
    struct no *proximo; //Aponta para o próximo elemento da pilha. A
}No;

Pessoa ler_pessoa(){
    Pessoa p;

    printf("\nDigite nome e data de nascimento (dd mm aaaa)\n");
    scanf("%49[^\n]%d%d%d", p.nome, p.data.dia, p.data.mes, p.data.ano); 

    return p;
}

void imprimir_pessoa(Pessoa p){
    printf("\nNome: %s\ndata: %2d/%2d/%4d\n", p.nome, p.data.dia, p.data.mes, p.data.ano);
}

// função para a operação push (empilhar)==================================================

//Recebe como parametro o ponteiro do topo.
//o tipo é NO* e não *NO como de costume porque indica retorno.
No* empilhar(No *topo){
    //Quando empilhamos, estamos criando um novo NÓ. Que será aquele que o *topo pegará como referencia.
    No *novo = malloc(sizeof(No)); //Alocação dinâmica de memória

    //Importante verificar se a memória foi alocada ou o programa poderá travar.
    if(novo){

        //Ps as setas tem a mesma função do ponto("."). Porém, são necessárias aqui por novo(variável) tratar-se de um ponteiro.
        //estamos criando uma nova pessoa
        novo -> p = ler_pessoa();
        //Além disso, é preciso que o proximo (ponteiro que aponta para o elemento debaixo da pilha) deve apontar para o topo(elemento que está no topo) atual.
        //Isso porque estamos colocando um novo elemento no "topo" da pilha.
        novo -> proximo = topo;

        //Depois, precisamos retornar o novo, que é o ponteiro para o nó. Pois, essa função será chamada pelo ponteiro do topo que precisará apontar para o novo elemento que está em cima da pilha.
        return novo;
        
    }else{//Caso não seja possível alocar memória.
        printf("\nErro ao alocar memoria...\n");
        return NULL; //É preciso retornar NULL aqui para que o ponteiro do topo continue não apontando para nada.
    }

}   

//Operação de pop()========================================================================

//Recebe como parâmetro um ponteiro de ponteiro, pois é preciso modificar o endereço para o qual o topo aponta (o elemento embaixo do elemento que foi removido)
//Assim, é recebido um ponteiro, que aponta para outro ponteiro, que possui esse endereço.
//Porque não retornar o novo enderço do topo?
//Essa função retorna o endereço que foi desempilhado (topo da pilha), pois em um programa real é feito algo com o que foi desempilhado.
//Assim, a função desempilhar fica exclusiva para direcionar o novo endereço e outra parte do código realizaria ação.
No *desempilhar(No **topo){
       if(*topo != NULL){ //Verifica se a pilha não é vazia.

        No *remover = *topo; //Guarda o endereço do elemento que está no topo da pilha (será removido);
        *topo = remover -> proximo; //Atribui ao topo o endereço que está embaixo de quem será removido.
        return remover; //Retorna o endereço do elemento que foi removido

    }else{
        printf("\nPilha vazia!\n");
        return NULL;  //Se não há elemento, retorna nulo.
    }
}

int main(){

    //o ponteiro criado é do tipo no, porque o ponteiro precisa ter o mesmo tipo de dado para o qual ele irá apontar.
    No *topo = NULL; //topo da pilha. Receberá null como default pq inicialmente a pilha não terá elementos.
    No *remover;
    int opcao;

    do{
        printf("\n0 - sair\n1 - Empilhar\n2 - Desempilhar\n3 - Imprimir\n");
        scanf("%d", &opcao); 
        getchar(); //Pra limpar o buffer do teclado.
    
        switch(opcao){
            case 1: 
                topo = empilhar(topo);
                break;
            
            case 2:
                remover = empilhar(&topo);

                if(remover != NULL){
                    printf("\nElemento removido com sucesso!\n");
                    imprimir_pessoa(remover->p);

                    free(remover); //Liberamos a memória do elemento que foi removido;
                }else{
                    printf("\nSem no a remover");
                }

                break;

            case 3:
                break;

            default:
                if(opcao != 0){
                    printf("\nOpcao invalida!!!\n");
                }
        }

    }while(opcao != 0);
    

    return 0;
}
