#include "game_features.h"
#include <stdlib.h> // Para a função rand()
#include "musicas.h"

//Aumento de dificuldade progressivo
int calcularTempo(int rodada) {

    // A cada 2 rodadas, o tempo diminui 200ms e para de diminir em 200ms
    if (rodada <= 2)
        return 1000;
    else if (rodada <= 4)
        return 800;
    else if (rodada <= 6)
        return 600;
    else if (rodada <= 8)
        return 400;
    else if (rodada <= 10)
        return 200;
    else
        return 200;

}

// Gera uma sequência de cores aleatórias
// A funcao recebe um vetor de caracteres e um inteiro
void geraSequencia(char* sequencia, int tamanho_sequencia, uint64_t tempo_inicial) {

    // Semente para a geração de números aleatórios
    srand(tempo_inicial);

    // Vetor de cores
    char cores[4] = {'R', 'G', 'B', 'Y'};
        
    for (int i = 0; i < tamanho_sequencia; i++) {

        sequencia[i] = cores[rand() % 4];
    }
    // Adiciona o caractere nulo ao final da sequência
    sequencia[tamanho_sequencia] = '\0';

    //Imprime a sequencia gerada -- Debug
    // printf("Sequencia gerada: %s\n", sequencia);
}


// Mostra a quantidade de acertos
void mostrarAcertos(int acertos, int BUZZER, int LED_VERMELHO, int LED_VERDE, int LED_AZUL) {
    // Indica que o jogador errou a sequencia
    playRickRoll(BUZZER,LED_VERMELHO);

    // Mostra a quantidade de acertos
    for (int i = 0; i < acertos; i++) {
        //Pisca LED
        pisca_led('B', 300, LED_AZUL, LED_VERMELHO, LED_VERDE);       
    }
}

void mostraCor(char cor, int BUZZER, int LED_VERMELHO, int LED_VERDE, int LED_AZUL, int t_delay){

    //Pisca LED
    pisca_led(cor, t_delay, LED_AZUL, LED_VERMELHO, LED_VERDE, BUZZER);

}


// Mostra a sequência de cores e define qual vai ser a sequência da rodada
void mostrarSequencia(char* sequencia, int rodada, char* sequenciaRodada, int t_delay, int BUZZER, int LED_VERMELHO, int LED_VERDE, int LED_AZUL) {

    sleep_ms(500); // Delay para que não comece a piscar as cores imediatamente após clicar no ultimo botão

    for (int i = 0; i < rodada; i++) {
        char cor = sequencia[i];

        //Adiciona a cor na sequencia da rodada
        sequenciaRodada[i] = cor;
        mostraCor(cor, BUZZER, LED_VERMELHO, LED_VERDE, LED_AZUL, t_delay);
    }
    sequenciaRodada[rodada] = '\0';
}