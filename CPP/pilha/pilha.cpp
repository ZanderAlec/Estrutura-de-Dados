#include <iostream>
#include <string.h>

using namespace std;

/*
    pilhas("stacks") são estruturas de dados nos quais os elementos só podem ser adicionados ou removidos
    apenas no começo ou no final.

    top -> elemento que pode ser acessado(está no topo) na pilha.
    push -> Operação de inserir um elemento no inicio/final da pilha.
    pop -> Operação de remover um elemento do final da pilha.

    //Uma pilha pode ser implementada array-based ou com ponteiros.
        ps:Array-based precisam de operações complexas quando ultrapassam o tamanho máximo.

    Pilha -> O primeiro a entrar é o último a sair. Ex: pilha de pratos.
    Fila -> variação da pilha no qual o primeiro a chegar é o primeiro a sair.

*/

/*Pilhas ligadas---------------------------------------*/

class Lista{
public: 
    string value;
    Lista * next;

    //Constructor
    Lista(string);
};

Lista::Lista(string v)
    :value{v}, next{nullptr}{
}

class Pilha{
private:
    //Tamanho da pilha
    int size;
    //primeiro elemento da pilha
    Lista * top;

public:
    //₢onstructor
    Pilha();

    //Destructor
    ~Pilha();

    //Métodos da pilha-----------

    //Verifica se a pilha está vazia
    bool isEmpty();

    //retorna o tamanho da pilha
    int stack_size() {return size;}

    void print_stack();

    //Insere elemento no topo da pilha
    void push(string);

    //Remove um elemento do topo da pilha
    void pop();

};

Pilha::Pilha()
    :size{0}, top{nullptr}{
}

Pilha::~Pilha(){
    Lista * temp;

    while(top){
        pop();
    }
}

bool Pilha::isEmpty(){
    if(size == 0){
        cout << "Pilha vazia!" << endl;
        return true;
    }

    return false;
}

void Pilha::print_stack(){
    if(isEmpty()) return;

    Lista * temp  = top;

    while(temp){
        cout << temp->value << endl;
        temp = temp->next;
    }
}

void Pilha::push(string name){

    Lista * elem = new Lista(name);

    if(isEmpty()){
        top = elem;
        elem = nullptr;

    }else{
        Lista * temp = top;
        top = elem;
        top->next = temp;
        temp = nullptr;
    }

    size++;
}

void Pilha::pop(){
    
    if(isEmpty()) return;

    Lista * temp = top;
    top = top->next;
    delete temp;
    size--;
}

int main(){

    Pilha p1;

    cout << p1.stack_size() << endl;
    p1.push("Prato 1");

    cout << p1.stack_size() << endl;

    p1.push("Prato 2");
    p1.push("Prato 3");

    cout << p1.stack_size() << endl;

    p1.print_stack();

    p1.pop();

    p1.print_stack();

    return 0;
}