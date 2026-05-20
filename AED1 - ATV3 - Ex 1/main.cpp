/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 3
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 1: O Desafio da Compra Inteligente 
 *  Um comprador está em um supermercado com um orçamento limitado e duas 
 *  prateleiras de produtos (Prateleira A e Prateleira B). Cada prateleira 
 *  contém itens organizados em uma estrutura de pilha, onde apenas o item 
 *  no topo pode ser acessado.
 *
 *  O objetivo é maximizar o número de itens comprados sem ultrapassar o 
 *  orçamento disponível. A cada passo, o comprador deve escolher sempre o 
 *  item de menor preço disponível entre os topos das duas pilhas.
 *
 *  Caso o custo acumulado ultrapasse o orçamento, a compra é interrompida 
 *  imediatamente. A pontuação final corresponde ao número de itens comprados.
 *
 * Entradas do Problema:
 *  Prateleira A = [5, 2, 9, 4, 6, 3, 1, 2, 4] (topo)
 *  Prateleira B = [2, 6, 9, 7, 2, 5, 1, 4, 2, 5, 3] (topo)
 *  ORÇAMENTO = 20
 *
 * Saída Esperada:
 *  Listagem dos itens comprados, custo acumulado e 
 *  pontuação final (quantidade máxima de itens).
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
        int keys[MAX_TAM];  // Vetor keys     
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

//Implementação dos métodos

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

int maximo_itens(Stack& A, Stack& B, int orcamento){
    int custo = 0;
    int itens = 0;

    //Percorre as duas pratileiras
    while (!A.is_empty() || !B.is_empty()){
        //Salva o primeiro item de cada pratileira
        int topoA = A.peek();
        int topoB = B.peek();

        //Compara o topo de cada pratileira
        if (topoA <= topoB){
            //Caso passar o orcamento
            if ( (custo + topoA) > orcamento){
                cout << "Passou do orcamento\n";
                break;
            }

            //Ainda dentro do orcamento
            custo += topoA;
            itens++;
            A.pop();
            cout << "Pegou " << topoA << " da prateleira A. Custo total: " << custo << "\n";
        } else {
            //Caso passar o orcamento
            if ( (custo + topoB) > orcamento){
                cout << "Passou do orcamento\n";
                break;
            }

            //Ainda dentro do orcamento
            custo += topoB;
            itens++;
            B.pop();
            cout << "Pegou " << topoB << " da prateleira B. Custo total: " << custo << "\n";
        }
    }

    cout << "Custo final: " << custo << "\n";
    return itens; 
}

int main(void) {
    // Problema do enunciado:
    int prateleira_A[] = {5, 2, 9, 4, 6, 3, 1, 2, 4};
    int prateleira_B[] = {2, 6, 9, 7, 2, 5, 1, 4, 2, 5, 3};

    int tamA = sizeof(prateleira_A) / sizeof(prateleira_A[0]);
    int tamB = sizeof(prateleira_B) / sizeof(prateleira_B[0]);
    int orcamento = 20;

    // Criação das pilhas
    Stack A(tamA);
    Stack B(tamB);

    // Inserção das pratileiras na pilha de forma que o último elemento seja o topo
    for (int i = 0; i <= tamA - 1; i++)
        A.push(prateleira_A[i]);
    for (int i = 0; i <= tamB - 1; i++)
        B.push(prateleira_B[i]);

    
    int pontos = maximo_itens(A, B, orcamento);
    cout<< "Pontuação final (quantidade de itens comprados): " << pontos << "\n";
    
    return 0;
}
