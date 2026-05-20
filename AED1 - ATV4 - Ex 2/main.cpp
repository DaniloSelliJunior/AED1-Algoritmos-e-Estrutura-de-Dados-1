/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 4
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 2 – Os Arquivistas de Chronos
 *
 * Dois Arquivistas mantêm registros em listas encadeadas
 * ordenadas cronologicamente. A missão é intercalar as 
 * listas sem perder a ordenação e sem duplicar registros.
 *
 * Função principal: intercalarListas(L1, L2)
 ******************************************************/

#include <iostream>
using namespace std;

// Estrutura básica do nó
struct node{
    int key;
    node* prox;
};

// Classe lista encadeada
class lista_encadeada {
private:
    node* head;
    int tamanho_lista;

public:
    lista_encadeada();             // Construtor
    ~lista_encadeada();            // Destrutor
    bool is_empty();                // Retorna true se vazia
    int length();                   // Retorna tamanho
    void add_head(int key);         // Insere no início
    void add_tail(int key);         // Insere no final
    bool search(int key);           // Busca elemento
    bool remove_no(int key);        // Remove elemento
    node* get_head();               // Retorna cabeça
    void set_head(node* novo_head); // Define cabeça
    void imprimir();                   // Imprime lista

    friend node* intercalarListas(lista_encadeada& L1, lista_encadeada& L2); // Função do exercício
};

// Construtor
lista_encadeada::lista_encadeada() {
    head = nullptr;
    tamanho_lista = 0;
}

// Destrutor
lista_encadeada::~lista_encadeada() {
    node* atual = head;
    while(atual != nullptr) {
        node* tmp = atual->prox;
        delete atual;
        atual = tmp;
    }
}

// Retorna true se vazia
bool lista_encadeada::is_empty() {
    return head == nullptr;
}

// Retorna tamanho
int lista_encadeada::length() {
    return tamanho_lista;
}

// Insere no início
void lista_encadeada::add_head(int key) {
    node* novo = new node;
    novo->key = key;
    novo->prox = head;
    head = novo;
    tamanho_lista++;
}

// Insere no final
void lista_encadeada::add_tail(int key) {
    node* novo = new node;
    novo->key = key;
    novo->prox = nullptr;

    if(head == nullptr) {
        head = novo;
        tamanho_lista++;
        return;
    }

    node* atual = head;
    while(atual->prox != nullptr) {
        atual = atual->prox;
    }
    atual->prox = novo;
    tamanho_lista++;
}

// Busca elemento
bool lista_encadeada::search(int key) {
    node* atual = head;
    while(atual != nullptr) {
        if(atual->key == key) return true;
        atual = atual->prox;
    }
    return false;
}

// Remove nó
bool lista_encadeada::remove_no(int key) {
    node* atual = head;
    node* anterior = nullptr;

    while(atual != nullptr) {
        if(atual->key == key) break;
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == nullptr) return false;

    if(anterior == nullptr) head = atual->prox;
    else anterior->prox = atual->prox;

    delete atual;
    tamanho_lista--;
    return true;
}

// Retorna head
node* lista_encadeada::get_head() {
    return head;
}

// Define head
void lista_encadeada::set_head(node* novo_head) {
    head = novo_head;
}

// Imprime lista
void lista_encadeada::imprimir() {
    node* atual = head;
    while(atual != nullptr) {
        cout << atual->key;
        if(atual->prox != nullptr) cout << " -> ";
        atual = atual->prox;
    }
    cout << " -> nil" << endl;
}

// Intercalação de duas listas ordenadas sem duplicar nós
node* intercalarListas(lista_encadeada& L1, lista_encadeada& L2) {
    node* p1 = L1.get_head();
    node* p2 = L2.get_head();
    node* new_ini = nullptr;
    node* fim = nullptr;

    while(p1 != nullptr && p2 != nullptr) {
        node* escolhido;

        if(p1->key < p2->key) {
            escolhido = p1;
            p1 = p1->prox;
        } else if(p2->key < p1->key) {
            escolhido = p2;
            p2 = p2->prox;
        } else {
            // Chaves iguais: escolhe p1 e descarta p2
            escolhido = p1;
            p1 = p1->prox;
            node* dup = p2;
            p2 = p2->prox;
            dup->prox = nullptr;
        }

        escolhido->prox = nullptr;

        if(new_ini == nullptr) {
            new_ini = fim = escolhido;
        } else {
            fim->prox = escolhido;
            fim = escolhido;
        }
    }

    // Restante de p1
    while(p1 != nullptr) {
        node* tmp = p1;
        p1 = p1->prox;
        tmp->prox = nullptr;

        if(new_ini == nullptr) new_ini = fim = tmp;
        else { fim->prox = tmp; fim = tmp; }
    }

    // Restante de p2
    while(p2 != nullptr) {
        node* tmp = p2;
        p2 = p2->prox;
        tmp->prox = nullptr;

        if(new_ini == nullptr) new_ini = fim = tmp;
        else { fim->prox = tmp; fim = tmp; }
    }

    // Limpa listas originais
    L1.set_head(nullptr);
    L2.set_head(nullptr);
    L1.tamanho_lista = 0;
    L2.tamanho_lista = 0;

    return new_ini;
}

// Função principal
int main() {
    lista_encadeada L1, L2;

    // Preenche L1
    L1.add_tail(1);
    L1.add_tail(3);
    L1.add_tail(5);
    L1.add_tail(7);
    L1.add_tail(9);
    L1.add_tail(10);
    L1.add_tail(11);

    // Preenche L2
    L2.add_tail(2);
    L2.add_tail(3);
    L2.add_tail(4);
    L2.add_tail(6);
    L2.add_tail(8);
    L2.add_tail(10);
    L2.add_tail(12);

    // Exibe listas originais
    cout << "L1: "; L1.imprimir();
    cout << "L2: "; L2.imprimir();

    // Intercala as listas
    node* resultado = intercalarListas(L1, L2);

    // Exibe lista intercalada
    cout << "\nLista intercalada:" << endl;
    node* atual = resultado;
    while(atual != nullptr) {
        cout << atual->key;
        if(atual->prox != nullptr) cout << " -> ";
        atual = atual->prox;
    }
    cout << " -> nil" << endl;

    return 0;
}