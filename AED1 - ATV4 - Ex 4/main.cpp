/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 4
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 4 – A Lista Circular do Castelo
 *
 * No castelo de Algorithmland, a fila de cavaleiros é
 * uma lista circular. Periodicamente, ocorre uma reordenação
 * onde cavaleiros com IDs ímpares vão para a frente, mantendo
 * a ordem relativa, seguidos pelos pares.
 *
 * Operação principal:
 * reorganizarLista(L) - separa nós ímpares e pares e
 * reconecta a lista mantendo a propriedade circular.
 *
 ******************************************************/

#include <iostream>

using namespace std;

// estrutura do nó
struct Node {
    int id;
    Node* prev;
    Node* prox;
};

// classe lista circular
class ListaCircular {
private:
    Node* head;

public:
    // construtor
    ListaCircular() {
        head = nullptr;
    }

    // destrutor
    ~ListaCircular() {
        if (head == nullptr) return;

        // quebra o ciclo para deletar linearmente
        Node* tail = head->prev;
        tail->prox = nullptr; // quebra a circularidade

        Node* atual = head;
        while (atual != nullptr) {
            Node* temp = atual->prox;
            delete atual;
            atual = temp;
        }
    }

    // insere no final mantendo circularidade
    void inserir(int v) {
        Node* novo = new Node;
        novo->id = v;

        if (head == nullptr) {
            head = novo;
            head->prox = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            
            // ajusta ponteiros do novo no
            novo->prox = head;
            novo->prev = tail;

            // ajusta ponteiros da lista existente
            tail->prox = novo;
            head->prev = novo;
        }
    }

    Node* getHead() const {
        return head;
    }

    // atualiza o head (usado pela funcao de reorganizacao)
    void setHead(Node* novoHead) {
        head = novoHead;
    }

    // imprime a lista circular (uma volta completa)
    void imprime() {
        if (head == nullptr) {
            cout << "Lista Vazia" << endl;
            return;
        }

        Node* atual = head;
        
        // loop do-while para garantir que imprime pelo menos uma vez e para no inicio
        do {
            cout << "[";
            cout << atual->id;
            cout << "]";
            
            if (atual->prox != head) {
                cout << " <-> ";
            }
            
            atual = atual->prox;
        } while (atual != head);
        
        cout << " (volta para [";
        cout << head->id;
        cout << "])";
        cout << endl;
    }
};

// funcao reorganizarLista
void reorganizarLista(ListaCircular& L) {
    Node* headOriginal = L.getHead();
    
    // se lista vazia ou com 1 elemento, nada a fazer
    if (headOriginal == nullptr || headOriginal->prox == headOriginal) {
        return;
    }

    // ponteiros auxiliares para construir as duas listas (impar e par)
    Node* headImpar = nullptr;
    Node* tailImpar = nullptr;
    Node* headPar = nullptr;
    Node* tailPar = nullptr;

    Node* atual = headOriginal;
    
    // percorre a lista original exatamente uma vez
    // usamos do-while para garantir volta completa
    bool primeiraIteracao = true;
    while (primeiraIteracao || atual != headOriginal) {
        primeiraIteracao = false;
        
        Node* proximoNo = atual->prox; // salva referencia do proximo
        
        // isola o nó atual logicamente
        atual->prox = nullptr;
        atual->prev = nullptr;

        // verifica se é impar ou par
        if (atual->id % 2 != 0) {
            // adiciona na lista de impares
            if (headImpar == nullptr) {
                headImpar = atual;
                tailImpar = atual;
            } else {
                tailImpar->prox = atual;
                atual->prev = tailImpar;
                tailImpar = atual;
            }
        } else {
            // adiciona na lista de pares
            if (headPar == nullptr) {
                headPar = atual;
                tailPar = atual;
            } else {
                tailPar->prox = atual;
                atual->prev = tailPar;
                tailPar = atual;
            }
        }

        atual = proximoNo;
    }

    // reconstrução da lista circular
    
    // cenario 1: apenas pares
    if (headImpar == nullptr) {
        // fecha o ciclo nos pares
        tailPar->prox = headPar;
        headPar->prev = tailPar;
        L.setHead(headPar);
        return;
    }

    // cenario 2: apenas impares
    if (headPar == nullptr) {
        // fecha o ciclo nos impares
        tailImpar->prox = headImpar;
        headImpar->prev = tailImpar;
        L.setHead(headImpar);
        return;
    }

    // cenario 3: misto (conecta fim dos impares no inicio dos pares)
    tailImpar->prox = headPar;
    headPar->prev = tailImpar;

    // conecta fim dos pares no inicio dos impares (fechando o circulo)
    tailPar->prox = headImpar;
    headImpar->prev = tailPar;

    // define o novo head como o inicio dos impares
    L.setHead(headImpar);
}

int main() {
    // cria lista circular
    ListaCircular L;
    
    // entrada original do exemplo
    // [4] -> [3] -> [2] -> [7] -> [8] -> [5] -> [6] -> [9]
    int dados[] = {4, 3, 2, 7, 8, 5, 6, 9};
    int n = sizeof(dados) / sizeof(int);

    for (int i = 0; i < n; i++) {
        L.inserir(dados[i]);
    }

    cout << "Lista Original:" << endl;
    L.imprime();

    // executa a reorganizacao
    reorganizarLista(L);

    cout << endl;
    cout << "Lista Reorganizada (Impares na frente):" << endl;
    L.imprime();

    return 0;
}