#include <stdio.h>
#include <stdlib.h>


//Lista ligada que guarda as adjacencias do vértice
typedef struct adj{
    int valor;
    struct adj * proximo;//proximo elemtno da lista
}listaAdjacencia;

typedef struct vertice{
    int valor; //Valor do vértice
    struct  vertice * proximo; //Proximo elemento da lista de vértices
    listaAdjacencia * primeiro; //Lista de adjacencias (vertice que o vértice está conectado)
}VERTICE;

//grafo como um todo. Guarda as informações gerais como numero de vértices, numero de arestas e o elemento mais recento do grafo. 
typedef struct grafo{
    int num_vertices;
    int num_arestas;
    VERTICE * listaVertices;
}GRAFO;

GRAFO * iniciaGrafo(){
    GRAFO * g = (GRAFO*) malloc(sizeof(GRAFO));

    if(g == NULL){
        return NULL;
    }

    g->num_vertices = 0;
    g->num_arestas = 0;
    g->listaVertices = NULL;

    return g;
}

//Cria um vértice sem aresta
VERTICE *criaVertice(int valor){
    VERTICE * g = (VERTICE*) malloc(sizeof(VERTICE));

    if(g == NULL){
        return NULL;
    }

    g->valor = valor;
    g->proximo = NULL;
    g->primeiro = NULL;

    return g;
}

listaAdjacencia *criaAdj(int valor){
    listaAdjacencia * novo = (listaAdjacencia*) malloc(sizeof(listaAdjacencia));

    if(novo == NULL){
        return NULL;
    }

    novo->valor = valor;
    novo->proximo = NULL;

    return novo;
}

//Procura um valor no grafo e retorna um ponteiro para a posição se encontrar
VERTICE * buscaValor(VERTICE * g, int valor){

    while(g != NULL && g->valor != valor){
        g = g->proximo;
    }

    return g;
}


//Quando um vértice é inserido no grafo, ele é inserido SEMPRE na primeira posição.
//Não permite repetição de valores no grafo.
void  insereVerticeGrafo(GRAFO * g, int valor){
    
    //se o grafo informado for nulo, cria um vértice e insere como o primeiro elemento do grafo.
    if(g->listaVertices == NULL){
        g->listaVertices = criaVertice(valor);
        g->num_vertices++;
        return;
    }
    //Se o grafo não for nulo,
    //Verifica se esse valor ja existe no grafo
    VERTICE * p  = buscaValor(g->listaVertices, valor);

    //Se o valor não existe na lista, coloca ele como primeiro. Se existir, não faz nada.
    if(p == NULL){
        //cria um vértice e o insere como primeiro elemento da lista de vértices.
        VERTICE * novo = criaVertice(valor);
        novo->proximo = g->listaVertices;
        g->listaVertices = novo;
        g->num_vertices++;
    }
}   

//Insere um valor na lista de adjacencias de um vértice
listaAdjacencia *  insereListaAdjacencia(listaAdjacencia * primeiro, int valor){

    if(primeiro == NULL){
        return criaAdj(valor);
    }

    //Assim, como na lista de vértices, a lista de adjacencia também coloca novos elementos no inicio da lista.
    listaAdjacencia * p = criaAdj(valor);
    p->proximo = primeiro;
    primeiro = p;


    return primeiro;
}

//Verifica seu uma relação já existe entre dois vertices.
listaAdjacencia * procuraAresta(listaAdjacencia * primeiro, int valor){

    if(primeiro == NULL){
        return (NULL);
    }

    listaAdjacencia * p = primeiro;

    while((p != NULL) && (p->valor != valor)){
        p = p->proximo;
    }

    return p;
}

//Cria a relação entre dois vértices,
//Ou seja, insere o valor deles na lista de adjacencias.
//ps: Essa implementação leva em conta que o grafo é orientado, portanto, apenas a lista de v1 é atualizada.
//Se fosse não-orientado, tanto v1 quanto v2 seriam atualizados.
void insereAresta(GRAFO * g, int v1, int v2){
    VERTICE * vert1 = buscaValor(g->listaVertices, v1);

    if(vert1 == NULL){
        return;
    }

    VERTICE * vert2 = buscaValor(g->listaVertices, v2);

    if(vert2 == NULL){
        return;
    }

    listaAdjacencia * p = procuraAresta(vert1->primeiro, v2);

    if(p == NULL){
        vert1->primeiro = insereListaAdjacencia(vert1->primeiro, v2);
    }

    g->num_arestas++;

}

void imprimeGrafo(GRAFO * g){
    VERTICE * v = g->listaVertices;

    while(v!= NULL){
        printf("%d |", v->valor);

        listaAdjacencia * p = v->primeiro;

        while(p!=NULL){
            printf("%d |", p->valor);
            p = p->proximo;
        }

        v = v->proximo;
        printf("\n");
    }
}


//Busca em largura---------------------------------------------------

//Coloca todos os indices do vetor como 0.
//0 = Não visitado.
void resetaVetor(int *v, int tam){

    for(int i = 0; i < tam; i++){
        v[i] = -1;
    }
}

//Recebe um valor a ser adicionado ao vetor.
void preencheVetor(int valor, int *v, int tam){
    
    for(int i = 0; i< tam; i++){
        if(v[i] == -1){
            v[i] = valor;
            break;
        }
    }
}

//Procura um valor no vetor;
int buscaVetor(int *v, int tam, int valor){

    for(int i = 0; i < tam; i++){
        if(v[i] == valor){
            return 1;
        }

        if(v[i] == -1){
            break;
        }
    }

    return 0;
}

VERTICE * verificaValores(GRAFO * g, VERTICE * v, int valorBusca, int *vet){

    int resultado = buscaVetor(vet, g->num_vertices, v->valor);

    if(resultado == 1){
        return NULL;
    }

    printf("vertice: %d\n", v->valor);

    preencheVetor(v->valor, vet, g->num_vertices);

    for(int i =0; i < g->num_vertices; i++){
        printf("%d ", vet[i]);
    }

    printf("\n");

    if(v->valor == valorBusca){
        return v;
    }

    listaAdjacencia * p  = v->primeiro;

    while(p != NULL){
        VERTICE * vert = buscaValor(g->listaVertices, p->valor);

        VERTICE * resp = verificaValores(g, vert, valorBusca, vet);
        if(resp != NULL){
            return resp;
        }

        p = p->proximo;
    }

    return NULL;

}

//A busca em profundidade é um algoritmo que verifica o vértice, o adjacente, o adjacente desse vértice e assim por diante.
//Visita sempre as camadas mais profundas até encontrar o resultado procurado ou esgotar todos os vértices.
//Nem sempre todos os vértices possuem arestas que os conectam, mas o algoritmo visita todos.
//Um vertice é visitado apenas uma única vez.
VERTICE * buscProfundidade(GRAFO * g, int valorBusca){
    
    int vet[g->num_vertices];
    resetaVetor(vet, g->num_vertices);

    VERTICE * p = g->listaVertices;

    while(p!=NULL){ 
        int existe = 0;

        while(p!=NULL){
            int resultado = buscaVetor(vet, g->num_vertices, p->valor);

            if(resultado == 1){
                existe = 1;
                p = p->proximo;
            }else{
                existe = 0;
                break;
            }
        }

        if(existe){
            break;
        }

        VERTICE * resp = verificaValores(g, p, valorBusca, vet);

        if(resp != NULL){
            return resp;
        }

        p = p->proximo;
    }

}

int main(){

    GRAFO * g = iniciaGrafo();

    insereVerticeGrafo(g, 4);
    insereVerticeGrafo(g, 24);
    insereVerticeGrafo(g, 2);
    insereVerticeGrafo(g,5);
    insereVerticeGrafo(g, 8);
    insereVerticeGrafo(g, 2);
    insereVerticeGrafo(g, 7);

    insereAresta(g, 2, 8);
    insereAresta(g, 2, 5);
    insereAresta(g, 5, 8);
    insereAresta(g, 4, 24);
    

    imprimeGrafo(g);

    VERTICE * result = buscProfundidade(g, 3);
    if(result == NULL){
        printf("O valor não está no grafo.\n");
    }else{
        printf("Valor encontrado!\n");
    }


    return 0;
}