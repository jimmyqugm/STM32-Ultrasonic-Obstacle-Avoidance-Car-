#include "motor.h"
#include "Math.h"
#include "delay.h"
#include "stm32f10x.h"                

#define L                         GPIO_Pin_7
#define L_GPIO                    GPIOB
#define L_SET                     GPIO_SetBits(L_GPIO,L)
#define L_RESET                   GPIO_ResetBits(L_GPIO,L)

#define L_PWM         				    GPIO_Pin_8
#define L_PWM_GPIO                GPIOB
#define L_PWM_SET                 GPIO_SetBits(L_PWM_GPIO,L_PWM)
#define L_PWM_RESET               GPIO_ResetBits(L_PWM_GPIO,L_PWM)

#define R                          GPIO_Pin_4
#define R_GPIO                     GPIOA
#define R_SET                      GPIO_SetBits(R_GPIO,R)
#define R_RESET                    GPIO_ResetBits(R_GPIO,R)

#define R_PWM                      GPIO_Pin_9
#define R_PWM_GPIO                 GPIOB
#define R_PWM_SET                  GPIO_SetBits(R_PWM_GPIO,R_PWM)
#define R_PWM_RESET                GPIO_ResetBits(R_PWM_GPIO,R_PWM)

void TIM4_PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;               //PWM
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //enable TIM4 & GPIO clock
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE);  
	
  GPIO_InitStructure.GPIO_Pin = L;                      //Left motor direction PB7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(L_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = L_PWM;                  //Left motor PWM PB8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	   
	GPIO_Init(L_PWM_GPIO, &GPIO_InitStructure);  
		
	
  GPIO_InitStructure.GPIO_Pin = R;                  //right motor direction  PA4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_Init(R_GPIO, &GPIO_InitStructure); 
	
	
	GPIO_InitStructure.GPIO_Pin = R_PWM;       //Right motor PWM  PB9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    
	GPIO_Init(R_PWM_GPIO, &GPIO_InitStructure);  //enable GPIO
	
	TIM_TimeBaseStructure.TIM_Period = 9999;
	TIM_TimeBaseStructure.TIM_Prescaler = 143;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //init TIM4
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE);		
  
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  	 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  
	
  TIM_ARRPreloadConfig(TIM4, ENABLE); //enable TIM4   
 	TIM_Cmd(TIM4, ENABLE);  
}

void Set_Speed(unsigned char Direction,signed char Speed)
{
		short count;
	
		if (Speed>=100) Speed = 100;
	  if (Speed<=-100) Speed = -100;
	
   	count = 7201 - fabs(Speed)*72;
	switch(Direction)
	{
		case 0:
			TIM_SetCompare3(TIM4, count);
			if (Speed>0) 
				R_RESET;
			else if(Speed<0) 
				R_SET;		
			break;
		case 1:
		  TIM_SetCompare4(TIM4, count); 
			if (Speed>0) 
				L_SET;
			else if (Speed<0)
				L_RESET;
			break;			
	}
}


void Run(signed char speed,int time)
{
		  signed char L_speed = - speed;
	    Set_Speed(1,L_speed);
			Set_Speed(0,speed);
			delay_ms(time);               
}

void Brake(int time) 
{
	  Set_Speed(1,0);
	  Set_Speed(0,0);
	  R_RESET;
	  L_RESET;
		delay_ms(time);     
}

void Left(signed char speed,int time) 
{
	  Set_Speed(1,0);
	  Set_Speed(0,speed);       
		delay_ms(time);               
}
void Spin_Left(signed char speed,int time)
{
	  signed char R_speed = 100 - speed; 
 	  Set_Speed(1,speed);
	  Set_Speed(0,R_speed);            
		delay_ms(time);                  
}
void Right(signed char speed,int time)  
{
	  signed char L_speed = - speed;
	  Set_Speed(1,L_speed);
	  Set_Speed(0,0);                
		delay_ms(time);                  
}
void Spin_Right(signed char speed,int time) 
{
	  signed char L_speed = 100 - speed;
	  signed char R_speed = - speed;
	  Set_Speed(1,-L_speed);
	  Set_Speed(0,R_speed);    
		delay_ms(time);         
}
void Back(signed char speed,int time) 
{
	  signed char L_speed = 100- speed;
	  signed char R_speed = - L_speed;
	  Set_Speed(1,L_speed);
	  Set_Speed(0,R_speed);
		delay_ms(time);        
}
