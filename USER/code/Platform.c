#include "Platform.h"
#include "Ultrasonic.h"
#include "stm32f10x.h"               

void TIM5_PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 TIM_TimeBaseStructure.TIM_Period = 9999;
	 TIM_TimeBaseStructure.TIM_Prescaler =143;
	 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	 TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
	
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 TIM_OCInitStructure.TIM_Pulse = 0;
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	 
	 TIM_CtrlPWMOutputs(TIM5,ENABLE);	
	 
	 TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable); 
   TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	 
	 TIM_ARRPreloadConfig(TIM5, ENABLE);
   TIM_Cmd(TIM5, ENABLE); 
}

void Roting_Degree(float degree)
{
	degree= 249 + 50 * degree / 9;
	TIM_SetCompare1(TIM5,degree);
}

int Detect(void)
{
	Roting_Degree(90);
	delay_ms(100);
	return Ultrasonic_Measure();
}
int Detect_L_1(void)
{
	Roting_Degree(135);
	delay_ms(300);
	return Ultrasonic_Measure();
}

int Detect_L_2(void)
{
	Roting_Degree(175);
	delay_ms(300);
	return Ultrasonic_Measure();
}
int Detect_R_1(void)
{
	Roting_Degree(45);
	delay_ms(300);
	return Ultrasonic_Measure();
}

int Detect_R_2(void)
{
	Roting_Degree(5);
	delay_ms(300);
	return Ultrasonic_Measure();
}