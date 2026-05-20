/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 2
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 3 – O Bibliotecário Organizado
 *
 * O algoritmo utilizado é o InsertionSort.
 * Ele retorna:
 * - a lista ordenada;
 * - o número total de comparações realizadas;
 * - o número total de movimentações (deslocamentos) realizadas.
 ******************************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 20000


//Primitiva Swap (inverte 2 valores reais)
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int lista[], int n) {
    // contadores
    int comparações = 0;
    int movimentações = 0;
    
    // Percorre cada elemento da lista
    for (int i = 1; i < n; i++) {
        int k = i;
        // Insere o pivô na posição correta
        while (k > 0 && lista[k] < lista[k-1]) {
            swap(&lista[k], &lista[k-1]);
            k--;
            comparações++;
            movimentações++;
        }
    }

    printf("Comparações = %d, Movimentações = %d\n", comparações, movimentações);
}


//cria uma lista dos 20 mil ID diferentes dos livros
void lista_20k_elementos(int lista[]) {
    // Inicializa a lista dos livros com valores de 0 a 20 mil em ordem.
    for (int i = 0; i < N; i++) 
        lista[i] = i;

    // Embaralha a lista para obter uma ordem aleatória.
    srand(time(NULL));
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1); // j escolhe um livro aleatório até i
        
        // Troca lista[i] com lista[j]
        int temp = lista[i];
        lista[i] = lista[j];
        lista[j] = temp;
    }
}

// função auxiliar para imprimir lista
void print_lista (int lista[], int n){
    printf("[");
    for (int i = 0; i < n; i++)
        printf(" %d ", lista[i]);
    printf("]\n");
}


int main() {
    // Exemplo enunciado
    int id_enum[4] = {7, 4, 5, 2};
    int n_enum = 4;

    
    printf("> Exemplo do enunciado:\nEntrada: ");
    print_lista(id_enum, n_enum);

    printf("\nUtilizando o método  InsertionSort temos:\n");
    insertionSort(id_enum, n_enum);
    
    printf("Saída: ");
    print_lista(id_enum, n_enum);
    
    // Exemplo lista de 20k livros
    int id_20k[N];
    // Variáveis temporais:
    clock_t ini_crono;
    clock_t fim_crono;
    
    printf("\n> Para uma lista de 20 mil livros, com InsertionSort temos:\n");
    lista_20k_elementos(id_20k);
    
    ini_crono = clock(); // inicia o cronometro
    insertionSort(id_20k, N);
    fim_crono = clock(); // encerra o cronometro
    double cronometro = (double)(fim_crono - ini_crono) / CLOCKS_PER_SEC; //calcula o tempo gasto
    
    printf("Tempo gasto para a resolução do problema: %.5fs\n", cronometro);
    
    return 0;
}
