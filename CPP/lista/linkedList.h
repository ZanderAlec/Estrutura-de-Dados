#include <iostream>

/*
    Lista linkada, diferente da arraylist, utiliza ponteiros para criar os elementos da lista conforme novos vão sendo acrescentados.
    Visto que cada elemento, é um "nó" da lista, os nós são uma classe á parte da lista.

    Existem ponteiros para o começo, o fim, e a posição atual na lista.
    Contudo, se a lista está vazia, isso gera casos especiais para as funções de "insert" e "remove"
    Para evitar esses casos, cria-se um nó fixo(header node) com valor nulo que é ignorado como parte da lista na execução do programa.
    Assim, se a lista está vazia todos os nós apontam para o header node.


    Vantagens:
        Inserir e remover simples -> Diferente do arrayList não precisa mover elementos.
        Tamanho infinito.
    
    Desvantagens:
        Diferente do arraylist não é possível ir diretamente para um nó. É preciso partir do começo da lista e seguir sequencialmente até o nó desejado.
        Ocupam mais memória, visto a necessidade de ponteiros.
        Tempo de acesso mais lento que arrayList.
*/
using namespace std;

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

/*Nó/Elemento da lista*/
class Node{
/*Os atributos da lista todos devem ser públicos, pois é outra classe (linkedlist) que irá modificá-los.
A quebra do princípio da encapsulação é apenas parcial, visto que a classe que irá manipular o nó terá o atributo "nó" como privado.
Assim, nenhuma outra parte do programa poderá manipular eles valores além dela.
*/
public:
    int valor;
    //Prox elemento da lista
    Node * prox;

    //constructor com parâmetro
    Node(int valor)
    :valor {valor}, prox{nullptr}{
    }

    //No args constructor
    Node(){
        Node(0);
    }
};

//Lista
class LinkedList{
private:
    //Primeiro elemento da lista
    Node * head;
    //Tamanho da lista
    int size;

public:
    //Constructor
    LinkedList()
    :head{nullptr}, size {0}{
    }

    //Destructor
    ~LinkedList();

    //Métodos-------------------------

    //Verifica se a lista está vazia
    bool is_empty();

    //Retorna o tamanho da lista
    int list_lenght();

    void print_list();

    //Insere um novo elemento no fim da lista
    void insereNo(int valor);

    //Exclui um elemento da lista
    void exclui_no(int indice);
};


LinkedList::~LinkedList(){
    Node * temp = nullptr;

    while(head){
        temp = head;
        head = head->prox;

        delete temp;
    }
}

bool LinkedList::is_empty(){
    if(size == 0){
        cout << "Lista vazia!" << endl;
        return true;
    }

    return false;
}

int LinkedList::list_lenght(){
    return size;
}

void LinkedList::print_list(){
    if(is_empty()){
        return;
    }

    Node * temp = head;

    int i = 1;
    while(temp){
        cout << i << ". " << temp->valor << endl;
        temp = temp->prox;
        i++;
    }
}

void LinkedList::insereNo(int valor){
    Node *novo = new Node(valor);

    //Se a lista está vazia head recebe o novo elemento, caso contrário procura um elemento 
    //que não possui irmão e insere nele.
    if(head == nullptr){
        head = novo;

    }else{
        Node * temp = head;

        while(temp->prox != NULL){
            temp = temp->prox;
        }

        temp->prox = novo;
    }
    
    size++;
}

void LinkedList::exclui_no(int indice){
    
    if(is_empty()){
        return;
    }

    //Se o indice passado for inválido
    if(indice > size){
        cout << "Elemento inexistente!" << endl;
        return;
    }
    
    Node * temp1 = head; 
    Node * temp2 = nullptr;

    //Excluir o primeiro elemento
    if(indice == 0){
        
        head = head->prox;

    }else{
        //Temp2 recebe o anterior ao elemento buscado
        //Temp 1 recebe o elemento buscado
        for(int i = 0; i <= indice; i++){
            temp2 = temp1;
            temp1 = temp1->prox;
        }

        //temp2 aponta para o elemento depois do buscado
        temp2->prox = temp1->prox;
  
    }

    //elemento buscado é deletado:
    delete temp1;
    size--;
}

#endif 