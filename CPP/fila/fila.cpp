#include <iostream>

using namespace std;

/*
    É uma estrutura do tipo lista cujos elementos são adicionados ao final e removidos do começo.
    Uma fila pode ser implementada array-based ou com lista linkada.

*/

class List{
public:
    int value;
    List * next;

    List(int);
};

List::List(int v)
:   value{v}, next{nullptr}{
}


class Queue{
private:
    //Tamanho da fila
    int size;   
    List * first;

public:
    //Constructor
    Queue();

    //Destructor
    ~Queue();

    void print_queue();

    int queue_size();

    //Verifica se a lista está vazia
    bool is_empty();

    //Insere elemento no fim da fila
    void arrival(int);

    //Remove elemento do começo da fila
    void pop();

};

Queue::Queue()
    :size{0}, first{nullptr}{
}

Queue::~Queue(){

    while(first){
        pop();
    }

}

void Queue::print_queue(){
    if(is_empty()) return;
    
    List * temp = first;

    while(temp){
        cout << temp->value << " ";
        temp = temp->next;
    }

    cout << endl;
}

int Queue::queue_size(){
    return size;
}

bool Queue::is_empty(){
    if(size == 0) return true;

    return false;
}

void Queue::arrival(int value){

    List * temp = new List(value);

    if(is_empty()){
        first = temp;
        temp = nullptr;
    }else{
        
        List * temp2 = first;

        while(temp2->next != nullptr){
            temp2 = temp2->next;
        }

        temp2->next = temp;
    }

    size++;
}

void Queue::pop(){
    if(is_empty()) return;

    List * temp = first;

    first = first->next;

    delete temp;
    size--;
}

int main(){

    Queue fila;

    cout << fila.is_empty() << endl;
    cout << fila.queue_size() << endl;

    fila.arrival(1);
    fila.arrival(2);

    cout << fila.is_empty() << endl;
    cout << fila.queue_size() << endl;

    fila.print_queue();

    fila.pop();

    fila.print_queue();

    return 0;
}