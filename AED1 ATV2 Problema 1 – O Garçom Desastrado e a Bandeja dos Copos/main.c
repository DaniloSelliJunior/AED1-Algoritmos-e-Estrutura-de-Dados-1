/******************************************************************************
Algoritmos e Estrutura de Dados I  
Atividade Avaliativa 2  

Aluno: Danilo Djovano Selli Junior  
RA: 842868 – UFSCar  

Problema 1 – O Garçom Desastrado e a Bandeja dos Copos  

Um garçom precisa organizar copos de diferentes alturas sobre uma bandeja.  
Por segurança, ele só compara copos adjacentes e, se necessário, troca-os de lugar, 
até que todos estejam em ordem crescente.  

Para resolver o problema, utiliza-se o algoritmo BubbleSort, que recebe uma lista 
com as alturas dos copos e retorna:  
- a lista ordenada;  
- o número total de comparações realizadas;  
- o número total de trocas efetuadas.  

*******************************************************************************/
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

void bubbleSort(double copos[], int n) {
    // contadores
    int comparações = 0;
    int trocas = 0;
    
    // Percorre cada elemento do array L
    for (int i= n-1; i >= 1; i--) 
        for (int j= 0; j < i; j++) {  // Flutua o maior elemento para a posição mais a direita
            comparações++;
            if (copos[j] > copos[j+1]){
                swap(&copos[j], &copos[j+1]);
                trocas++;
            }
        }
    printf("Comparações = %d, Trocas = %d\n", comparações, trocas);
}

//cria uma lista da alturas aleatórias de 20 mil copos
void lista_20k_copos(double copos[]){
    srand(time(NULL)); 
    for(int i = 0; i < N; i++)
        copos[i] = rand() % 2001 / 100.0; // valores entre 0.00 e 20.00
}

// função auxiliar para imprimir lista
void print_lista (double copos[], int n){
    printf("[");
    for (int i = 0; i < n; i++)
        printf(" %.2f ", copos[i]);
    printf("]\n");
}


int main() {
    // Exemplo enunciado
    double copos_enum[4] = {4, 3, 2, 1};
    int n_enum = 4;

    
    printf("> Exemplo do enunciado:\nEntrada: ");
    print_lista(copos_enum, n_enum);

    printf("\nUtilizando o método BubbleSort temos:\n");
    bubbleSort(copos_enum, n_enum);
    
    printf("Saída: ");
    print_lista(copos_enum, n_enum);
    
    // Exemplo lista 20k copos
    double copos_20k[N];
    // Variáveis temporais:
    clock_t ini_crono;
    clock_t fim_crono;
    
    printf("\n> Para uma lista de 20 mil copos, com BubbleSort temos:\n");
    lista_20k_copos(copos_20k);
    
    ini_crono = clock(); // inicia o cronometro
    bubbleSort(copos_20k, N);
    fim_crono = clock(); // encerra o cronometro
    double cronometro = (double)(fim_crono - ini_crono) / CLOCKS_PER_SEC; //calcula o tempo gasto
    
    printf("Tempo gasto para a resolução do problema: %.5fs\n", cronometro);
    
    return 0;
}