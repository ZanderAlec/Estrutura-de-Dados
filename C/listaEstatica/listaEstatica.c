#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{ //Tipo que será armazenado e manipulado.
    char nome[31];
    int idade;
}Elem;

//É preciso ter noção da quantidade de elementos e do tamanho da lista que está sendo criada.
//Essa necessidade se dá pelo fato de precisar verificar se pode ou não adicionar/remover elementos.
typedef struct{
    Elem *elementos; //Ponteiro que aponta o endereço onde começa a lista.
    int quantidade, tamanho;
}ListaEstatica;

//Operações básicas--------------------------------------------------------------------

//Criar:==================================

//É preciso indicar a quantidade de memória que será alocada(o tamanho do vetor).

//É passado o ponteiro de lista, pois não está se criando uma nova INSTANCIA, mas sim acessando a já existente.
//Tam refere-se ao tamanho da lista
int criarLista(ListaEstatica *lista, int tam){

    //Elementos irá receber o endereço do início da memória alocada. 
    lista->elementos = calloc(tam, sizeof(Elem));

    //Verifica se a lista foi criada:
    if(lista->elementos == NULL){
        printf("Não ha espaco suficiente para criar a lista!\n");
        return 0;//falso
    }

    printf("Lista alocada com sucesso!\n");

    lista->tamanho = tam;
    lista->quantidade = 0; //Se criada com sucesso, a variável que controla o tamanho recebe o valor 0, pois ainda não há elementos na lista.

    return 1;
}

//Verificar vazia:==========================

//P/ verificar se a lista está vazia basta verificar se lista.quantidade é = 0;
//Por isso não precisa passar a lista por referência, pois nenhuma alteração no seu conteúdo será realizada.
int verificaVazia(ListaEstatica lista){
    return lista.quantidade == 0; //Retornará 0 ou 1.
}

//Verificar Cheia:============================

//Uma lista está cheia quando a quantidade de elementos armazenada for igual a quantidade de elementos que a lista suporta(tamanho);
//Por isso não precisa passar a lista por referência, pois nenhuma alteração no seu conteúdo será realizada.
int verificaCheia(ListaEstatica lista){
    return lista.quantidade == lista.tamanho; //retornará 0 ou 1;
}

//Verifica Quantidade de elementos============================

//Está operação apenas retorna a quantidade de elementos :b;

int verificaQuantElem(ListaEstatica lista){
    return lista.quantidade;
}

//INSERINDO ELEMENTOS-----------------------

//INSERIR NO INÍCIO===============

//A seguir as boas práticas de programação, o preenchimento do vetor será feito do começo para o final.
//Neste caso, começando da primeira posição e se esta estiver ocupada, deslocamos esse elemento para a próxima posição, então a primeira ficará disponível para o novo elemento.
//Após inserir o novo elemento, a variável que controla a quantidade de elementos deverá ter seu valor incrementado 1 unidade.

int inserirInicio(ListaEstatica *lista, Elem novo){

    //Verifica se há espaço na lista.
    if(verificaCheia(*lista)){
        printf("A lista está cheia. Não é possível inserir novos elementos.\n");
        return 0;
    }

    //passa todos os valores para o próximo "índice".
    //quantidade = ultimo índice do "vetor";
    //o primeiro índice é 0;
    for(int i = lista->quantidade; i > 0; --i){
        lista->elementos[i] = lista->elementos[i - 1];
    }

    //Atribui o novo elemento ao primeiro índice.
    lista->elementos[0] = novo;
    lista->quantidade++;
    return 0;
}


//Inserir Final =======================

//P/ inserir no final da lista(vetor), é preciso saber a quantidade de elementos que serão armazenados nesse vetor.
//Esse valor será controlado pela variável "quantidade". Se quantidade = 4, então os índices, 0,1,2 e 3 estarão ocupados e a próxima posição disponível é a do índice 4.

int inserirFinal(ListaEstatica *lista, Elem novo){

    if(verificaCheia(*lista)){
        printf("A lista está cheia. Não é possível adicionar nenhum novo elemento.\n");
        return 0;
    }

    lista->elementos[lista->tamanho] = novo; 
    lista->quantidade++;
    return 0;
}

//Imprimir elementos========================

//Os elementos são impressos do início até o final da estrutura.

int imprimirLista(ListaEstatica lista){

    for(int i = 0; i < lista.quantidade; ++i){
        printf("Nome: %s", lista.elementos[i].nome);
        printf("Idade: %d", lista.elementos[i].idade);
        printf("\n");
    }

    return 0;
}

//PESQUISAR ELEMENTOS==================

//A pesquisa tem por objetivo verificar se um determinado elemento está contido na lista. Ao encontrar o elemento a operação retorna o indicativo de sucesso.
//Caso contrário, retorna que não houve êxito na busca.

//Se o elemento for encontrado retonra sua posição, caso contrário retorna -1;
int pesquisarElemento(ListaEstatica lista, char *nome){
    
    for(int i = 0; i < lista.quantidade; ++i){
        if(strcmp(lista.elementos[i].nome, nome) == 0){
            return i ;
        }
    }
    return -1;
}


//Removendo elementos----------------------------------------------------------------

//REMOVER DO INÍCIO

//Remove o elemento que está armazenado na posição 0 do vetor.
//Depois de feita a remoção, todos os outros elementos deverão ser deslocados para o início do vetor. (Do segundo p/ o ultimo elemento)
//Após a remoção do elemento, a variável que controla a quantidade deverá ter seu valor decrementado em 1 unidade.

int removerInicio(ListaEstatica *lista, Elem *elem){

    if(verificaVazia(*lista)){
        printf("Não há nenhum elemento na lista. A remoção não é possível.\n");
        return 0;
    }

    //Retorna o elemento que foi removido.
    *elem = lista->elementos[0]; 

    //Decrementa a quantidade de elementos.
    --lista->quantidade;

    //Desloca todos os elementos restantes pro começo da lista.
    //Aqui que a remoção é feita.
    for(int i = 0; i < lista->quantidade; ++i){
        lista->elementos[i] = lista->elementos[i + 1];
    }

    return 0;
}


//REMOVER FINAL ==============

//A quantidade de elementos armazenados no vetor é que vai indicar a posição em que será realizada a remoção.
//Quando solicitada a remoção, a variável que controla a quantidade de elementos deve ser decrementada.
//Deve retornar a posição do elemento que foi removido.

int removerFim(ListaEstatica *lista, Elem *elem){

    if(verificaVazia(*lista)){
        return 0;
    }

    //Realiza o processo de decrementar e retornar o removido ao mesmo tempo
    *elem = lista->elementos[--lista->quantidade];
    
    //A "remoção" não ocorre realmente. A informação desse ultimo índice continua armazenada igualmente.
    //PORÉM, para o PROGRAMA  e a IDEIA de funcionamento dele, foi deletado.
    //O que acontece é que o programa vai IGNORAR a existencia desse valor. Isso porque a quantidade foi decrementada. MEsmo que a informação exista, esteja armazenada, o programa "vai" reconhecer essa posição como vazia.
    //Então, se for chamada a "preencheFinal", esse índice com esse valor será sobrescrito.

    return 0;
}

//REMOVER BUSCANDO ELEMENTO =============

//No caso de sucesso da remoção, os elementos que estão localizados consecutivamente na lista deverão ser deslocados. Semelhante ao que ocorre na remoção do início.
//Caso o elemento não conste na lsita, deverá ser informada a confirmação de erro.


int removerElemento(ListaEstatica *lista, Elem *elem){

    //Posicao do elemento
    int pos = pesquisarElemento(*lista, elem->nome);

    if(pos == 0){
        printf("O elemento informado não existe!\n");
        return 0;
    }else{
        
        //retorna o elemento que foi removido;
        *elem = lista->elementos[pos];

        //Desloca os elementos posteriores ao elemento removido.
        for(int i = pos; i < lista->quantidade; ++i){
            lista->elementos[i] = lista->elementos[i + 1];
            lista->quantidade--;
        }

        return 0;

    }

}

//Retorna quantas ocorrências tem o elemento.
int contaOcorrencias(ListaEstatica lista, char nome){
    int cont = 0;

    for(int i = 0; i < lista.quantidade; ++i){
        if(strcmp(lista.elementos[i].nome, nome) == 0){
            ++cont;
        }

    }

    return cont;
}


int main(){

    ListaEstatica newList; 
    ListaEstatica *plist = &newList;
    Elem novo;
    int tam;
    int resp;
    char temp;

    printf("\t===============Lista Estatica===============\n\n");

    printf("\tDigite quantos elementos terá a lista: ");
    scanf("%d", &tam);
    scanf("%c", &temp);

    criarLista(plist, tam);

    printf("Inserir um elem no final\n");

    printf("Insira o nome: ");
    scanf("%s", &novo.nome);

    printf("Insira a idade: ");
    scanf("%d", &novo.idade);

     printf("Insira o nome: ");
    scanf("%s", &novo.nome);

    printf("Insira a idade: ");
    scanf("%s", &novo.idade);


    inserirFinal(plist, novo);




    printf("tamanho: %d\n", newList.tamanho);
    printf("Nº itens: %d\n", newList.quantidade);
    printf("Começo da lista: %p\n", newList.elementos);



    


    return 0;
}
