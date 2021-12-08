#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "stm32f10x.h"

void TIM4_PWM_Init(void);
void Set_Speed(unsigned char Direction,signed char Speed);
void Run(signed char speed,int time);      
void Brake(int time);              
void Left(signed char speed,int time);    
void Spin_Left(signed char speed,int time); 
void Right(signed char speed,int time);    
void Spin_Right(signed char speed,int time);
void Back(signed char speed,int time);      

#endif
