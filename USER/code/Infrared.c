#include "Infrared.h"
#include "delay.h"
#include "motor.h"
#include "stm32f10x.h"                

int R,L;
void Infrared_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = IR_R;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IR_R_GPIO , &GPIO_InitStructure); 
	
  GPIO_InitStructure.GPIO_Pin = IR_L;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IR_L_GPIO , &GPIO_InitStructure); 
}


void Infrared_Measure(void)
{
	R = IR_R_D;
	L = IR_L_D;
	if(L == 1 && R == 1)
	{
		 Run(60,5);	
	}
	else if (L == 1 && R == 0)
	{
		  Right(70,300);
	}
	else if(R == 1 && L == 0)
	{
		   Left(70,300);
	}
}
