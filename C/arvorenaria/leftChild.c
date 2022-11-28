#include <stdio.h>
#include <stdlib.h>

//Árvore do tipo n-árias são árvores que cada nó pode ter um número de filhos que vai de 0 a n.
//Sendo n > 2. Não necessariamente precisa ter um LIMITE para N, assim cada nó podem ter quantos filhos necessários, depende do problema em questão.

//Diferente da binária, não há como saber ao certo quantos filhos cada nó terá, e mesmo que saibamos a criação de ponteiros para todos eles é inviável.
//Assim, cada nó terá, além do valor, um ponteiro para o PRIMEIRO FILHO e um ponteiro para o IRMÃO ao lado.


typedef struct no{
    int valor;
    struct no *primogenito; //Primeiro filho 
    struct no *irmao; //Irmão ao lado

}No;

No* criaNovoNo(int num){
    No* novo = (No*)malloc(sizeof(No)); //Alloca memória para o novo nó

    novo->primogenito = NULL; //o NÓ ainda não possui filhos
    novo->irmao = NULL; //O NÓ ainda não possui irmão
    novo->valor = num;
    return(novo);
}

//Não podemos começar uma nova árvore iniciando o primeiro nó como NULL, pois, diferente da binária, aqui não sabemos ao certo para o onde o elemento vai
//Por isso, na criação de cada nó é preciso ESPECIFICAR QUEM É O PAI.
//Inicializa cria um nó na memória e retorna o endereço desse nó.
No* inicializa(int num){
    return(criaNovoNo(num));
}

//procura um valor na árvore e retorna o ponteiro para esse valor.
//A busca na árvore n-ária não é tão rápida quanto a binária, pois não há critérios. Então não é possível mais apenas excluir uma parte da árvore na busca, agora, é preciso varrer a árvore por completo.
No * buscaValor(int valor, No* raiz){
    if(raiz == NULL){
        return NULL; //Não há elementos na árvore.
    }

    if(raiz->valor == valor){ //Verifica se o valor está na raiz
        return raiz;
    }

    No *p = raiz->primogenito; //se não encontra no pai, procura no filho.

    while(p){ //e p/ cada filho buscamos na subárvore em que ele é a raiz
        No* resp = buscaValor(valor,p); //chamada recursiva
        if(resp){  //Verifica se encontrou um valor
            return resp;
        }
        p = p->irmao;
    }

    return (NULL);
}

//A função inserir deve receber o primeiro nó, o valor a ser colocado na árvore e o valor do elemento pai(pai do novo nó que será criado)
int inserir(No* raiz, int valor, int valorPai){
    No* pai = buscaValor(valorPai, raiz); //Procura o pai informado na árvore
    if(!pai){  
        return 0;
    }
    No* filho = criaNovoNo(valor); //Cria o nó do filho
    No* p = pai->primogenito; //verifica se o pai já tem um filho

    if(!p){ //Se não tiver filho, o novo nó será o primogênito
        pai->primogenito = filho; 
    
    }else{//Se ja tiver um filho

        while(p->irmao){ //Passa pelos filhos até encontrar um que tenha irmão = NULL;
            p = p->irmao; //Enquanto isso, auxiliar vai passando de irmão em irmão até encontrar o que tenha valor NULL.
        }

        //Após encontrado:
        p->irmao = filho;
        return 1;
    }
}

void imprimeArvore(No* raiz){

    if(raiz == NULL){ //Verifica se há elementos na raiz
         return;
    }

    printf("%d(", raiz->valor); //Imprime o valor do nó atual
    No *p = raiz->primogenito; //guarda o primeiro filho num vetor temporário

    while(p){ //Imprime de forma recursiva, um nós filho(sub-arvore) e depois os filhos desse nó, até imprimir toda a árvore.
        imprimeArvore(p);
        p = p->irmao;
    }
    printf(")");
}

//Exclusão:
//A exclusão na arvore n-ária depende do contexto em que ela será utilizada.
//Ela pode nem ser necessária. E caso seja, tem que decidir se os filhos do nó também serão excluídos ou se serão adotados.
//E se adotados, por quem serão? pelo pai do nó excluído ou por seus irmãos?


int main(){


    No* raiz = inicializa(8); //Cria o primeiro nó da árvore.
    return 0;
}