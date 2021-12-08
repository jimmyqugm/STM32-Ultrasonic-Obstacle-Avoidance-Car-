#include "Ultrasonic.h"
#include "delay.h"
#include "stm32f10x.h" 


#define	TRIG_PORT      GPIOC		//TRIGGER      
#define	ECHO_PORT      GPIOC		//ECHO 
#define	TRIG_PIN       GPIO_Pin_0   //TRIGGER       
#define	ECHO_PIN       GPIO_Pin_1	//ECHO   

float Ultrasonic_Distance;      //distance to obstcle   

/*
 * Function name£ºUltrasonic_Init
 * Description  £ºinitialize sensor
 */
void Ultrasonic_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;              //external interrupt
 	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE); //enable clock
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					  //PC0 to TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //push-pull output
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	      //init GPIOC0

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				   //PC1 to ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //input
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);				 //init GPIOC1
	
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);	//Connect EXTI Line 1 to GPIO Pin PC1

 	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;     //when the echo signal come interrupt
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		                         
		
			
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			     //Enable exti1
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			   
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						 
  NVIC_Init(&NVIC_InitStructure);  	                        
}

void EXTI1_IRQHandler(void)             // interupt function
{
	delay_us(10);		                      
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
			TIM_SetCounter(TIM2,0);
			TIM_Cmd(TIM2, ENABLE);                                       //count the echo time
		
			while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	           //waiting for the low value

			TIM_Cmd(TIM2, DISABLE);			                                 //close the timer
			Ultrasonic_Distance=TIM_GetCounter(TIM2)*5*34/200;			//calculate the Distance
	  
			EXTI_ClearITPendingBit(EXTI_Line1);  
	}
}
/*
 * Function name£ºUltrasonic_Measure
 * Description  £ºmeasure the distance£¬send a 15us pluse and caculate the echo time
 */
int Ultrasonic_Measure(void)
{
  int temp;
	GPIO_SetBits(TRIG_PORT,TRIG_PIN); 	
  delay_us(15);		                      //15us wait
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
	temp = Ultrasonic_Distance*10;
	return temp;
}
