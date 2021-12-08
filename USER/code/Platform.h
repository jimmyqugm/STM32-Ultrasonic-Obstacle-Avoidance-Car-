#ifndef __PLATFORM_H
#define __PLATFORM_H
#include "stm32f10x.h"                  // Device header

void TIM5_PWM_Init(void);
void Roting_Degree(float degree);
int Detect(void);
int Detect_L_1(void);
int Detect_R_1(void);
int Detect_L_2(void);
int Detect_R_2(void);
	
#endif 
