/******************************************************************************
Algoritmos e Estrutura de Dados 1 
Atividade Avaliativa 1

Danilo Djovano Selli Junior Nº UFSCar 842868

3)
Problema: O Labirinto Mágico do Feiticeiro

Em um labirinto representado por uma matriz N x N, começando no canto superior esquerdo (0, 0) e,
uilizando recursão e Backtracking, deve mover-se com destino no canto inferior direito (N-1, N-1).
Regras:
    - Células seguras: 1
    - Células amaldiçoadas: 0
    - Movimentos permitidos: 
        →  (direita)
        ↓  (baixo)
        ↘  (diagonal inferior-direita)
    - Cada célula visitada vira amaldiçoada temporariamente 


*******************************************************************************/
#include <stdio.h>
#include <string.h>
#define N 5 //dimensão do labirinto

//Variáveis globais
char *movimento[] = {"→", "↘", "↓"};    // Vetor (string) para imprimir os movimentos 
int mov_linha[] = {0, 1, 1};            // Vetor p/ representar mudança na linha: 0=mesma linha (→), 1=linha+1 (↘ ou ↓)
int mov_coluna[] = {1, 1, 0};           // Vetor p/ representar mudança na coluna: 1=coluna+1 (→ ou ↘), 0=mesma coluna (↓)

//contador de caminhos possíveis e permitidos
int total_caminhos = 0;

// Função recursiva para explorar os caminhos
void percorre_labirinto(int linha, int coluna, char caminho[][4], int passo, int matriz[N][N]) {
    //Caso posição amaldiçoado
    if (matriz[linha][coluna] == 0)
        return;
    
    // Marca a posição passada como zero
    matriz[linha][coluna] = 0;
        
    // Caso base: chegou ao destino
    if (linha == N-1 && coluna == N-1) {
        total_caminhos++;
        printf("Caminho %d: ", total_caminhos);
        for (int i = 0; i < passo; i++) {
            printf("%s ", caminho[i]); //imprime os caminhos percorridos
        }
        printf("\n");
        matriz[linha][coluna] = 1; // restaura antes de retornar
        return;
    }
    
    // Loop para tentar os 3 movimentos, salvar o movimento permitido e realizar as chamadas recurssiva
    for (int k = 0; k < 3; k++) {
        int prox_linha = linha + mov_linha[k];
        int prox_coluna = coluna + mov_coluna[k];
        
        // Verificação do caminho
        if (prox_linha >= 0 && prox_linha < N && prox_coluna >= 0 && prox_coluna < N && matriz[prox_linha][prox_coluna] == 1) {
            strcpy(caminho[passo], movimento[k]); // guarda o movimento realizado em "caminho"
            percorre_labirinto(prox_linha, prox_coluna, caminho, passo+1, matriz); // chamada recursiva 
        }
    }
    
    // Backtracking: restaura célula
    matriz[linha][coluna] = 1;
}


int main(void){
   
   //Teste com a matriz do enunciado (1 = seguro, 0 = amaldiçoado)
    int matriz_labirinto[N][N] = {                   
                        {1, 1, 1, 0, 1},
                        {1, 0, 1, 1, 1},
                        {0, 1, 1, 1, 0},
                        {1, 0, 1, 0, 1},
                        {0, 1, 1, 1, 1}
                                       };
                                       
                                       
    char caminho[50][4]; // Matriz para salvar todos os caminhos possíveis
    total_caminhos = 0;
    
    percorre_labirinto(0, 0, caminho, 0, matriz_labirinto);
    printf("O número total de caminhos para o labirinto é: %d", total_caminhos);
    
    return 0;
}