#include <iostream>
#include "arrayList.h"
#include "linkedList.h"

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

int main(){

    //testes-----------------------------
    Array_list lista1 {5};

    cout << "Size: " <<  lista1.length() << endl;
    lista1.is_empty();

    lista1.insert_current(25);

    lista1.is_empty();
    lista1.print_list();

    lista1.insert_current(44);
    lista1.print_list();


    cout << lista1.current_position() << endl;
    cout << lista1.current_value() << endl; 

    lista1.moveToTail();

    cout << lista1.current_position() << endl;
    cout << lista1.current_value() << endl; 

    lista1.moveToHead();
    cout << lista1.current_position() << endl;
    cout << lista1.current_value() << endl; 

    lista1.insert_head(15);
    lista1.print_list();

    lista1.insert_tail(21);
    lista1.print_list();

    cout << lista1.current_position() << endl;
    cout << lista1.current_value() << endl; 

    lista1.remove_current();
    lista1.print_list();

    lista1.moveForward();

    cout << lista1.current_position() << endl;
    cout << lista1.current_value() << endl; 

    lista1.remove_current();
    lista1.print_list();

    lista1.clear();
    lista1.print_list();

    cout << endl;

    LinkedList lista2;

    lista2.is_empty();
    cout << "size: " << lista2.list_lenght() << endl;

    lista2.insereNo(66);
    lista2.print_list();

    lista2.insereNo(24);
    lista2.insereNo(82);
    lista2.print_list();

    cout << "size: " << lista2.list_lenght() << endl;
    
    lista2.exclui_no(1);
    lista2.print_list();
    cout << "size: " << lista2.list_lenght() << endl;
    return 0;
}