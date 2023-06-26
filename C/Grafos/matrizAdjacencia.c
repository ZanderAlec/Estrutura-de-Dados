#include <stdio.h>
#include <stdlib.h>

 //Representação de grafos do tipo matriz de adjacência consistem em criar uma matriz de nxn, no qual n é a quantidade nós no grafo.
 //Cada linha receberá 0 se não houver conexão com o nó da coluna, ou 1 se tiver conexão.
 /*
    Ex:
         v1 | v2 | v3
    v1 |  0 | 1  | 0
    v2 |  1 | 0  | 0
    v3 |  1 |  1 | 0

grafo dirigido: aumenta a quantidade de 0
grafo com peso: substitui 1 pelo valor do peso

//Mais recomendado para grafos densos(Muitas arestas em relação ao número de nós), pois consome menos memória em relação a lista de adjacências.
Testar se existe aresta entre dois nós é mais rápido, basta ir na posição correspondente M[x,y];
Encontrar um nó anterior ao nó atual é mais fácil, basta olhar na coluna e vê quem aponta para esse nó.
 */


//Implentação:

//Nesse tipo de implementação, os nós não guardam informação, apenas a informação de conexão e peso.
//A informação se dá em uma estrutura a parte.
typedef struct grafo {
    int vertices; //Numero de vértices
    int arestas; //Numero de arestas
}GRAFO;

//representação de grafos tipo lista de adjacencias
//Nesse tipo de representação cada nó está contido em uma lista e possui, individualmente, uma lista de todos os nós a que está conectado.
/*
    v1 | -> |v2| -> |v3| 
    v2 | -> |v1| -> |v4|
    v3 | -> |v4| -> |v1|
    v4 | -> |v2| -> |v3|

grafo dirigido: diminui o tamanho da lista ligada individual de cada nó
grafo com peso: valor do peso contido dentro da estrutura de lista ligada indiviudal de cada nó

Mais recomendado em grafos esparsos(Poucas arestas em relação ao número de nós)
A busca é mais rápida em lista de adjacências, pois cada nó já possui a lista de elementos ligados a ele. Diferente da matriz que precisa ser varrida toda a linha.
*/

//Implementação

//Lista(individual) de elementos ligados ao nó.
typedef struct adjacencia{
    int vertice; // Valor do vertice em que a lista chega
    int peso; //Valor do peso
    struct adjacencia * prox; //Ponteiro para o prox elemento da lista ligada
}ADJACENCIA;

//Nó do vertice onde estará contido o valor.
typedef struct vertice{
    int valor;
    ADJACENCIA * primeiro; //primeiro elemento da lista de adjacencias (elementos ligados à um nó)
}VERTICE;

//LISTA ENCADEADA DOS GRAFOS TODOS
//É POR MEIO DELA QUE É POSSÍVEL TRANSITAR ENTRE OS ELEMENTOS
typedef struct grafo{
    int vertices; //número de vertices presentes na lista
    int arestas;  //número de arestas presentes na lista
    VERTICE * adj; //LISTA ENCADEADA
}GRAFO;


//Cria grafo sem aresta, porém com um número definido de relacionamentos.
//Recebe quantos relacionamentos esse grafo terá.
GRAFO * criaGrafo(int v){
    GRAFO * g  = (GRAFO*) malloc(sizeof(GRAFO));
    g->arestas = 0;
    g->vertices = v;

    //Cria a lista de adjancencias inteira de uma vez, mesmo que não exista elementos para preenche-la ainda.
    //Multiplicando v por sizeof, reservamos q quantidade de espaço necessário para toda a lista.    
    g->adj = (VERTICE*) malloc(v*sizeof(VERTICE)) ;

    //É importante determinar todos os espaços como NULL, pois os compiladores do C divergem na questão do que é colocado em espaços vazios.
    for(int i =0; i < v; i++){
        //É possível percorrer toda a lista como se fosse um vetor;
        g->adj[i].primeiro = NULL;
    }

    return (g);
};

//Cria a adjacencia para colocar no nó
//Recebe o nó final da aresta e o peso da aresta
ADJACENCIA * criaAdj(int v, int peso){  
    ADJACENCIA * temp = (ADJACENCIA*) malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return (temp);
}

//Vi = primeiro vertice
//vf = ultimo vertice
//p = peso;
int criaAresta(GRAFO * gr, int vi, int vf, int p){
    //Se o grafo não existir retorna falso.
    if(!gr){
        return 0;
    }

    //Valida se os valores não são negativos
    if(vf < 0 || vf >= gr->vertices){
        return 0;
    }

    //valida se os valores não são maiores que os numemeros dos grafos
    if(vi <0 || vi >= gr->vertices){
        return 0;
    }

    ADJACENCIA * novo = criaAdj(vf,p);
    novo->prox = gr->adj[vi].primeiro;
    gr->adj[vi].primeiro = novo;
    gr->arestas++;
    return 1;
}



int main(){
    return 0;
}