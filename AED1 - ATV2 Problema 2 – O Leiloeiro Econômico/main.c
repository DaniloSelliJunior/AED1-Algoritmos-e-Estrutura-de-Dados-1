/******************************************************
 * Algoritmos e Estrutura de Dados I
 * Atividade Avaliativa 2
 *
 * Aluno: Danilo Djovano Selli Junior
 * RA: 842868 – UFSCar
 *
 * Problema 2 – O Leiloeiro Econômico
 *
 * Um leiloeiro precisa organizar lances de um leilão em ordem crescente.
 * Para economizar energia, ele percorre a lista da esquerda para a direita,
 * sempre selecionando o menor valor do restante da lista e trocando-o com
 * o valor da posição atual.
 *
 * O algoritmo utilizado é o SelectionSort.
 * Ele retorna:
 *   - a lista ordenada;
 *   - o número total de comparações realizadas;
 *   - o número total de trocas realizadas.
 ******************************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 20000 

//Primitiva Swap (inverte 2 valores reais)
void swap(double *a, double *b){
    double temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(double lista[], int n) {
    // contadores
    int comparações = 0;
    int trocas = 0;
    
    // Percorre todos os elementos da lista
    for (int i = 0; i < n-1; i++) {
        int menor = i;
        // Encontra o menor elemento
        for (int k = i+1; k < n; k++) {
            comparações++;
            if (lista[k] < lista[menor])
            menor = k;
        }
        
        // Troca a posição do elemento i com o menor
        if (menor != i) { 
            swap(&lista[menor], &lista[i]);
            trocas++;
        }
    }
    printf("Comparações = %d, Trocas = %d\n", comparações, trocas);
}


//cria uma lista dos 20 mil lances aleatórios
void lista_20k_elementos(double lista[]){
    srand(time(NULL)); 
    for(int i = 0; i < N; i++)
        lista[i] = rand() % 10000000 / 10.0; // valores entre 0.00 e 1000000.00
}

// função auxiliar para imprimir lista
void print_lista (double lista[], int n){
    printf("[");
    for (int i = 0; i < n; i++)
        printf(" %.2f ", lista[i]);
    printf("]\n");
}


int main() {
    // Exemplo enunciado
    double lances_enum[5] = {29.0, 10.0, 14.0, 37.0, 14.0};
    int n_enum = 5;

    
    printf("> Exemplo do enunciado:\nEntrada: ");
    print_lista(lances_enum, n_enum);

    printf("\nUtilizando o método Selection Sort temos:\n");
    selectionSort(lances_enum, n_enum);
    
    printf("Saída: ");
    print_lista(lances_enum, n_enum);
    
    // Exemplo lista 20k lances
    double lances_20k[N];
    // Variáveis temporais:
    clock_t ini_crono;
    clock_t fim_crono;
    
    printf("\n> Para uma lista de 20 mil lances, com SelectionSort temos:\n");
    lista_20k_elementos(lances_20k);
    
    ini_crono = clock(); // inicia o cronometro
    selectionSort(lances_20k, N);
    fim_crono = clock(); // encerra o cronometro
    double cronometro = (double)(fim_crono - ini_crono) / CLOCKS_PER_SEC; //calcula o tempo gasto
    
    printf("Tempo gasto para a resolução do problema: %.5fs\n", cronometro);
    
    return 0;
}