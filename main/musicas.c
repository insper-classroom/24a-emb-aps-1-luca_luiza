#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "acionamentos.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

void playMusica(int freq, int tempo, int pino) {
    int calcula_repeticoes = tempo*freq/1000;
    for (int i = 0; i < (calcula_repeticoes); i++) {
        int tempo_sleep = (1000000/freq)/2;
        gpio_put(pino, 1);
        sleep_us(tempo_sleep);
        gpio_put(pino, 0);
        sleep_us(tempo_sleep);
    }
}

void playRickRoll(int pin, int LED_R) {
    int melody[] = {
    // Rick Roll
    NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
    NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

    NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
    NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8, 
    NOTE_E5,4, NOTE_D5,2
};
;
    int melodyLength = sizeof(melody) / sizeof(melody[0]) / 2;
    int tempo = 114;

    float wholenote = (60000 * 4) / (float)tempo;

    for (int thisNote = 0; thisNote < melodyLength * 2; thisNote = thisNote + 2) {
        gpio_put(LED_R, 1);
        float divider = melody[thisNote + 1];
        float noteDuration = 0; // Initialize noteDuration
        if (divider > 0) {
            noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
            noteDuration = (wholenote) / (float)abs(divider);
            noteDuration *= 1.5;
        }
        playMusica(melody[thisNote], noteDuration, pin);
        sleep_ms(1); // Optional pause between notes
        gpio_put(LED_R, 0);
    }

}

void playIntro(int pin, int LED_R, int LED_B) {
    int melody[] = {

    // Pacman
    // Score available at https://musescore.com/user/85429/scores/107109
    NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
    NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
    NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

    NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
    NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
    NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8

    };
    int melodyLength = sizeof(melody) / sizeof(melody[0]) / 2;
    int tempo = 105;

    float wholenote = (60000 * 4) / (float)tempo;

    for (int thisNote = 0; thisNote < melodyLength * 2; thisNote = thisNote + 2) {
        gpio_put(LED_B, 1);
        gpio_put(LED_R, 1);
        float divider = melody[thisNote + 1];
        float noteDuration = 0; // Initialize noteDuration
        if (divider > 0) {
            noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
            noteDuration = (wholenote) / (float)abs(divider);
            noteDuration *= 1.5;
        }
        playMusica(melody[thisNote], noteDuration, pin);

        sleep_ms(1); // Optional pause between notes
        gpio_put(LED_B, 0);
        gpio_put(LED_R, 0);
    }

}
