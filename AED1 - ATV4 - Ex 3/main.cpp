/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 4
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 3 – O Arqueólogo dos Dados
 *
 * No Arquivo Antigo de Computália, as informações históricas
 * estão em listas duplamente encadeadas com números possivelmente
 * repetidos. A tarefa é criar uma lista compactada, mantendo
 * apenas um nó por valor, junto com sua frequência.
 *
 * Operação principal:
 * compactarLista(L) - percorre L e cria C, ordenada por chave
 * com contagem de ocorrências.
 *
 ******************************************************/

#include <iostream>

using namespace std;

// estruturas dos nós
struct NodeL {
    int valor;
    NodeL* prev;
    NodeL* prox;
};

struct NodeC {
    int key;
    int count;
    NodeC* prev;
    NodeC* prox;
};

// classe lista original L
class ListaOriginal {
private:
    NodeL* head;

public:
    // construtor
    ListaOriginal() {
        head = nullptr;
    }

    // destrutor
    ~ListaOriginal() {
        NodeL* atual = head;
        while (atual != nullptr) {
            NodeL* temp = atual->prox;
            delete atual;
            atual = temp;
        }
    }

    // insere no fim
    void inserirFinal(int v) {
        NodeL* novo = new NodeL;
        novo->valor = v;
        novo->prox = nullptr;
        novo->prev = nullptr;

        if (head == nullptr) {
            head = novo;
        } else {
            NodeL* temp = head;
            while (temp->prox != nullptr) {
                temp = temp->prox;
            }
            temp->prox = novo;
            novo->prev = temp;
        }
    }

    NodeL* getHead() const {
        return head;
    }

    // imprime a lista sem acumulação de operadores
    void imprime() {
        NodeL* atual = head;
        while (atual != nullptr) {
            cout << atual->valor;
            if (atual->prox != nullptr) {
                cout << " <-> ";
            }
            atual = atual->prox;
        }
        cout << " <-> NIL";
        cout << endl;
    }
};

// classe lista compactada C
class ListaCompactada {
private:
    NodeC* head;

public:
    // construtor
    ListaCompactada() {
        head = nullptr;
    }

    // destrutor
    ~ListaCompactada() {
        NodeC* atual = head;
        while (atual != nullptr) {
            NodeC* temp = atual->prox;
            delete atual;
            atual = temp;
        }
    }

    // insere ordenado ou incrementa contador
    void processarEvento(int chave) {
        // se vazia, insere o primeiro
        if (head == nullptr) {
            NodeC* novo = new NodeC;
            novo->key = chave;
            novo->count = 1;
            novo->prev = nullptr;
            novo->prox = nullptr;
            head = novo;
            return;
        }

        // se menor que o head, insere no inicio
        if (chave < head->key) {
            NodeC* novo = new NodeC;
            novo->key = chave;
            novo->count = 1;
            novo->prox = head;
            novo->prev = nullptr;
            head->prev = novo;
            head = novo;
            return;
        }

        NodeC* atual = head;
        while (atual != nullptr) {
            // se achou a chave, incrementa
            if (atual->key == chave) {
                atual->count++;
                return; 
            }

            // insere se for fim ou o proximo for maior
            if (atual->prox == nullptr || atual->prox->key > chave) {
                NodeC* novo = new NodeC;
                novo->key = chave;
                novo->count = 1;
                novo->prev = atual;
                novo->prox = atual->prox;

                if (atual->prox != nullptr) {
                    atual->prox->prev = novo;
                }
                atual->prox = novo;
                return;
            }

            atual = atual->prox;
        }
    }

    // imprime a lista sem acumulação de operadores
    void imprime() {
        NodeC* atual = head;
        while (atual != nullptr) {
            cout << "(";
            cout << atual->key;
            cout << ", ";
            cout << atual->count;
            cout << ")";

            if (atual->prox != nullptr) {
                cout << " <-> ";
            }
            atual = atual->prox;
        }
        cout << " <-> NIL";
        cout << endl;
    }
};

// funcao compactarLista
ListaCompactada compactarLista(ListaOriginal& L) {
    ListaCompactada C;
    NodeL* atualL = L.getHead();

    // percorre L e popula C
    while (atualL != nullptr) {
        C.processarEvento(atualL->valor);
        atualL = atualL->prox;
    }

    return C;
}

int main() {
    // cria lista L
    ListaOriginal L;
    int dados[] = {4, 2, 1, 4, 2, 3, 1, 3, 5, 5, 2, 2, 3, 2, 4, 1, 3, 5};
    int n = sizeof(dados) / sizeof(int);

    for (int i = 0; i < n; i++) {
        L.inserirFinal(dados[i]);
    }

    cout << "Lista Original L:" << endl;
    L.imprime();

    // cria lista C
    ListaCompactada C = compactarLista(L);

    cout << endl;
    cout << "Lista Compactada C:" << endl;
    C.imprime();

    return 0;
}