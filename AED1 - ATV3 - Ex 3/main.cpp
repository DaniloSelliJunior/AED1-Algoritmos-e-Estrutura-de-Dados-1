/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 3
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 3: O Problema do Intervalo de Ações
 *
 * O Problema do Intervalo de Ações (Stock Span Problem) envolve determinar, para cada
 * dia em uma série de preços de ações, o número de dias anteriores consecutivos (incluindo o
 * dia atual) em que o preço das ações foi menor ou igual ao preço das ações daquele dia
 * 
 * Entradas do Problema:
 * Considere n = 20 e P dado por:
 * P = [120, 100, 80, 90, 80, 95, 105, 100, 90, 80, 70, 90, 100, 115, 125, 110, 95, 90, 80, 100]
 *
 * Saída Esperada:
 *  
 ******************************************************/
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define MAX_TAM 20


class Deque{
    private:
        int keys[MAX_TAM + 1];  // Vetor keys de tamanho MAX_TAM  
        int start;          // (extremidade da esquerda)
        int end;            // (extremidade da direita)
        int size;           // Quantidade de elementos do deque

    public:
        Deque();                    // Construtor
        bool is_empty() const;      // Verifica se o deque está vazio
        bool is_full() const;       // Verifica se o deque está cheio
        void add_start(int key);    // Insere elemento no início
        void add_end(int key);      // Insere elemento no final
        int remove_start();         // remove elemento no início
        int remove_end();           // remove elemento no início
        int get_end();              //Retorna o elemento do fim do Deque
        int get_size();             // Retorna o size
};


// ---- Implementação dos métodos do Deque -----

// Construtor: Inicializa o deque vazio
Deque::Deque(){
    start = 0;
    end = 0;
    size = 0;
}      

// Verifica se o deque está vazio
bool Deque::is_empty() const{
    return size == 0;
}     

// Verifica se o deque está cheio
bool Deque::is_full() const{
    return size == MAX_TAM;
}      
    
// Insere elemento no início
void Deque::add_start(int key){
    if (is_full()){
        cerr << "Erro: deque cheio (overflow)";
        return;
    } else {
        if(is_empty()){
        start = 1;
        end = 1;
        }else {
            if(start == 1){
                start = MAX_TAM;
            }else {
                start--;
            }    
        }
    keys[start] = key;
    size++;
    }    
}    

// Insere elemento no final
void Deque::add_end(int key){
    if (is_full()){
        cerr << "Erro: deque cheio (overflow)";
        return;
    } else {
        if(is_empty()){
        start = 1;
        end = 1;
        }else {
            if(end == MAX_TAM){
                end = 1;
            }else {
                end++;
            }    
        }
    keys[end] = key;
    size++;
    } 
}     
       
// remove elemento no início
int Deque::remove_start(){
    if (is_empty()){
        cerr << "Erro: deque vazio (underflow)";
        return -1;
    } else {
        int key = keys[start];
        keys[start] = 0;
        if (start == end){
            start = 0;
            end = 0;
        } else{
            if (start == MAX_TAM)
                start = 1;
            else
                start++;
        }
        size--;
        return key;
    }  
}       
 
// remove elemento no início
int Deque::remove_end(){
    if (is_empty()){
        cerr << "Erro: deque vazio (underflow)";
        return -1;
    } else {
        int key = keys[end];
        keys[end] = 0;
        if (start == end){
            start = 0;
            end = 0;
        } else{
            if (end == 1)
                end = MAX_TAM;
            else
                end--;
        }
        size--;
        return key;
    } 
}          
     
// Retorna o size
int Deque::get_size(){
    return size;
}             

//Retorna o elemento do fim do Deque
int Deque::get_end(){
    if(is_empty()){ 
        return -1;
    }else{
        return keys[end];
    }
};


//Função para calcular o Intervalos das ações
void calcular_Intervalos(int P[], int n, int S[]){
    //Cria Deque D
    Deque D;


    for(int i = 0; i < n; i++){
        //Remove do final todos os índices cujos preços são <= P[i]
        while(!D.is_empty() && P[D.get_end()] <= P[i])
            D.remove_end();

        //Se o deque ficar vazio, significa que P[i] é o maior até agora
        if(D.is_empty())
            S[i] = i + 1;
        else
            S[i] = i - D.get_end();
        
        //Adiciona o elemento i ao final
        D.add_end(i);  
    }
}

int main(void) {
    // Problema do enunciado:
    int P[] = {120, 100, 80, 90, 80, 95, 105, 100, 90, 80, 70, 90, 100, 115, 125, 110, 95, 90, 80, 100};
    int S[MAX_TAM];

    calcular_Intervalos(P, MAX_TAM, S);

    for (int i = 0; i < MAX_TAM; i++){
        cout<< "Preços: " << P[i] << "| Intervalo: " << S[i] <<"\n";
    }

    return 0;
}