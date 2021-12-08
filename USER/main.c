#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "Ultrasonic.h"
#include "Platform.h"
#include "Infrared.h"

 int main(void)
 {	
	 int Distance_F ,Distance_L, Distance_R;
	 int Distance_L_1, Distance_R_1, Distance_L_2, Distance_R_2;
	 Ultrasonic_Init();        //ultrasonic mode init
	 TIM4_PWM_Init();          //DC motor init
	 TIM5_PWM_Init();          //servo init
	 Infrared_Init();          //infared init
	 delay_init();
	 Brake(100);		
	while(1)
	{  		
		Run(60,5);
		Infrared_Measure();
		Distance_F = Detect();
		if(Distance_F < 80 && Distance_F > 0) //forward obstacle
		{
			Brake(500);		
			Back(60,500);	
			Brake(500);	
			
			Distance_L_1= Detect_L_1();
			delay_ms(200);
			Distance_L_2= Detect_L_2();
			delay_ms(200);
			Distance_R_1= Detect_R_1();
			delay_ms(200);
			Distance_R_2= Detect_R_2();
			delay_ms(200);
			Distance_L = Distance_L_1 + Distance_L_2;
			Distance_R = Distance_R_1 + Distance_R_2;
			
			if(Distance_L > Distance_R)
			{
				Left(60,1000);
				Brake(100);
			}	
      else
			{
				Right(60,1000);
				Brake(100);					
			}								
	}
 }
}
