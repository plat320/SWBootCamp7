#include "bgm.h"
#include "OS.h"

void TIM3_Out_Init(void)
{
    Macro_Set_Bit(RCC->APB1ENR, 1);
    Macro_Set_Bit(RCC->APB2ENR, 3);
    Macro_Write_Block(GPIOB->CRL,0xf,0xb,0);
    Macro_Write_Block(TIM3->CCMR2,0x7,0x6,4);
    TIM3->CCER = (0<<9)|(1<<8);
}

void TIM3_Out_Freq_Generation(unsigned short freq)
{
    TIM3->PSC = (unsigned int)(TIMXCLK/(double)TIM3_FREQ + 0.5)-1;
    TIM3->ARR = (double)TIM3_FREQ/freq-1;
    TIM3->CCR3 = TIM3->ARR/2;

    Macro_Set_Bit(TIM3->EGR,0);
    TIM3->CR1 = (1<<4)|(0<<3)|(0<<1)|(1<<0);
}

void TIM3_Out_Stop(void)
{
    Macro_Clear_Bit(TIM3->CR1, 0);
    Macro_Clear_Bit(TIM3->DIER, 0);
}

void play_tone(unsigned short freq, unsigned int duration_ms)
{
    if (freq == 0) {
        TIM3_Out_Stop();
    } else {
        TIM3_Out_Freq_Generation(freq);
    }
    OS_Block_Current_Task(duration_ms); // 주어진 시간만큼 대기
    TIM3_Out_Stop();
    OS_Block_Current_Task(10); // 노트 사이의 짧은 휴식
}

void play_coin()
{
    unsigned short melody[] = {G5, A5};

    int melody_length = sizeof(melody) / sizeof(melody[0]);

    int i;
    for (i = 0; i < melody_length; i++) {
        play_tone(melody[i], NOTE_DURATION);
    }
}

void play_dead()
{
    unsigned short melody[] = {G4, G4, G4};

    int melody_length = sizeof(melody) / sizeof(melody[0]);

    int i;
    for (i = 0; i < melody_length; i++) {
        play_tone(melody[i], NOTE_DURATION);
    }
}

void play_melody()
{
    unsigned short melody[] = {
        E4, E4, E4, C4, E4, G4,
        G4, C4, G4, E4,
        A4, B4, A4, G4, E4, G4, A4,
        F4, G4, E4, C4, D4, B4,

        E4, E4, E4, C4, E4, G4,
        G4, C4, G4, E4,
        A4, B4, A4, G4, E4, G4, A4,
        F4, G4, E4, C4, D4, B4
    };

    int melody_length = sizeof(melody) / sizeof(melody[0]);

    int i;
    for (i = 0; i < melody_length; i++) {
        play_tone(melody[i], NOTE_DURATION);
    }
}
