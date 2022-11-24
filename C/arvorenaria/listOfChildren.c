#include <stdio.h>
#include <stdlib.h>

/*
    Nessa variação de implementação cada nó da árvore corresponderá a um ÍNDICE da linked LIST e cada nó possuirá um ponteiro pra uma linked list com indices de todos os seus filhos.
    Cada nó possuirá um valor, um ponteiro para seu pai e um ponteiro para um vetor que contem a lista de todos os filhos desse nó.

*/

//IMPLEMENTAÇÃO DA ÁRVORE-------------------------------------------------------------------
//linked list========================================================

//Essa lista linkada é a lista dos filhos de cada nó da árvore
typedef struct nof{

    int indice;
    struct nof * proximo; 

}no_filho;


//Cria um novo item no_filho e retorna esse item
no_filho * criaItem(int indice){
    
    no_filho * novo = (no_filho *)malloc(sizeof(no_filho));  

    if(novo  == NULL){
        return NULL;
    }

    novo->indice = indice;
    novo->proximo = NULL;

    return novo;
}


//Insere um item na lista de filhos de um nó
void inserirItemLista(no_filho * primeiro, int indice){

    if(primeiro != NULL){
        
        if(primeiro->proximo == NULL){
            primeiro->proximo = criaItem(indice);
            return;
        }

        no_filho * item =  primeiro->proximo;

        while(item->proximo!=NULL){
            item = item->proximo;
        }

        item->proximo = criaItem(indice);
    }
}

//Imprime a lista linkada de filhos
void imprimeLista(no_filho * primeiro){

    if(primeiro != NULL){
        
        printf("|%d| ", primeiro->indice);

        imprimeLista(primeiro->proximo);
        
    }
    printf("\n");

}

//ÁRVORE======================================================

//Nó da árvore:
typedef struct NO{
    int valor;
    int index_pai;
    no_filho * lista_filhos;
}no;

//Lista linkada que guardará os nós da árvore
typedef struct listA{
    struct NO * noArvore;
    struct listA* proximo;

}lista_arvore;

// cria o nó da arvore
no* criaNoArvore(int valor, int index_pai ){

    no * novo = (no* ) malloc(sizeof(no));

    if(novo == NULL){
        return NULL;
    }
    
    novo->valor = valor;

    //Se index for -1 então é o primeiro nó na arvore e o pai é null
    if(index_pai == -1){
        novo->index_pai = -1;
    }else{
        novo->index_pai = index_pai;
    }   
    
    novo->lista_filhos = NULL;

    return novo;
}

//Cria um novo indice na linked list de nós e insere o nó nesse indice
lista_arvore * criaIndiceArvore(int valor, int index_pai){

    lista_arvore * novoIndice = (lista_arvore*) malloc(sizeof(lista_arvore));

    if(novoIndice == NULL){
        return NULL;
    }

    novoIndice->noArvore = criaNoArvore(valor, index_pai);

    novoIndice->proximo = NULL;

    return novoIndice;
}

//Cria o primeiro indice da lista de nós/primeiro nó da lista:
lista_arvore * criaRaiz(int valor){
   return criaIndiceArvore(valor, -1);
}

//Procura na lista encadeada o indice informado, se existir retorna um ponteiro pra essa posição
lista_arvore * procuraPai(lista_arvore * raiz, int index_pai){

    lista_arvore * indice = raiz;

    for(int i = 0; i > index_pai; i++){

        if(indice == NULL){
            printf("Esse pai não existe!\n");
            return NULL;
        }

        indice = indice->proximo;
    }

    return indice;
}

//Procura um valor na lista e retorna, se encontrar, seu indice
int buscaIndicelista(lista_arvore * raiz, int valor){
    lista_arvore * temp = raiz;
    
    int indice = 0;

    while(temp != NULL){
         if(temp->noArvore->valor == valor){
            break;
        }
        
        indice++;
        temp = temp->proximo;
    }

    return indice;
}

//Insere um novo nó na árvore (novo elemento na lista encadeada)
void  inserirNoArvore(lista_arvore * raiz, int valor, int index_pai){

    //Verifica se a arvore ja foi iniciada
    if(raiz == NULL){
        printf("A arvore ainda não foi inicializada!\n");
        return;
    }

    //Verifica se o index do pai informado existe:
    lista_arvore * pai = procuraPai(raiz, index_pai);

    if(pai == NULL){
        printf("O indice informado não consta na lista.\n");
        return;
    }

    // //Cria o novo indice na lista:
    lista_arvore * indice = raiz;

    //procura um indice que não tenha proximo
    while(indice->proximo != NULL){
        indice = indice->proximo;
    }

    // //Cria o novo indice na arvore
    indice->proximo = criaIndiceArvore(valor, index_pai);


    //adiciona esse indice a lista de filhos do pai informado:-------
    int indiceFilho =  buscaIndicelista(raiz, valor);
   
    //Verifica se ja existe uma lista de filhos, se não existir cria uma
    if(pai->noArvore->lista_filhos != NULL){

        inserirItemLista(pai->noArvore->lista_filhos, indiceFilho);
    }else{
        pai->noArvore->lista_filhos = criaItem(indiceFilho);
    }

}   

void imprimeArvore(lista_arvore* raiz){
    if(raiz != NULL){

            lista_arvore* pai = raiz;

             printf("v  p  lf\n");

            while(pai != NULL){
                printf("|%d", pai->noArvore->valor);
                printf("|%d", pai->noArvore->index_pai);

                no_filho * filho =  pai->noArvore->lista_filhos;  

                while(filho != NULL){
                    printf("|%d", filho->indice);
                    filho = filho->proximo;
                }

                if(filho == NULL){
                    printf("|");
                }
                
                printf("\n");
                pai = pai->proximo;
            }
    }
}




//Operações-----------------------------------------------------------------------



int main(){

    lista_arvore* raiz = criaRaiz(2);


    inserirNoArvore(raiz, 4, 0);
    inserirNoArvore(raiz, 3, 0);
    inserirNoArvore(raiz, 77, 1);
    inserirNoArvore(raiz, 22, 0);
    
    imprimeArvore(raiz);



    return 0;
}