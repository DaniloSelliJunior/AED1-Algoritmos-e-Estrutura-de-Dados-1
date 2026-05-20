/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Projeto Prático
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Opção A - Árvores Binárias de Busca
 * 
 * Implementação de um sistema de gerenciamento de registros
 * utilizando uma Árvore Binária de Busca (ABB). Cada nó da
 * árvore armazena os dados de um cidadão, organizados a partir
 * de um identificador único. O sistema permite operações de
 * inserção, busca, remoção, listagem ordenada, geração de
 * relatórios estatísticos e visualização textual da estrutura
 * da árvore.
 *
 ******************************************************/

#include <iostream>
#include <string>

using namespace std;

struct Registro {
    // Estrutura que representa um cidadão armazenado na árvore
    int id;
    string nome;
    int idade;
};

struct No {
    // Nó da árvore binária de busca
    Registro dado;
    No* esq;
    No* dir;

    No(const Registro& r) : dado(r), esq(nullptr), dir(nullptr) {}
};

class ArvoreBST {
// Classe que encapsula as operações da Árvore Binária de Busca
private:
    No* raiz;

    // Insere um novo registro respeitando a propriedade da ABB
    No* inserir(No* atual, const Registro& r) {
        if (atual == nullptr)
            return new No(r);
        if (r.id < atual->dado.id)
            atual->esq = inserir(atual->esq, r);
        else if (r.id > atual->dado.id)
            atual->dir = inserir(atual->dir, r);
        return atual;
    }

    // Busca um registro pelo identificador
    No* buscar(No* atual, int id) const {
        if (atual == nullptr || atual->dado.id == id)
            return atual;
        if (id < atual->dado.id)
            return buscar(atual->esq, id);
        return buscar(atual->dir, id);
    }

    No* minimo(No* atual) {
        while (atual != nullptr && atual->esq != nullptr)
            atual = atual->esq;
        return atual;
    }

    // Remove um nó da árvore tratando os três casos possíveis
    No* remover(No* atual, int id) {
        if (atual == nullptr)
            return atual;

        if (id < atual->dado.id) {
            atual->esq = remover(atual->esq, id);
        } else if (id > atual->dado.id) {
            atual->dir = remover(atual->dir, id);
        } else {
            if (atual->esq == nullptr) {
                No* temp = atual->dir;
                delete atual;
                return temp;
            }
            if (atual->dir == nullptr) {
                No* temp = atual->esq;
                delete atual;
                return temp;
            }

            No* temp = minimo(atual->dir);
            atual->dado = temp->dado;
            atual->dir = remover(atual->dir, temp->dado.id);
        }
        return atual;
    }

    // Percurso em ordem crescente
    void emOrdem(No* atual) const {
        if (atual == nullptr)
            return;
        emOrdem(atual->esq);
        cout << atual->dado.id << " ";
        emOrdem(atual->dir);
    }

    // Percurso em ordem decrescente
    void emOrdemReverso(No* atual) const {
        if (atual == nullptr)
            return;
        emOrdemReverso(atual->dir);
        cout << atual->dado.id << " ";
        emOrdemReverso(atual->esq);
    }

    // Calcula a altura da árvore
    int altura(No* atual) const {
        if (atual == nullptr)
            return -1;

        int hEsq = altura(atual->esq);
        int hDir = altura(atual->dir);

        if (hEsq > hDir)
            return 1 + hEsq;
        else
            return 1 + hDir;
    }

    // Conta o número total de nós
    int contarNos(No* atual) const {
        if (atual == nullptr)
            return 0;
        return 1 + contarNos(atual->esq) + contarNos(atual->dir);
    }

    // Conta o número de folhas da árvore
    int contarFolhas(No* atual) const {
        if (atual == nullptr)
            return 0;
        if (atual->esq == nullptr && atual->dir == nullptr)
            return 1;
        return contarFolhas(atual->esq) + contarFolhas(atual->dir);
    }

    // Verifica se a árvore está balanceada
    bool balanceada(No* atual) const {
        if (atual == nullptr)
            return true;

        int hEsq = altura(atual->esq);
        int hDir = altura(atual->dir);

        if (hEsq - hDir > 1 || hDir - hEsq > 1)
            return false;

        return balanceada(atual->esq) && balanceada(atual->dir);
    }

    // Exibe a árvore de forma indentada
    void visualizar(No* atual, int nivel) const {
        if (atual == nullptr)
            return;

        visualizar(atual->dir, nivel + 1);

        for (int i = 0; i < nivel; i++)
            cout << "    ";

        cout << atual->dado.id << "\n";

        visualizar(atual->esq, nivel + 1);
    }

public:
    ArvoreBST() : raiz(nullptr) {}

    void inserirRegistro(int id, const string& nome, int idade) {
        Registro r;
        r.id = id;
        r.nome = nome;
        r.idade = idade;
        raiz = inserir(raiz, r);
    }

    void removerRegistro(int id) {
        raiz = remover(raiz, id);
    }

    void buscarRegistro(int id) const {
        No* res = buscar(raiz, id);
        if (res != nullptr)
            cout << "Encontrado: " << res->dado.nome << ", idade " << res->dado.idade << "\n";
        else
            cout << "Registro nao encontrado\n";
    }

    void listarEmOrdem() const {
        emOrdem(raiz);
        cout << "\n";
    }

    void listarDecrescente() const {
        emOrdemReverso(raiz);
        cout << "\n";
    }

    void relatorio() const {
        cout << "Altura da arvore: " << altura(raiz) << "\n";
        cout << "Numero de nos: " << contarNos(raiz) << "\n";
        cout << "Numero de folhas: " << contarFolhas(raiz) << "\n";
        cout << "Arvore balanceada: " << (balanceada(raiz) ? "Sim" : "Nao") << "\n";
    }

    void visualizarArvore() const {
        visualizar(raiz, 0);
    }
};

int main() {
    // Testes conforme especificado no enunciado
    ArvoreBST arvore;

    arvore.inserirRegistro(16, "Alex", 18);
    arvore.inserirRegistro(8, "Ana", 15);
    arvore.inserirRegistro(24, "Bruno", 21);
    arvore.inserirRegistro(4, "Maria", 17);
    arvore.inserirRegistro(12, "Lucas", 28);
    arvore.inserirRegistro(20, "Isabela", 18);
    arvore.inserirRegistro(28, "Rafael", 14);
    arvore.inserirRegistro(2, "Laura", 25);
    arvore.inserirRegistro(6, "Pedro", 18);
    arvore.inserirRegistro(10, "Sofia", 17);
    arvore.inserirRegistro(14, "Gabriel", 19);
    arvore.inserirRegistro(18, "Helena", 20);
    arvore.inserirRegistro(22, "Arthur", 18);
    arvore.inserirRegistro(26, "Beatriz", 16);
    arvore.inserirRegistro(30, "Mateus", 19);
    arvore.inserirRegistro(5, "Alice", 17);
    arvore.inserirRegistro(17, "Davi", 18);
    arvore.inserirRegistro(19, "Livia", 21);

    cout << "Em ordem: ";
    arvore.listarEmOrdem();

    cout << "Decrescente: ";
    arvore.listarDecrescente();

    cout << "\nArvore:\n";
    arvore.visualizarArvore();

    cout << "\nRelatorio:\n";
    arvore.relatorio();

    arvore.removerRegistro(8);
    arvore.removerRegistro(24);
    arvore.removerRegistro(4);
    arvore.removerRegistro(30);

    cout << "\nRelatorio apos remocoes:\n";
    arvore.relatorio();

    cout << "\nArvore final:\n";
    arvore.visualizarArvore();

    return 0;
}
