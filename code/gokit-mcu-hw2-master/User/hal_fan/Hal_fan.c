/**
  ******************************************************************************
  * @file    Hal_fan.c
  * @author  leo
  *******************************************************************************/ 
#include "include.h"
#include "hal_fan.h"


/*
 * 函数名：TIM2_GPIO_Config
 * 描述  ：配置TIM2复用输出PWM时用到的I/O
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM2_GPIO_Config(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* GPIOA and GPIOB clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE); 
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
	
   /*GPIOB Configuration: TIM2 channel 3 and 4 as alternate function push-pull */
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/*
 * 函数名：TIM2_Mode_Config
 * 描述  ：配置TIM2输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM2_Mode_Config(void)
{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM信号电平跳变值 */
	u16 CCR1_Val = 500;        
	u16 CCR2_Val = 500;


/* -----------------------------------------------------------------------
    TIM2 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM2CLK = 72 MHz, Prescaler = 0x0, TIM2 counter clock = 72 MHz
    TIM2 ARR Register = 999 => TIM2 Frequency = TIM2 counter clock/(ARR + 1)
    TIM2 Frequency = 72 KHz.
    TIM2 Channel1 duty cycle = (TIM2_CCR1/ TIM2_ARR)* 100 = 50%
    TIM2 Channel2 duty cycle = (TIM2_CCR2/ TIM2_ARR)* 100 = 37.5%
    TIM2 Channel3 duty cycle = (TIM2_CCR3/ TIM2_ARR)* 100 = 25%
    TIM2 Channel4 duty cycle = (TIM2_CCR4/ TIM2_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //使能通道2
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);                   //使能定时器2
}

void Fan_Init(void)
{
	TIM2_GPIO_Config();
	TIM2_Mode_Config();
	
}


void Fan_Ctrl(u8 m1,u8 m2)
{
	u16 temp = (FAN_ARR+1) / FAN_MAX;
	
	TIM_SetCompare1(TIM2,m1*temp);	
	TIM_SetCompare2(TIM2,m2*temp);	
	
}

void Fan_status(uint16_t status)
{		
	if(status == 5)
	{
		Fan_Ctrl(0,0);
	}
	else if (status > 5)
	{
		Fan_Ctrl(status*10,0);
	}
	else if (status < 5)
	{
		Fan_Ctrl(0,(10-status)*10);
	}

}
