/**
  ******************************************************************************
  * @file    Hal_fan.c
  * @author  leo
  *******************************************************************************/ 
#include "include.h"
#include "hal_fan.h"


/*
 * ��������TIM2_GPIO_Config
 * ����  ������TIM2�������PWMʱ�õ���I/O
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
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
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/*
 * ��������TIM2_Mode_Config
 * ����  ������TIM2�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM2_Mode_Config(void)
{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM�źŵ�ƽ����ֵ */
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

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);                   //ʹ�ܶ�ʱ��2
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
