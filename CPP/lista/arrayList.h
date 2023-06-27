/*Array-Based List
São listas que possuem tamanho fixo.
Desvantagens:
    Não pode expandir ou encolher.
    Se um elemento for removido é preciso mover todos os elementos p/ preencher o gap.
    Se o tamanho da lista for ultrapassado é preciso criar uma nova lista e migrar todos os elementos.    
*/

#include <iostream>
using namespace std;

#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

class Array_list{
private:
    int maxSize; //Tamanho máximo da lista
    int size; //Tamanho atual da lista
    int current; //item atual na lista
    int *list; //Lista

public:
    //Constructor
    Array_list(const int max)
        :maxSize{max}, size{0}, current{0} {
            list = new int[max];
    };

    //Destructor
    ~Array_list(){
        delete [] list;
    };

    //métodos da lista-------------

    //Reseta a lista
    void clear();

    //Verifica se a lista está cheia
    bool is_full();

    //Verifica se a lista está vazia
    bool is_empty();

    //Retorna a posição atual
    int current_position(){
        return current;
    }

    //retorna o valor da posição atual.
    int current_value();

    //Retorna quantos elementos tem na lista
    int length(){
        return size;
    }

    void print_list();

    //insere um elemento na posição atual
    void insert_current(const int value);

    //Insere o elemento no final da lista
    void insert_tail(const int value);

    //Insere o elemento no começo da lista
    void insert_head(const int value);

    //Remove o elemento da posição atual e o retorna.
    int remove_current();

    //Se movimentar pela lista:--------------------------

    //Vai para o primeiro elemento da lista
    void moveToHead(){
        current = 0;
    }

    //Vai para o último elemento da lista
    void moveToTail(){
        current = size-1;
    }

    //Vai para o elemento anterior ao atual
    void moveBack(){
        if(current != 0) current--;
    }

    //Vai para o elemento depois do atual
    void moveForward(){
        if(current < size-1) current++;
    }
};


void Array_list::clear(){
     size = current = 0;
        //Cria uma nova lista:
        delete [] list;
        list = new int[maxSize];
}

bool Array_list::is_full(){
    if(size == maxSize){
        cout << "Lista cheia!" << endl;
        return true;
    }

    return false;
}

bool Array_list::is_empty(){
    if(size == 0){
        cout << "Lista vazia!" << endl;
        return true;
    }

    return false;
}

int Array_list::current_value(){
    if(!is_empty()){
        return list[current];
    }
}

void Array_list::print_list(){
    if(is_empty()){
        return;
    }

    for(int i = 0; i < size; i++){
        cout << i+1 <<". " << list[i] << endl;
    }
}

void Array_list::insert_current(const int value){
    if(is_full()){
        return;
    }  

    //Move todos os elementos 1 casa pra trás:
    for(int i = size; i > current; i--){
        list[i] = list[i-1];
    }

    list[current] = value;

    size++;
}

void Array_list::insert_tail(const int value){
    if(is_full()){
        return;
    }

    //Insere na última posição e incrementa size ao mesmo tempo.
    list[size++] = value;
}

void Array_list::insert_head(const int value){
    if(is_full()){
        return;
    }

    //Move todos os elementos 1 casa pra trás:
    for(int i = size; i > 0; i--){
        list[i] = list[i-1];
    }

    list[0] = value;
    size++;
}

int Array_list::remove_current(){
    if(!is_empty()){
        int elem = list[current];

        //Move os elementos uma casa pra frente:
        for(int i = current; i < size; i++){
            list[i] = list[i+1];
        }

        size--;
        return elem;
    }
}



#endif 