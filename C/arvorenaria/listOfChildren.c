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
    while(indice->valor != valor){
        indice = indice->proximo;
    }

    return indice;
}


//insere um nó na arvore
//PS: A árvore não aceita repetição.
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


//Operações=============================================================================


//Soma duas arvores de forma recursiva e o resultado é uma terceira árvore.
//A soma só é realizada com elementos que estão no mesmo nível e existem nas duas árvores.
NO * somaArvores(NO * r1, NO * r2, NO * rsoma){

    //Verifica se algum dos nós é nulo (Não existem 2 nós nas duas arvores nesse nível, logo a soma n é feita)
    if(r1 == NULL || r2 == NULL ){
        return NULL;
    }

    //Se existirem, soma os valores e insere na terceira árvore o resultado:
    int valor = r1->valor + r2->valor;

    if(rsoma == NULL){
        rsoma = iniciaArvore(valor);

    }else{
        insereNoArvore(rsoma, valor, (r1->pai->valor + r2->pai->valor));
    }

    //Verifica se os nós (r1 e r2) ambos possuem filhos/netos/... nos mesmos níveis:
    itemLista * f1 = r1->listaFilhos; 
    itemLista * f2=  r2->listaFilhos;

    while(f1 != NULL && f2 != NULL){
        somaArvores(f1->filho, f2->filho, rsoma);

        f1 = f1->proximo;
        f2 = f2->proximo;
    }

    //Retorna a árvore soma
    return rsoma;
}

//UNIÃO--------------------------------------------------------------
//Cria uma nova árvore identica a primeira
NO * copiaArvore(NO* r1, NO* r2){

    if(r1 == NULL){
        return NULL;
    }

    if(r2 == NULL){
        r2 = iniciaArvore(r1->valor);
    }else{
        insereNoArvore(r2, r1->valor, r1->pai->valor);
    }

    itemLista * p = r1->listaFilhos;

    while(p != NULL){
        copiaArvore(p->filho, r2);

        p = p->proximo;
    }

    return r2;
}

//Essa função copia uma árvore, mas como filha de outra árvore.
//Nessa representação de árvore, seria colocar as duas árvores, que estão em listas distintas, numa mesma lista.
//Recebe a arvore que vai ser inserida e a arvore que receberá.
NO *  insereArvore(NO * r1, NO* rUniao){

    if(r1 == NULL){
        return NULL;
    }

    //Se é o nó raiz, insere-o como filho da raiz da árvore rUniao
    if(r1->pai == NULL){
         insereNoArvore(rUniao, r1->valor, rUniao->valor);
    
    //Se não é o nó raiz, mantém a mesma relação de filhos que existia na árvore r1.
    }else{
        insereNoArvore(rUniao, r1->valor, r1->pai->valor);
    }   
   

    itemLista * p = r1->listaFilhos;

    while(p != NULL){
        insereArvore(p->filho, rUniao);

        p = p->proximo;
    }

    return rUniao;
}

//Essa função uni duas árvores
//Funcionamento: pega a raiz da segunda árvore e insere como filha da primeira
NO *  unirArvores(NO * r1, NO * r2){

    if(r1 == NULL || r2 == NULL){
        printf("É preciso duas árvores para realizar essa operação\n");
        return NULL;
    }

    NO * rUniao = NULL;

    //Copia a primeira arvore inteira:
    rUniao = copiaArvore(r1, rUniao);
    rUniao = insereArvore(r2, rUniao);

    return rUniao;
}


//pertence------------------------------------------------------------
//retorna 1 se o valor informado pertence a árvore, e 0 se não pertence.
int pertenceArvore(int valor, NO *  raiz){

    if(raiz == NULL){
        return 0;
    }

    //Percorre "indice" a "Indice" da lista buscando o valor:
    while(raiz!= NULL){
        if(raiz->valor == valor){
            return 1;
        }

        raiz = raiz->proximo;
    }

    return 0;
}

//Complemento-------------------------------------------------------
//Cria uma nova árvore com todos os elementos de uma árvore(r1) que não estão em outra(r2).
NO * complementoArvore(NO * r1, NO * r2, NO * rcomp){

    //Se o nó é vazio retorna
    if(r1 == NULL){
        return NULL;
    }   

    //Verifica se o valor do no pertence a arvore r2
    int resultado = pertenceArvore(r1->valor, r2);

    //Se não pertence, coloca na árvore:
    if(!resultado){

        //Se a árvore estiver vazia, esse nó será a raiz:
        if(rcomp == NULL){
            rcomp = iniciaArvore(r1->valor);
        }else{

            //Verifica se o pai do nó exsite na lista
            resultado = pertenceArvore(r1->pai->valor, rcomp);
            
            if(resultado){
                insereNoArvore(rcomp, r1->valor, r1->pai->valor);

            //Se não tiver vazia, mas pai desse nó não existir, então o nó raiz será o pai desse nó.
            }else{
                insereNoArvore(rcomp, r1->valor, rcomp->valor);
            }
        }      
    }

    itemLista * p = r1->listaFilhos;

    while(p != NULL){
        complementoArvore(p->filho, r2, rcomp);
        p = p->proximo;
    }

    return rcomp;
}

int main(){ 

    NO * r1 = iniciaArvore(2);
    NO * r2 = iniciaArvore(4);

    insereNoArvore(r1, 5, 2);
    insereNoArvore(r1, 6,  2);
    insereNoArvore(r1, 25, 6);
    insereNoArvore(r1, 1, 5);

    insereNoArvore(r2, 12, 4);
    // insereNoArvore(r2, 2,  4);
    insereNoArvore(r2, 9, 12);
    insereNoArvore(r2, 1, 4);
    
    imprimeArvore(r1);
    printf("\n");
    imprimeArvore(r2);
    printf("\n");

    NO * raizSoma = NULL;
    raizSoma = somaArvores(r1,r2, raizSoma);
    printf("Raiz Soma: ");
    imprimeArvore(raizSoma);
    printf("\n");

    NO * raizUniao = NULL;
    raizUniao = unirArvores(r1, r2);
    printf("Raiz União: ");
    imprimeArvore(raizUniao);
    printf("\n");

    NO * raizComplemento = NULL;
    raizComplemento = complementoArvore(r1,r2,raizComplemento);
    printf("Raiz Complemento: ");
    imprimeArvore(raizComplemento);
    printf("\n");


    return 0;
}