#include <stdio.h>
#include <stdlib.h>

/*
    Problema do desenho da casa:
    O problema possui 6 vértices não-direcionados. O objetivo é percorrer todos as arestas que compões a figura da casa.
    Não pode:
        Retroceder caminhos. Ex: 6->1 e 1>6
        Percorrer um mesmo caminho dnv. Ex: 6->1 e 6->1

    Solução:
        Sempre começa no primeiro
*/

//lista de relações de um vértice
typedef struct adj{
    int valor; //indice do elemento que está relacionado ao vertice
    struct adj * prox; //Prox elemento da lista de adjacencias
}adjacencia;

//lista de vértices
//É um vetor, pois o numero de elementos é conhecido.
typedef struct vert{
    int valor;
    adjacencia * primeiro;
}vertice;

//Guarda as informações gerais a respeito dos grafos.
typedef struct{    
    //Guarda as adjacencias que ja foram visitadas pelo primeiro vértice.
    //É a condição de parada da operação.
    int indices[4]; 
    vertice * listaVertices;
}grafo;

//Lista do caminho percorrido pelo programa para encontrar a solução.
typedef struct listC{   
    int valorSaida; //sai de x
    int valorDestino;//vai para y
    struct listC * prox;
}listaCaminhos;



//Inicia a estrutura de grafo
grafo * iniciaGrafo(){
    grafo * novo = (grafo *) malloc((sizeof(grafo)));

    if(novo == NULL){   
        return NULL;
    }

    //Cria o vetor de vertices
    novo->listaVertices = (vertice *) malloc(6 * (sizeof(vertice)));
    
    //Preenche/null e zero os elementos da lista p/ garantir que o compilador não coloque nada diferente do esperado. 
    for(int i = 0; i<6; i++){
        novo->listaVertices[i].valor = 0;
        novo->listaVertices[i].primeiro = NULL;
    }

    for(int i = 0; i<4; i++){
        novo->indices[i] = 0;
    }

    return novo;
}

adjacencia * insereAdjacencia(adjacencia * primeiro, int valor){
    adjacencia * novo = (adjacencia * ) malloc(sizeof(adjacencia));

    if(novo == NULL){
        return NULL;
    }

    novo->valor = valor;

    //Se ainda a lista não é vazia, coloca o novo elemento como primeiro da lista.
    if(primeiro != NULL){
        novo->prox = primeiro;
    }
    
    return novo;
}

//Cria a estrutura(coloca vertice e relaciona-os) de casa do problema
void criaCasa(grafo * g){
    //g nunca será null, não precisa ser verificado.
    
    //Insere os vertices na lista de vertices
    //São colocados de trás pra frente, pois nos grafos o ultimo elemento adicionado é sempre o primeiro.
    //assim o vertice 1 será o ultimo.
    for(int i = 5, j = 1; i > -1; i--, j++){
        g->listaVertices[i].valor = j;
    }

    //Adjacencias do vertice 1 
    g->listaVertices[5].primeiro = insereAdjacencia(g->listaVertices[5].primeiro, 2);
    g->listaVertices[5].primeiro = insereAdjacencia(g->listaVertices[5].primeiro, 3);
    g->listaVertices[5].primeiro = insereAdjacencia(g->listaVertices[5].primeiro, 4);
    g->listaVertices[5].primeiro = insereAdjacencia(g->listaVertices[5].primeiro, 6);

    //Adjacencias do vertice 2 
    g->listaVertices[4].primeiro = insereAdjacencia(g->listaVertices[4].primeiro, 3);
    g->listaVertices[4].primeiro = insereAdjacencia(g->listaVertices[4].primeiro, 1);

    //Adjacencias do vertice 3 
    g->listaVertices[3].primeiro = insereAdjacencia(g->listaVertices[3].primeiro, 2);
    g->listaVertices[3].primeiro = insereAdjacencia(g->listaVertices[3].primeiro, 1);
    g->listaVertices[3].primeiro = insereAdjacencia(g->listaVertices[3].primeiro, 5);
    g->listaVertices[3].primeiro = insereAdjacencia(g->listaVertices[3].primeiro, 6);

    //Adjacencias do vertice 4 
    g->listaVertices[2].primeiro = insereAdjacencia(g->listaVertices[2].primeiro, 1);
    g->listaVertices[2].primeiro = insereAdjacencia(g->listaVertices[2].primeiro, 5);
    g->listaVertices[2].primeiro = insereAdjacencia(g->listaVertices[2].primeiro, 6);

    //Adjacencias do vertice 5 
    g->listaVertices[1].primeiro = insereAdjacencia(g->listaVertices[1].primeiro, 3);
    g->listaVertices[1].primeiro = insereAdjacencia(g->listaVertices[1].primeiro, 6);
    g->listaVertices[1].primeiro = insereAdjacencia(g->listaVertices[1].primeiro, 4);

    //Adjacencias do vertice6 
    g->listaVertices[0].primeiro = insereAdjacencia(g->listaVertices[0].primeiro, 3);
    g->listaVertices[0].primeiro = insereAdjacencia(g->listaVertices[0].primeiro, 4);
    g->listaVertices[0].primeiro = insereAdjacencia(g->listaVertices[0].primeiro, 1);
    g->listaVertices[0].primeiro = insereAdjacencia(g->listaVertices[0].primeiro, 5);
}

void imprimeGrafo(grafo * g){
    if(g != NULL){
        for(int i = 0; i<6; i++){
            printf("%d |", g->listaVertices[i].valor);

            adjacencia * p = g->listaVertices[i].primeiro;

            while(p != NULL){
                printf("%d |", p->valor);
                
                p = p->prox;
            }

            printf("\n");
        } 
    }
}

listaCaminhos * iniciaListaVazia(){
    return NULL;
}

listaCaminhos * insereNaListaCaminhos(listaCaminhos * lista, int inicio, int destino){
    listaCaminhos * novo = (listaCaminhos * ) malloc(sizeof(listaCaminhos));

    if(novo == NULL){
        return NULL;
    }
    
    novo->valorSaida = inicio;
    novo->valorDestino = destino;
    novo->prox = NULL;

    if(lista != NULL){
        listaCaminhos * p = lista;
        
        while(p->prox != NULL){ 
            p = p->prox;
        }

        p->prox = novo;
        
        return lista;
    }

    return novo;
}


int retornaIndice(grafo * g, int valorBuscado){

    for(int i = 0; i<6; i++){
        if(g->listaVertices[i].valor == valorBuscado){
            return i;
        }
    }
}

//Verifica se alguma caminho ou o oposto dele já foi tomado.
int procuraListaCaminhos(listaCaminhos * list, int valor1, int valor2){
    listaCaminhos * p = list;

    while(p != NULL){
        if(p->valorSaida == valor1 && p->valorDestino == valor2){
            return 1;
        }

        if(p->valorSaida == valor2 && p->valorDestino == valor1){
            return 1;
        }

        p = p->prox;
    }

    return 0;
}

//Essa função verifica se todos os caminhos foram percorridos.
int verificaResultado(grafo * g, listaCaminhos * lista){

    for(int i = 0; i< 6; i++){

        // printf("indice = %d\n", i);
        adjacencia * p = g->listaVertices[i].primeiro;

        // printf("primeiro = %d\n", p->valor);

        //Verifica se todos os filhos do vértice atual possuem um caminho com ele:
        while(p != NULL){
            int result = procuraListaCaminhos(lista, g->listaVertices[i].valor, p->valor);


            //Se algum n possuir, quer dizer que todos os caminhos não foram traçados.
            if(!result){
                return 0;
            }

            p = p->prox;
        }
    }

    //Se chegou até aqui, todos os caminhos foram traçados.
    return 1;
}


void limpaMatriz(int m[][4]){
    for(int x =0; x< 6; x++){
        for(int y = 0; y <4; y++){
            m[x][y] = 0;
        }
    }
}

void limpaVetor(int v[]){
    for(int i = 0; i<4; i++){
        v[i] = 0;
    }
}

void InsereVetor(int v[], int valor){
    for(int i = 0; i<4; i++){
        if(i == 0){
            v[i] = valor;
            break;
        }
    }
}

//Procura o ultimo elemento da lista e deleta ele.
//Retorna o caminho tomado nesse índice
listaCaminhos *  deletaElementoListaCaminhos(listaCaminhos * lista, int vet[]){
    listaCaminhos * l = lista;
    listaCaminhos * l2 = lista;

    while(l->prox != NULL){
        l = l->prox;

        if(l->prox != NULL){
            l2 = l;
        }
    }

    vet[0] = l->valorSaida;
    vet[1] = l->valorDestino;

    free(l);
    l2->prox = NULL;

    return lista;
}   


//Solução:
listaCaminhos * percorreCaminhos(grafo * g, listaCaminhos* lista, int m[][4]){
    
    //Esse loop mantém o algoritmo rodando até achar a solução.
    int indice = 1;

   while(1){

        adjacencia * p = g->listaVertices[indice].primeiro;
        int vpai = g->listaVertices[indice].valor;
        int resultado;

        //Procurar um indice não visitado
        while(p != NULL){   
            resultado = procuraListaCaminhos(lista, vpai, p->valor);

            if(resultado){
                p = p->prox;
                continue;
            }

            for(int y = 0; y < 4; y++){
                if(p == NULL){
                    break;
                }

                if(p->valor == m[indice-1][y]){
                    p = p->prox;
                    y = 0;
                }
            }

            break;
        }

        if(p == NULL){
            resultado = verificaResultado(g, lista);

            if(resultado == 1){
                return lista;
            }

            int vetTemp[2];

            lista = deletaElementoListaCaminhos(lista, vetTemp);

            InsereVetor(m[vetTemp[0]-1], vetTemp[1]);
            limpaVetor(m[vetTemp[1]-1]);

            indice = vetTemp[0];

            continue;
        }



        lista = insereNaListaCaminhos(lista, vpai, p->valor);

        listaCaminhos * l = lista;

        while(l != NULL){
            printf("%d | %d ->", l->valorSaida, l->valorDestino);
            l = l->prox;
        }
        printf("\n");

        indice = retornaIndice(g, p->valor);
   }
   
    
}

void imprimeCaminho(listaCaminhos * list){

    printf("Caminho:\n");
    
    listaCaminhos * l = list;
    while(l != NULL){
        printf("%d -> ",l->valorSaida);
        
        l = l->prox;  
    }

    printf("\n");
}



int main(){

    grafo * g = iniciaGrafo();
    criaCasa(g);

    imprimeGrafo(g);

    int m[6][4];
    
    limpaMatriz(m);

    listaCaminhos * l = iniciaListaVazia();
    l = percorreCaminhos(g, l, m);
    
    imprimeCaminho(l);

    return 0;
}