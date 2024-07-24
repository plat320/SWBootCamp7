#include "device_driver.h"

#define TIM3_FREQ           (8000000)           // Hz
#define TIM3_TICK           (1000000/TIM3_FREQ) // usec
#define TIME3_PLS_OF_1ms    (1000/TIM3_TICK)

// 주파수 정의
#define C4  261
#define D4  294
#define E4  329
#define F4  349
#define G4  392
#define A4  440
#define B4  493

#define C5  523
#define D5  587
#define E5  659
#define F5  698
#define G5  784
#define A5  880
#define B5  988

#define NOTE_DURATION (200) // 기본 노트 길이 (밀리초)
#define COIN_NOTE_DURATION (50) // 기본 노트 길이 (밀리초)
#define DEAD_NOTE_DURATION (20) // 기본 노트 길이 (밀리초)

void TIM3_Out_Init(void);
void TIM3_Out_Freq_Generation(unsigned short freq);
void TIM3_Out_Stop(void);
void play_tone(unsigned short freq, unsigned int duration_ms);
void play_coin();
void play_dead();
void play_melody();
