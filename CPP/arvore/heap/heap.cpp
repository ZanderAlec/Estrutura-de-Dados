#include <iostream>

//Possui os valores máximos permitidos pelo compilador dos tipos de dados padrão.
#include <climits>

using namespace std;

/*
    Heap -> É uma coleção de objetos organizados por importância ou prioridade (lista de prioridade). 
        Uma lista(queue) não pode ser utilizada, pois o tempo necessário para procurar o elemento de maior prioridade
        levaria muito tempo.

    Na heap, os elementos já são parcialmente organizados desde a sua inserção na estrutura:
        max-heap:
            Cada nó da heap é MAIOR ou IGUAL ao de seus filhos.
            raiz tem o maior valor da lista.
            
        min-heap:
            Cada nó da heap é MENOR que o de seus filhos.
            raiz tem o menor valor da lista.

    A implementação é feita usando uma estrutura de  arvore binária completa, que é representada como um array.
    Diferente da árvore binária de busca, a heap não precisa necessáriamente armazenar os valores menores a esquerda
    e os maiores a direita da raiz.  
*/

class MinHeap{
private:
    //Array de elementos da heap;
    int *heap_array;
    //Tamanho máximo da heap
    int max_size; 
    //Tamanho atual da heap;
    int heap_size;

public:
    //Constructor
    MinHeap(int);

    //Destructor
    ~MinHeap();

    //Métodos da heap------------

    void printHeap();


    //Transforma uma arvore em heap.
    //No caso, coloca todos os nós, como os índices do array.
    //O processo ocorre por camadas, todos os nós da camada são colocados um após o outro até o fim da árvore.
    
    //recebe um index e troca ele de lugar, no caso da min-heap, com um filho que seja MENOR que ele.
    //É utilizado quando o menor elemento é removido do array, dessa forma, o último elemento toma o lugar do antigo menor e o array é rearranjado
    void minHeapify(int);

    //Verifica se a heap está cheia
    bool is_full();

    //Retorna o pai de um nó.
    int getParent(int);

    //Retorna o filho esquerdo de um nó
    int getLeftChild(int);

    //Retorna o filho direito de um nó
    int getRightChild(int);

    //Retorna a raiz(primeiro elemento do vetor)
    int returnMin();

    //Remove o elemento raiz do vetor
    int releaseMin();

    //Muda o valor de um index e o posiciona na posição correta
    void decreaseKey(int, int);

    //Deleta um valor na heap no index passado
    void deleteKey(int);

    //Insere um valor na heap
    void insertKey(int);
};

MinHeap::MinHeap(int max)
    :max_size{max}, heap_size{0}{  
    heap_array = new int[max];
}

MinHeap::~MinHeap(){
    delete [] heap_array;
}

void MinHeap::printHeap(){
    for(int i =0 ; i < heap_size; i++){
        cout << heap_array[i] << " ";
    }

    cout << endl;
}

int MinHeap::getParent(int index){
    return (index-1)/2;
}

int MinHeap::getLeftChild(int index){
    return (index*2)+1;
}

int MinHeap::getRightChild(int index){
    return (index*2)+2;
}

int MinHeap::returnMin(){
    if(heap_size == 0){
        cout << "Heap vazia!" << endl;
        return -1;
    }

    return heap_array[0];
}

int MinHeap::releaseMin(){
    if(heap_size == 0) return INT_MAX;

    if(heap_size == 1){
        heap_size--;
        return heap_array[0];
    }

    int min = heap_array[0];
    heap_array[0] = heap_array[heap_size -1];
    heap_size--;
    minHeapify(0);

    return min;
}

bool MinHeap:: is_full(){
    return (heap_size == max_size);
}

void MinHeap::insertKey(int value){
    if(is_full()){
        cout << "Heap cheia!" << endl;
        return;
    }

    //Insere o novo elemento no fim da heap
    heap_size++;
    int i = heap_size -1;   
    heap_array[i] = value;

    //troca os filhos e pais de lugar se os filhos forem menores q os pais:
    for(i; i != 0; i--){
        int dad = getParent(i);

        if(heap_array[dad] > heap_array[i]){
            
            int temp = heap_array[dad];
            heap_array[dad] = heap_array[i];
            heap_array[i] = temp;

            i = dad;

        }else{
            break;
        }
    }
}

void MinHeap::minHeapify(int i){
    
    //O valor recebido é dado como menor, se ele se manter assim até o final, o vetor esta ordenado.
    int smallest = i;
    int lc = getLeftChild(i);
    int rc = getRightChild(i);

    //Se o filho esquerdo é menor que o pai informado(i)
    if(lc < heap_size && heap_array[lc] < heap_array[i])
        smallest = lc;

    //Se o filho esquerdo é menor que o pai informado(i) ou o filho direto
    if(rc < heap_size && heap_array[rc] < heap_array[smallest])
        smallest = rc;
    
    //Se não foi alterado, encerra
    if(smallest != i){
        //Troca de lugar
        int temp = heap_array[i];
        heap_array[i] = heap_array[smallest];
        heap_array[smallest] = temp;

        //Chama novamente pro novo menor
        minHeapify(smallest);
    } 
};

void MinHeap::decreaseKey(int i, int val){
    heap_array[i] = val;

    //O elemento é posicionado de forma a atender a prioridade
    //O posicionamento leva em conta apenas os pais dos índices, visto que trata-se na verdade de uma ÁRVORE binária.
    //Portanto, se temos a ÁRVORE binária o programa considera que os filhos são sempre menores que os pais.
    while(i != 0){
        int dad = getParent(i);
        if(heap_array[dad] < heap_array[i]) break;
        
        else{
            int temp = heap_array[dad];
            heap_array[dad] = heap_array[i];
            heap_array[i] = temp;
        }

        i = dad;
    }
}

void MinHeap::deleteKey(int i){
    decreaseKey(i, INT_MIN);
    releaseMin();
}

int main(){

    MinHeap h{8};

    cout << h.is_full() << endl;

    h.insertKey(11);

    h.printHeap();

    h.insertKey(3);
    h.insertKey(2);
    h.insertKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);

    h.printHeap();

    cout << h.releaseMin() << endl;
    cout << h.returnMin() << endl;

    h.printHeap();

    h.deleteKey(3);

    h.printHeap();

    return 0;
}