/******************************************************************************
Algoritmos e Estrutura de Dados 1 
Atividade Avaliativa 1

Danilo Djovano Selli Junior Nº UFSCar 842868

2) b)
O Problema do Reality Show

Em um reality show, em que "n" participantes estão dispostos em um círculo, ao ser sorteado 
um número "k" maior do que zero, em sentido horário será contado k participantes e o escolhido será elimninado, 
a contagem para as eliminações seguirá a partir do próximo participante e assim por diante até 
sobrar apenas 1. A mecânica do jogo está expressa pela função "reality_show".

Recursão
    Caso base: n = 1 --> retorna 1 (apenas 1 participante)
    Passo recurssivo: n > 1 --> retorna (reality_show(n-1, k) + k - 1) % n + 1


*******************************************************************************/
#include <stdio.h>


int reality_show (int n, int k){
    //Caso base: apenas 1 participante
    if (n == 1) 
        return 1;
        
    // Passo recurssivo: chama a função percorrendo o círculo e eliminando os participantes
    return (reality_show(n-1, k) + k) % n + 1;
    
}

int main(void){
    // Caso do exemplo apresentado no enunciado:
    printf("O vencedor do Reality Show foi o participante: %d\n", reality_show(7,2));
    
    return 0;
}
