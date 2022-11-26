#include <stdio.h>
#include <stdlib.h>
/*
    Nessa variação de implementação cada nó da árvore corresponderá a um ÍNDICE da linked LIST e cada nó possuirá um ponteiro pra uma linked list com indices de todos os seus filhos.
    Cada nó possuirá um valor, um ponteiro para seu pai, um ponteiro para um vetor que contem a lista de todos os filhos desse nó e um ponteiro para o próximo elemento da lista de elementos.
*/

//Lista linkada:(filho dos nós)
typedef struct IL{
    //Endereço do elemento(No) contido nesse índice
    struct no * filho; 
    //Endereço para o próximo indice filho
    struct IL * proximo;
}itemLista;

//NO/LISTA LINKADA
typedef struct no{
    //Valor do no
    int valor;  
    //ponteiro para o pai desse no
    struct no * pai; 
    //Ponteiro para o primeiro indice da lista de filhos
    itemLista * listaFilhos;
    //Proximo nó da lista de nós
    struct no * proximo;
}NO;

//cria um item da lista de filhos
itemLista* criaItemlista(NO* filho){
    itemLista * novo = (itemLista*) malloc(sizeof(itemLista));

    if(novo == NULL){
        printf("Não há espaço suficiente pra criar a lista!\n");
        return NULL;
    }

    novo->filho = filho;
    novo->proximo = NULL;

    return novo;
}   

//Insere um no na lista de filhos (ja criada)
void insereItemLista(itemLista * primeiroFilho,  NO* filho){

    itemLista * item = primeiroFilho;

    while(item->proximo != NULL){
        item = item->proximo;
    }

    item->proximo = criaItemlista(filho);
}

//Cria um nó qualquer
NO * criaNo(int valor, NO * pai){

    NO * novo = (NO*) malloc(sizeof(NO));

    if(novo == NULL){
        return NULL;
    }

    novo->valor = valor;
    novo->pai = pai;
    novo->listaFilhos = NULL;
    novo->proximo = NULL;

    return novo;
}

//Cria o nó raiz
NO * iniciaArvore(int valor){
    criaNo(valor, NULL);
}

//Recebe o valor do nó pai, procura sua posição e retorna essa posição.
NO * buscaPai(int valor, NO* raiz){
    NO * indice = raiz;

    //Passa por todos os indices da lista até encontrar o pai ou até terminar a lista
    while(indice->valor != valor && indice->pai != NULL){
        indice = indice->proximo;
    }

    return indice;
}


//insere um nó na arvore
void insereNoArvore(NO * raiz, int valor, int valorPai){

    NO * pai = buscaPai(valorPai, raiz);

    //Como o endereço do pai já é passado, ele não precisa ser procurado.
    if(pai == NULL){
        return;
    }

    NO * filho = criaNo(valor, pai); 

    //Se o pai ainda não tem nenhum filho, cria a lista de filhos.
    if(pai->listaFilhos == NULL){
        pai->listaFilhos = criaItemlista(filho);

    //Se não, apenas insere o elemento.
    }else{
        insereItemLista(pai->listaFilhos, filho);
    }

    //procura um indice "vazio";
    NO* indice = pai;

    while(indice->proximo != NULL){
        indice = indice->proximo;
    }

    //Coloca o elemento filho, criado agora, como um dos itens da lista:
    indice->proximo = filho;

}

//Imprime a arvore de maneira recursiva
void imprimeArvore(NO * raiz){

    if(raiz != NULL){
        printf("%d( ", raiz->valor);

        itemLista * p  = raiz->listaFilhos;

        //Imprime todos os filhos
        while(p != NULL){
             imprimeArvore(p->filho);
             p = p->proximo;
        }
    }

    printf(")");
}


int main(){ 

    NO * r1 = iniciaArvore(2);
    NO * r2 = iniciaArvore(4);

    insereNoArvore(r1, 5, 2);
    insereNoArvore(r1, 6,  2);
    insereNoArvore(r1, 25, 6);
    insereNoArvore(r1, 1, 5);

    insereNoArvore(r2, 12, 4);
    insereNoArvore(r2, 2,  4);
    insereNoArvore(r2, 9, 12);
    insereNoArvore(r2, 1, 4);

    imprimeArvore(r1);
    printf("\n");
    imprimeArvore(r2);

    return 0;
}