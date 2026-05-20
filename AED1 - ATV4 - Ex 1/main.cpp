/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 4
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 1 – A Missão do Guardião das Memórias
 *
 * No reino digital de Memória Eterna, as lembranças dos
 * habitantes são armazenadas em listas encadeadas. 
 * Cada Node guarda uma memória e aponta para a próxima.
 * 
 * Um vírus chamado “Rewind” inverte a ordem das memórias,
 * fazendo com que as pessoas se lembrem dos fatos na 
 * direção contrária. Sua missão é implementar três formas
 * diferentes de inverter a ordem dessas memórias:
 *
 *   (a) inverterLista(L): inversão in-place (O(n))
 *   (b) inverterLista_S(L): inversão usando pilha (O(n))
 *   (c) inverterLista_R(L): inversão recursiva (O(n))
 *
 ******************************************************/

#include <iostream>
#include <string>

using namespace std;

// Nó da lista
struct Node {
    int id;
    string memoria;
    Node* prox;
};

// Classe da lista encadeada
class ListaEncad {
private:
    Node* head;  // cabeça da lista
    int size;    // tamanho da lista

public:
    ListaEncad();             // construtor
    ~ListaEncad();            // destrutor
    bool vazia();             // retorna true se lista vazia
    int length();             // retorna tamanho da lista
    void add_head(int id, const string& mem);   // insere no início
    void add_tail(int id, const string& mem);   // insere no final
    bool search(int id);      // busca elemento
    bool remove_node(int id); // remove elemento
    Node* get_head();         // retorna cabeça
    void set_head(Node* novo); // define cabeça
    void mostrar();           // exibe lista

    friend Node* inverterLista(ListaEncad &L);      // inversão in-place
    friend Node* inverterLista_S(ListaEncad &L);    // inversão com pilha
    friend Node* inverterLista_R(ListaEncad &L);    // inversão recursiva
};

// Construtor
ListaEncad::ListaEncad() {
    head = nullptr;
    size = 0;
}

// Destrutor
ListaEncad::~ListaEncad() {
    Node* atual = head;
    while (atual != nullptr) {
        Node* tmp = atual->prox;
        delete atual;
        atual = tmp;
    }
}

// Retorna true se lista vazia
bool ListaEncad::vazia() {
    return head == nullptr;
}

// Retorna tamanho
int ListaEncad::length() {
    return size;
}

// Insere no início
void ListaEncad::add_head(int id, const string& mem) {
    Node* novo = new Node;
    novo->id = id;
    novo->memoria = mem;
    novo->prox = head;
    head = novo;
    size++;
}

// Insere no final
void ListaEncad::add_tail(int id, const string& mem) {
    Node* novo = new Node;
    novo->id = id;
    novo->memoria = mem;
    novo->prox = nullptr;

    if (head == nullptr) {
        head = novo;
    } else {
        Node* aux = head;
        while (aux->prox != nullptr) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    size++;
}

// Busca elemento
bool ListaEncad::search(int id) {
    Node* aux = head;
    while (aux != nullptr) {
        if (aux->id == id) return true;
        aux = aux->prox;
    }
    return false;
}

// Remove nó
bool ListaEncad::remove_node(int id) {
    Node* atual = head;
    Node* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->id == id) break;
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == nullptr) return false;

    if (anterior == nullptr) head = atual->prox;
    else anterior->prox = atual->prox;

    delete atual;
    size--;
    return true;
}

// Retorna cabeça
Node* ListaEncad::get_head() { return head; }

// Define cabeça
void ListaEncad::set_head(Node* novo) { head = novo; }

// Mostra lista
void ListaEncad::mostrar() {
    Node* aux = head;
    while (aux != nullptr) {
        cout << "(" << aux->id << ", " << aux->memoria << ")";
        if (aux->prox != nullptr) cout << " -> ";
        aux = aux->prox;
    }
    cout << "\n";
}

// Classe da pilha estática
class PilhaEstatica {
private:
    Node** dados;
    int topo;
    int capacidade;

public:
    PilhaEstatica(int cap);
    ~PilhaEstatica();
    bool vazia();
    void push(Node* ptr);
    Node* pop();
};

// Construtor da pilha
PilhaEstatica::PilhaEstatica(int cap) {
    capacidade = cap;
    dados = new Node*[cap];
    topo = -1;
}

// Destrutor da pilha
PilhaEstatica::~PilhaEstatica() {
    delete[] dados;
}

// Verifica se vazia
bool PilhaEstatica::vazia() {
    return topo == -1;
}

// Empilha
void PilhaEstatica::push(Node* ptr) {
    if (topo + 1 >= capacidade) return;
    dados[++topo] = ptr;
}

// Desempilha
Node* PilhaEstatica::pop() {
    if (topo == -1) return nullptr;
    return dados[topo--];
}

// Inversão in-place
Node* inverterLista(ListaEncad &L) {
    Node* anterior = nullptr;
    Node* atual = L.get_head();
    Node* seguinte = nullptr;

    while (atual != nullptr) {
        seguinte = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = seguinte;
    }

    L.set_head(anterior);
    return anterior;
}

// Inversão com pilha
Node* inverterLista_S(ListaEncad &L) {
    Node* h = L.get_head();
    if (h == nullptr) return nullptr;

    PilhaEstatica P(L.length());
    Node* aux = h;

    while (aux != nullptr) {
        Node* prox = aux->prox;
        aux->prox = nullptr;
        P.push(aux);
        aux = prox;
    }

    Node* novo_head = P.pop();
    Node* cur = novo_head;

    while (!P.vazia()) {
        cur->prox = P.pop();
        cur = cur->prox;
    }

    L.set_head(novo_head);
    return novo_head;
}

// Função auxiliar recursiva
Node* inverter_rec_aux(Node* no) {
    if (no == nullptr || no->prox == nullptr) return no;
    Node* novo_head = inverter_rec_aux(no->prox);
    no->prox->prox = no;
    no->prox = nullptr;
    return novo_head;
}

// Inversão recursiva
Node* inverterLista_R(ListaEncad &L) {
    L.set_head(inverter_rec_aux(L.get_head()));
    return L.get_head();
}

// Função principal
int main() {
    ListaEncad L;

    L.add_tail(12,"vida adulta");
    L.add_tail(11,"trabalho");
    L.add_tail(10,"faculdade");
    L.add_tail(9,"ensino médio");
    L.add_tail(8,"amizade");
    L.add_tail(7,"adolescência");
    L.add_tail(6,"ensino fundamental");
    L.add_tail(5,"natal");
    L.add_tail(4,"praia");
    L.add_tail(3,"infância");
    L.add_tail(2,"pai");
    L.add_tail(1,"mãe");

    cout << "\nLista original:\n";
    L.mostrar();

    cout << "\nInversão in-place:\n";
    inverterLista(L);
    L.mostrar();

    cout << "\nInversão com pilha:\n";
    inverterLista_S(L);
    L.mostrar();

    cout << "\nInversão recursiva:\n";
    inverterLista_R(L);
    L.mostrar();

    return 0;
}