#include <iostream>

using namespace std;

class Node{
public:
    //valor do nó
    int value;
    //1º filho(menor q o pai)
    Node * left_child;
    //2º filho(maior q o pai)
    Node * right_child;

    //Constructor
    Node(int);
};

Node::Node(int v)
    :value{v}, left_child{nullptr}, right_child{nullptr}{
}

/*Os nós da árvore binária possuem um valor, e dois ponteiros para dois(max) filhos, "left-child" e "right-child"*/
class BinarySearchTree{
private:
    //Nó raiz
    Node * root;

    //métodos da árvore---------------------
    
    /*Quando se trata de objeto, as chamadas recursivas q precisam de um ponteiro q faz parte do próprio objeto
        torna-se redundante para ser chamado pelo usuário.
        Assim, esses métodos precisam ser chamados por outros métodos.
    */

    //delete_tree recebe o nó raiz, porém este método tem acesso ao nó raiz (redundante).
    //É por isso q é chamada por outra função.
    void delete_tree(Node * node);

    void print_tree(Node*&node);

     /*Encontra o pai(nó anterior) de um nó*/
    Node * find_Dad(Node*&temp);

    //procura o elemento que será removido.
    void remove_search(int, Node*&temp);

    //deleta um nó
    void delete_node(Node*& atual);

public:

    //₢onstructors
    BinarySearchTree();

    BinarySearchTree(int);

    //Destructor
    ~BinarySearchTree();

    //métodos da árvore---------------------

    //Verifica se a árvore está vazia
    bool is_empty();

    //Imprime a árvore
    void print();

    //Insere um nó na árvore
    //Valores menores q o nó raiz são colocados a esquerda, maiores a direita.
    void insert_node(int);

    //Remove um nó da árvore
    void remove_node(int);
};

BinarySearchTree::BinarySearchTree()
    :root{nullptr}{
}

BinarySearchTree::BinarySearchTree(int v){
   root = new Node(v);
}

BinarySearchTree::~BinarySearchTree(){
   delete_tree(root);
}


void BinarySearchTree:: delete_tree(Node * node){

    if(node == NULL){
        return;
    }

    delete_tree(node->left_child);
    delete_tree(node->right_child);

    delete node;
}

bool BinarySearchTree::is_empty(){
    return (root == NULL);
}

void BinarySearchTree::print(){
    print_tree(root);
    cout << endl;
}

void BinarySearchTree::print_tree(Node*&node){
    if(node != NULL){
        
        cout << node->value;

        if(node->left_child !=NULL){
            cout << "{" << node->left_child->value << "} ";
        } else{
             cout << "{ }";
        }

        if(node->right_child !=NULL){
            cout << "{" << node->right_child->value << "}" << endl;
        }else{
            cout << "{ }" << endl;
        }
        
        print_tree(node->left_child);
        print_tree(node->right_child);
    }
}

void BinarySearchTree::insert_node(int v){
    Node * temp = new Node(v);

    //Se a árvore está vazia, o novo nó é a raiz.
    if(is_empty()){
        root = temp;
        temp = nullptr;
        return;

    //Caso não esteja vazia, procura um nó cujo filho esteja vazio.
    //Nós maiores que o atual ficam a direita
    //menores ficam a esquerda.
    }else{

        Node * temp2 = root;

        while(true){

            if(v > temp2->value){
                
                if(temp2->right_child == NULL){
                    temp2->right_child = temp;
                    break;

                }

                temp2 = temp2->right_child;
                continue;
            }

            if(v < temp2->value){

                if(temp2->left_child == NULL){
                    temp2->left_child = temp;
                    break;
                }

                temp2 = temp2->left_child;
                continue;
            }
        }

        temp2 = nullptr;
    }

    temp = nullptr;
}


Node * BinarySearchTree::find_Dad(Node*&temp){
    Node * dad = root;

    while(true){

        //Se algum dos filhos é o valor procurado:
        if(dad-> left_child->value == temp->value || dad->right_child->value == temp->value){
            break;
        }

        //Se não entra em um dos filhos
        if(temp->value > dad->value){
            dad = dad->right_child;

        }else if(temp->value < dad->value){
            dad = dad->left_child;
        }
    }

    return dad;
}

void BinarySearchTree::remove_node(int v){
    remove_search(v, root);
}

void BinarySearchTree::remove_search(int v, Node*& atual){

    //Procura recursivamente o elemento passado
    if(v > atual->value){
        remove_search(v, atual->right_child);
    
    }else if(v < atual->value){
        remove_search(v, atual->left_child);

    }else{
        //Quando encontra deleta.
         delete_node(atual);
    }
}   

void BinarySearchTree::delete_node(Node*& atual){
    
    Node * temp = atual;

    if(atual->left_child == NULL){

        atual = atual->right_child;

    }else if(atual->right_child == NULL){

        atual = atual->left_child;
        
    }else{

        // Node * dad = find_Dad(atual);

        // if(dad->value > atual->value){
        //     dad->left_child = atual->right_child;

        // }else{
        //     dad->right_child = atual->right_child;
        // }

        // Node * temp2 = dad->right_child;

        // while(temp2->left_child){
        //     temp2 = temp2->left_child;
        // }

        // temp2->left_child = atual->left_child;

        // temp2 = nullptr;
    }

    // delete temp;
}


int main(){

    BinarySearchTree arvore {2};
    
    arvore.print();

    arvore.insert_node(5);
    arvore.insert_node(12);
    arvore.insert_node(6);
    arvore.insert_node(4);

    arvore.print();

    arvore.remove_node(5);

    arvore.print();


    return 0;
}