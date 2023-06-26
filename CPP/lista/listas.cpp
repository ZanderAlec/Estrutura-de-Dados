#include <iostream>

using namespace std;

/*
    Listas são definidas como uma sequência ordenada e finita de elementos.
    A ordem pode ou não representar grau de importância entre os elementos.

    Head: Primeiro elemento da lista
    Tail: Último elemento da lista.

    Na implementação de listas elas devem poder:
        ->Crescer a medida que adicionam elementos
        ->Diminuir conforme removem elementos
        ->Inserir elementos em qualquer parte da lista
        ->Remover elementos de qualquer parte da lista
        ->Criar a lista
        ->Limpar completamente a lista
        ->Acessar o anterior ou o próximo elemento a partir do elemento atual.(Conveniência)
   
*/

/*Array-Based List
São listas que possuem tamanho fixo.
Desvantagens:
    Não pode expandir ou encolher.
    Se um elemento for removido é preciso mover todos os elementos p/ preencher o gap.
    Se o tamanho da lista for ultrapassado é preciso criar uma nova lista e migrar todos os elementos.    
*/

class Array_list{
private:
    int maxSize; //Tamanho máximo da lista
    int size; //Tamanho atual da lista
    int current; //item atual na lista
    int *list; //Lista

public:
    //Constructor
    Array_list(int max)
        :maxSize{max}, size{0}, current{0} {
            list = new int[max];
    };

    //Destructor
    ~Array_list(){
        delete [] list;
    };

    //métodos da lista-------------

    //Reseta a lista
    void clear(){
        size = current = 0;
        //Cria uma nova lista:
        delete [] list;
        list = new int[maxSize];
    }

    //Verifica se a lista está cheia
    bool is_full(){
        if(size == maxSize){
            cout << "Lista cheia!" << endl;
            return true;
        }

        return false;
    }

    bool is_empty(){
        if(size == 0){
            cout << "Lista vazia!" << endl;
            return true;
        }

        return false;
    }

    int current_value(){
        if(is_empty()){
            return;
        }

        return list[current];
    }

    int length(){
        return size;
    }

    void print_list(){
        for(int i = 0; i < size; i++){
            cout << i+1 <<". " << list[i] << endl;
        }
    }

    //insere um elemento na posição atual
    void insert_current(const int value){
        if(is_full()){
            return;
        }

        //Move todos os elementos 1 casa pra trás:
        for(int i = size; i == current; i--){
            list[i] = list[i-1];
        }

        list[current] = value;
        size++;
    }

    //Insere o elemento no final da lista
    void insert_tail(const int value){
        if(is_full()){
            return;
        }

        list[size++] = value;
    }

    //Insere o elemento no começo da lista
    void insert_head(const int value){
        if(is_full()){
            return;
        }

        //Move todos os elementos 1 casa pra trás:
        for(int i = size; i == 0; i--){
            list[i] = list[i-1];
        }

        list[0] = value;
        size++;
    }

    //Remove o elemento da posição atual e o retorna.
    int remove_current(){
        if(is_empty()){
            return;
        }

        int elem = list[current];

        //Move os elementos uma casa pra frente:
        for(int i = current; i == size; i++){
            list[i] = list[i++];
        }

        size--;
        return elem;
    }

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
        if(current != 0){
            current = current--;
        }
    }

    //Vai para o elemento depois do atual
    void moveForward(){
        if(current < size-1){
            current = current++;
        }
    }

};

int main(){


    return 0;
}