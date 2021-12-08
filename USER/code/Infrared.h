#ifndef __INFRARED_H_
#define __INFRARED_H_

#include "stm32f10x.h"                  // Device header

void Infrared_Init(void);
void Infrared_Measure(void);

#define IR_R                    GPIO_Pin_1
#define IR_R_GPIO               GPIOB
#define IR_R_D                  GPIO_ReadInputDataBit(IR_R_GPIO, IR_R)

#define IR_L                    GPIO_Pin_8
#define IR_L_GPIO               GPIOA
#define IR_L_D                  GPIO_ReadInputDataBit(IR_L_GPIO, IR_L)

#endif
