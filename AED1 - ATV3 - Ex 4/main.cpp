/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 3
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 4: O Problema da Conexão das Cordas
 * 
 * Entradas do Problema:
 * 
 * O problema do Custo Mínimo para Conectar Cordas é um problema clássico de
 * otimização. O objetivo é conectar n cordas de comprimentos variados em uma única corda
 * com o custo total mínimo. O custo de conectar duas cordas é igual à soma de seus
 * comprimentos. Em cada etapa, combinamos duas cordas, e a corda combinada pode então
 * ser usada em combinações subsequentes
 * 
 * Definição do problema:
 * Dada uma matriz de comprimentos inteiros [1…n], onde cada inteiro representa o
 * comprimento de uma corda, encontre o custo mínimo para conectar todas as cordas em
 * uma única corda.
 * Ideia-chave:
 * Combinar duas cordas incorre em um custo igual à soma de seus comprimentos. Para 
 * minimizar o custo total, sempre combine as duas menores cordas em cada etapa.
 * 
 * Exemplo ilustrativo
 * Entrada: n = 4 (4 cordas de comprimentos 4, 3, 2 e 6)
 * lengths = [4, 3, 2, 6]
 * 
 * a) Combine as duas cordas menores (2 e 3):
 * Custo = 2 + 3 = 5
 * Cordas restantes = [4, 5, 6]
 * 
 * b) Combine as duas cordas menores (4 e 5):
 * Custo = 4 + 5 = 9
 * Cordas restantes = [6, 9]
 * 
 * c) Combine as duas Cordas restantes (6 e 9):
 * Custo = 6 + 9 = 15
 * Cordas restantes = [15]
 * Custo total: 5 + 9 + 15 = 29
 *
 *  
 ******************************************************/
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define MAX_TAM 4

struct Node{
    int key;
    int priority;
};

class PriorityQueue{
    private:
        Node data[MAX_TAM];
        int tail;
        int size;

    public:
        PriorityQueue();                            //Construtor
        void enqueue(int key, int p);               // Adiciona chave com prioridade p no final da fila
        int findMin();                              // Encontra elemento de menor prioridade
        int dequeue();                              // Remove o elemento de menor prioridade
        bool is_empty();                            // Verifica se a fila de prioridade está vazia
        int get_size();                             //Retorna o size    
};

//Construtor
PriorityQueue::PriorityQueue(){
    tail = size = 0;
}

// Adiciona chave com prioridade p no final da fila
void PriorityQueue::enqueue(int key, int p){
    if (size == MAX_TAM)
        cerr<< "overflow\n";
    else {
        tail ++;
        data[tail - 1].key = key;
        data[tail - 1].priority = p;
        size++;
    }
}

// Encontra elemento de menor prioridade
int PriorityQueue::findMin(){
    if (size == 0){
        cerr << "Underflow\n";
        return -1;
    }

    int index = 0;
    int min = data[0].key;
    
    for(int i = 1; i < size; i++){
        if(data[i].key < min){
            min = data[i].key;
            index = i;
        }
    }
    return index;
}

// Remove o elemento de menor prioridade
int PriorityQueue::dequeue(){
      if (size == 0){
        cerr << "Underflow\n";
        return -1;
    }

    // encontra a posição do elemento de menor prioridade
    int pos = findMin();
    int key = data[pos].key;

    // precisa realocar todos elementos de pos até tail
    for (int i = pos; i < size - 1; i++) {
        data[i].key = data[i+1].key;
        data[i].priority = data[i+1].priority;
    }

    tail--;
    size--;
    return key;
}

// Verifica se a fila de prioridade está vazia
bool PriorityQueue::is_empty(){
    return size == 0;
}

//Retorna o size 
int PriorityQueue::get_size(){
    return size;
}  

int custo_min_tot (int v[]){
    // Cria uma PriorityQueue e a preenche com a entrada
    PriorityQueue pq;
    for(int i = 0; i < MAX_TAM; i++)
        pq.enqueue(v[i], v[i]); // O comprimento também representa a prioridade

    int custo_total = 0;
    // Percorre a PriorityQueue enquanto ainda há cordas
    while (pq.get_size() > 1){
        // Retira as duas menores
        int corda_menor1 = pq.dequeue();
        int corda_menor2 = pq.dequeue();

        // Soma as menores cordas e volta o resultado para a PriorityQueue
        custo_total += corda_menor1 + corda_menor2;
        pq.enqueue(corda_menor1 + corda_menor2, corda_menor1 + corda_menor2);

        cout << "Cordas menores: " << corda_menor1 << " e " << corda_menor2 << " | Custo: " << corda_menor1 + corda_menor2 << "\n";
    }
    return custo_total;
}

int main(void) {
    // Problema do enunciado:
    int comprimentos[MAX_TAM] = {4, 3, 2, 6};

    int custo = custo_min_tot(comprimentos);
    cout << "------------\nCusto mínimo total da corda: " << custo << "\n";

    return 0;
}