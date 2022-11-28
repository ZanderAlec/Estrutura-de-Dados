#include <stdio.h>
#include <stdlib.h>

/*  
     Essa implementação é basicamente indentica a lista de filhos, cada nó vai ter armazenado um 
     valor um ponteiro para uma lista linkada de ponteiros que apontam para os filhos desse nó.
    A principal diferença entre as implementações está no fato de que no dynamic node os nós não 
    estão contidos em uma lista linkada como era na lista de filhos.
*/

typedef struct itemL{
    struct no * filho;
    struct itemL * proximo;
}Lista;

typedef struct no{
    int valor;
    Lista * Listafilhos;
}NO;

//Cria uma nova lista
Lista * criaItemLista(NO * filho){
    Lista * nova = (Lista*) malloc(sizeof(Lista));

    if(nova == NULL){
         printf("Não há espaço suficiente para criar a lista!\n");
        return NULL;
    }

    nova->filho = filho;
    nova->proximo = NULL;

    return nova;
}

//Insere um elemento em uma lista ja criada
void insereLista(Lista * primeiro, NO * filho){

    Lista * p = primeiro;

    while(p->proximo != NULL){
        p->proximo;
    }

    p->proximo = criaItemLista(filho);
}

//Cria um nó da árvore
NO * criaNo(int valor){
    
    NO * novo = (NO * ) malloc(sizeof(NO));

    if(novo == NULL){
        printf("Não há espaço suficiente para criar o nó!\n");
        return NULL;
    }

    novo->valor = valor;
    novo->Listafilhos = NULL;
}

//Procura recursivamente seu um valor existe na árvore, se existir retorna o ponteiro pra essa posição.
NO * procuraValor(NO * raiz, int valor){

    if(raiz == NULL){
        return NULL;
    }
    
    //Se é a posição ,retorna
    if(raiz->valor == valor){
        return raiz;
    }

    //Se não é procura entre os filhos, netos, bisnetos...
    Lista * p = raiz->Listafilhos;

    while(p != NULL){

        NO * result = procuraValor(p->filho, valor);

        if( result != NULL){
            return result;
        }

        p = p->proximo;
    }

    // //Se não retornou ainda, retorna NULL, pois esse valor não existe.
    return NULL;
}

void insereNoArvore(NO * raiz, int valorPai, int valor){
    NO * pai = procuraValor(raiz, valorPai);

    if(pai == NULL){
        printf("Esse pai não existe na árvore!\n");
        return;
    }  

    NO * filho = criaNo(valor);

    //Se ainda não tem filhos, cria uma nova lista e insere esse filho nela
    if(pai->Listafilhos == NULL){
        pai->Listafilhos = criaItemLista(filho);

    //Se já tem, apenas insere o filho na lista
    }else{
        insereLista(pai->Listafilhos, filho);
    }
}

//Imprime a árvore recursivamente
void imprimeArvore(NO * raiz){
    
    if(raiz != NULL){
        printf("%d\n", raiz->valor);   

        Lista * p = raiz->Listafilhos;

        while(p != NULL){
            imprimeArvore(p->filho);
            
            p = p->proximo;
        }

    }
}


int main(){

    NO * raiz = criaNo(2);

    insereNoArvore(raiz, 2,  5);
    insereNoArvore(raiz, 5,  22);
    insereNoArvore(raiz, 2,  7);
    insereNoArvore(raiz, 9,  5);

    imprimeArvore(raiz);


    return 0;
}