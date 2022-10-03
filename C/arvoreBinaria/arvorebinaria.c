#include <stdio.h>
#include <stdlib.h>

//O nó de uma árvore é composto de 3 partes:
// O valor, um ponteiro para  uma sub-ávore esquerda e um ponteiro para  uma sub-ávore direita;

typedef struct no{
    int valor;
    struct no* esq; //sub-arvore esquerda
    struct no* dir; //sub-arvore direita
}noArvore;


//Função que cria o primeiro nó da árvore;
noArvore * CriaRaiz(){
    return NULL; //retorna uma árvore com nenhum elemento, ou seja vazia. 
}


//Inserir na árvore:
void inserirNo(int valor, noArvore ** no){

    if(*no == NULL){

        *no = (noArvore*)malloc(sizeof(noArvore)); //Aloca memória do tamanho da estrutura nó

        (*no) -> esq = NULL; //sub-arvore esquerda ainda não terá nada
        (*no) -> dir = NULL; //sub-arvore direita ainda não terá nada
        (*no) -> valor = valor; //Guarda o valor nesse nó
   
    }else{

        if(valor > (*no)->valor){
            inserirNo(valor, &(*no)->dir);

        }else if(valor < (*no)->valor ){
             inserirNo(valor, &(*no)->esq);
        }
    }
}


//Essa função mostra todos os elementos da árvore de forma recursiva.
void imprimirArvore(noArvore* raiz){
    
    if(raiz != NULL){ 

        printf("%d ", raiz->valor); //Mostra a raiz
        imprimirArvore(raiz->esq); //Mostra a sub-árvore esquerda
        imprimirArvore(raiz->dir); //Mostra a sub-árvore direita

    }
}


//procura o valor informado e, se achar, retorna o nó que possui o valor.
//A função procura em apenas um lado da raiz baseando-se na idéia de que valores menores estão de um lado e maiores do outro.
noArvore * procuraNo(int valor, noArvore* no){

    if(no != NULL){ //Verifica se a árvore não está vazia
 
        if(valor == no->valor){ //Verifica se o nó atual possui o valor procurado
            printf("\nO valor procurado existe na arvore\n");
            return no;
        }

        printf("\nnao era igual\n");

        if(valor > no->valor){ //Se o valor informado for maior, procura na  sub-arvore direita
            procuraNo(valor, no->dir);

        }else if(valor < no->valor){ //Se o valor informado for menor, procura na  sub-arvore esquerda
            procuraNo(valor, no->esq);
        }
   
    }

    printf("\nO valor procurado não existe na arvore\n");
    return NULL;
}


int main(){

    noArvore * raiz = CriaRaiz(); //Cria a árvore, ou seja o primeiro nó(raiz).
    int num;
    int opcao, rodando = 1;

    do{
        
        printf("O que deseja fazer?\n1 - inserir\n2 - mostrar Arvore\n3 - Excluir elemento\n4 - sair\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &num);
            inserirNo(num, &raiz);
        break;

        case 2: 
            imprimirArvore(raiz);
            printf("\n");
        break;

        case 3:
            printf("Digite um valor: ");
            scanf("%d", &num);
            procuraNo(num, raiz);
        break;

        case 4:
            printf("Saindo...\n");
            rodando = 0;
        break;
        
        default:
            printf("A opcao escolhida nao e valida!\n");
        break;
        }
    

    }while(rodando);


    

    

    return 0;
}
