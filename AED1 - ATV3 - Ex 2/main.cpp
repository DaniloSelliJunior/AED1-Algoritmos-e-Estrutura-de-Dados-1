/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 3
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 2: O Desafio da Distribuição de Ferramentas
 *  O mestre de um canteiro de obras precisa distribuir ferramentas para seus trabalhadores.
 *  Há uma pilha de ferramentas disponíveis e uma fila de trabalhadores,
 *  cada um com uma preferência específica por um tipo de ferramenta
 *  
 *  As ferramentas são de dois tipos: chave de fenda (representada por 0) e martelo
 *  (representada por 1). Cada trabalhador na fila tem uma preferência por apenas um desses
 *  tipos de ferramenta.
 *
 *  Se o trabalhador que está na frente da fila preferir a ferramenta que está no topo da pilha,
 *  ele a pegará e sairá da fila.
 *  Caso contrário (se ele não preferir a ferramenta do topo), ele sairá sem pegar a ferramenta
 *  e irá para o final da fila, dando a chance para o próximo trabalhador.
 * 
 *  Esse processo continua até que a pilha de ferramentas esteja vazia e todos os trabalhadores
 *  tenham pegado suas ferramentas, ou até que nenhum dos trabalhadores na fila queira
 *  pegar a ferramenta do topo, impedindo que a distribuição continue.
 * 
 * Entradas do Problema:
 *  ferramentas = [1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1] (topo)
 *  trabalhadores = (início) [1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1] (fim)
 *
 * Saída Esperada:
 *  Retornar o número de trabalhadores que não conseguem pegar uma ferramenta
 *  
 ******************************************************/
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define MAX_TAM 30

class Stack{
    private:
        //Atributos:
        int n;              // Tamanho da pilha
        int keys[MAX_TAM];  // Vetor keys de tamanho MAX_TAM     
        int top;                    
        
    public:
        Stack(int tam = 20);    // Inicializa a pilha de tamanho padrão 20

        //Métodos de manipulação da pilha
        bool is_empty() const;  // Confere se a pilha está vazia
        int peek() const;       // Retorna o elemento no topo da pilha (sem remover)
        void push(int key);     // Insere um elemento no topo da pilha
        int pop();              // Retira o elemento do topo da pilha
        int qtd_item();         // Retorna a quantidade de itens na pilha
};

class Queue{
    private:
        int m;              // Tamanho da fila
        int keys[MAX_TAM];  // Vetor keys de tamanho MAX_TAM  
        int head;           // (para remoção)
        int tail;           // (para inserção)
        int size;           // (número de elementos presentes na fila)

    public:
        Queue(int tam = 20);    // Inicializa fila vazia
        bool is_empty() const;  // Verifica se fila está vazia
        void enqueue(int key);  // Insere elemento no final da fila (equivalente ao push)
        int dequeue();          // Remove elemento do início da fila (equivalente ao pop)
        int get_size();         // Retorna o size


};

// ---- Implementação dos métodos do Stack -----

//Construtor
Stack::Stack(int tam){
    if (tam > MAX_TAM)
        cerr << "Erro: tamanho maior que o permitido (" << MAX_TAM << ")\n";
        
    n = tam;
    top = 0;
}    


//Retorno booleano, confere se a pilha está vazia
bool Stack::is_empty() const{
    return top == 0;
}  

//Retorna o elemento no topo da pilha (sem remover)
int Stack::peek() const{
    if (is_empty()){
        cerr << "Erro: pilha vazia (underflow)";
        return 0;
    }else    
        return keys[top - 1];
}       

//Insere um elemento no topo da pilha
void Stack::push(int key){
    if (top == n){  // pilha está cheia
        cerr << "Erro: pilha cheia (overflow)";
        return;
    }else {
        keys[top] = key;
        top++;
    }
}   

//Retira o elemento do topo da pilha
int Stack::pop(){
    if (is_empty()){
        cerr << "Erro: pilha vazia (underflow)";
        return 0;
    }else {
        top--;
        int key = keys[top];
        keys[top] = 0; 
        return key;
    } 
}

int Stack::qtd_item(){
    return top;
}


// ---- Implementação dos métodos do Queue -----

//  Construtor inicializa fila vazia
Queue::Queue(int tam){
    if (tam > MAX_TAM)
        cerr << "Erro: tamanho maior que o permitido (" << MAX_TAM << ")\n";

    m = tam;
    head = 0;
    tail = 0;
    size = 0;
}

// Verifica se fila está vazia
bool Queue::is_empty() const{
    return size == 0;
}

// Insere elemento no final da fila (equivalente ao push)
void Queue::enqueue(int key){
    if (size == m)
        cerr << "Erro: fila cheia (overflow)";
    else {
        if (tail == m)
            tail = 0;
        else
            tail++;
    }
    keys[tail] = key;
    size++;
}

// Remove elemento do início da fila (equivalente ao pop)
int Queue::dequeue(){
    if (is_empty())
        cerr << "Erro: fila vazia (underflow)";
    else {
        if (head == m)  // para tornar a fila circular
            head = 0;
        else
            head++;
    }
    size--;
    return keys[head];
}

int Queue::get_size(){
    return size;
}

// ---- Funções para distribuir ferramentas ----

int distribuir (Stack pilha, Queue fila){
    // Variáveis iniciais
    int tentativas_falhas = 0; // Contador de quantas vezes falhou

    while (!pilha.is_empty() && !fila.is_empty() && tentativas_falhas < fila.get_size()){
        // "Trabalhador da frente saí da fila e olha a ferramenta do top da pilha"
        int primeiro_trabalhador = fila.dequeue();
        int ferramenta_topo = pilha.peek();

        // "Trabalhador verificará se é a ferramenta de sua preferencia"
        if (primeiro_trabalhador == ferramenta_topo){
            pilha.pop();
            tentativas_falhas = 0;
            cout << "Trabalhador pegou a ferramenta, restam: "<< fila.get_size() << " trabalhadores\n";
        } else {
            fila.enqueue(primeiro_trabalhador);
            tentativas_falhas++;
            cout << "Trabalhador recusou a ferramenta, restam: "<< fila.get_size() << " trabalhadores\n";;
        }
    }

    return pilha.qtd_item();
}



int main(void) {
    // Problema do enunciado:
    int ferramentas[] = {1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1};  // (topo)
    int trabalhadores[] = {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1}; // (início) --> (fim)

    int tam_fer = sizeof(ferramentas) / sizeof(ferramentas[0]);
    int tam_trab = sizeof(trabalhadores) / sizeof(trabalhadores[0]);

    // Criação das pilhas e da fila
    Stack fer(tam_fer);
    Queue trab(tam_trab);

    // Inserção das ferramenta na pilha de forma que o último elemento seja o topo
    for (int i = 0; i < tam_fer; i++)
        fer.push(ferramentas[i]);
    // Inserção dos trabalhadores na fila 
    for (int i = 0; i < tam_trab; i++)
        trab.enqueue(trabalhadores[i]);

    int resultado = distribuir(fer, trab);
    cout << "Sobrou " << resultado << " trabalhadores que não conseguiram pegar uma ferramenta\n";
    
    return 0;
}
