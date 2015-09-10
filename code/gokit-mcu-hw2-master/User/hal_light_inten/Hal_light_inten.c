/**
  ******************************************************************************
  * @file    Hal_light_inten.c
  * @author  leo
  *******************************************************************************/ 
#include "include.h"
#include "Hal_light_inten.h"
#include "Hal_moisture.h"

extern Device_WirteTypeDef   					  Device_WirteStruct;
u8 g_light_th = 0;
/*
 * 函数名：TIM4_GPIO_Config
 * 描述  ：配置TIM4复用输出PWM时用到的I/O
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM4_GPIO_Config(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* GPIOA and GPIOB clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE); 
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
	
   /*GPIOB Configuration: TIM4 channel 3 and 4 as alternate function push-pull */
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/*
 * 函数名：TIM4_Mode_Config
 * 描述  ：配置TIM4输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM4_Mode_Config(void)
{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM信号电平跳变值 */
	u16 CCR1_Val = 500;        
	u16 CCR2_Val = 500;


/* -----------------------------------------------------------------------
    TIM4 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM4CLK = 72 MHz, Prescaler = 0x0, TIM4 counter clock = 72 MHz
    TIM4 ARR Register = 999 => TIM4 Frequency = TIM4 counter clock/(ARR + 1)
    TIM4 Frequency = 72 KHz.
    TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR)* 100 = 50%
    TIM4 Channel2 duty cycle = (TIM4_CCR2/ TIM4_ARR)* 100 = 37.5%
    TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 25%
    TIM4 Channel4 duty cycle = (TIM4_CCR4/ TIM4_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);	  //使能通道2
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //使能定时器2
}

void Light_Init(void)
{
	#if 0
	TIM4_GPIO_Config();
	TIM4_Mode_Config();
	#endif
	Light_gpio_Init();
	Light_adc_Init();

	return;
}

void Light_gpio_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LIGHT_GPIO_CLK, ENABLE);
	  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	  
	GPIO_InitStructure.GPIO_Pin = LIGHT_GPIO_PIN1;
	GPIO_Init(LIGHT_GPIO_PORT1, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(LIGHT_GPIO_CLK2, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LIGHT_GPIO_PIN2;
	GPIO_Init(LIGHT_GPIO_PORT2, &GPIO_InitStructure);

	return;
}



void Light_CfgInten(u8 m1,u8 m2)
{
	u16 temp = (LIGHT_ARR+1) / LIGHT_MAX;
	
	TIM_SetCompare1(TIM4,m1*temp);	
	TIM_SetCompare2(TIM4,m2*temp);	

	return;
}

void Light_Ctrl(u16 Level)
{		
	if(Level == 0)
	{
		GPIO_SetBits(LIGHT_GPIO_PORT1, LIGHT_GPIO_PIN1);
		GPIO_SetBits(LIGHT_GPIO_PORT2, LIGHT_GPIO_PIN2);	
		//GPIO_ResetBits(LIGHT_GPIO_PORT1, LIGHT_GPIO_PIN1);
		//GPIO_ResetBits(LIGHT_GPIO_PORT2, LIGHT_GPIO_PIN2);
	}
	else if(Level == 1)
	{
		GPIO_SetBits(LIGHT_GPIO_PORT1, LIGHT_GPIO_PIN1);
		GPIO_ResetBits(LIGHT_GPIO_PORT2, LIGHT_GPIO_PIN2);		
	}
	else if(Level == 2)
	{
		GPIO_ResetBits(LIGHT_GPIO_PORT1, LIGHT_GPIO_PIN1);
		GPIO_ResetBits(LIGHT_GPIO_PORT2, LIGHT_GPIO_PIN2);
		//GPIO_SetBits(LIGHT_GPIO_PORT1, LIGHT_GPIO_PIN1);	
		//GPIO_SetBits(LIGHT_GPIO_PORT2, LIGHT_GPIO_PIN2);
	}
	
	return;
}
void Light_Proc(u16 meaIntens, u16 appLedCfg, bool isAutoMode)
{		

	if(TRUE == isAutoMode)
	{
		if(meaIntens < g_light_th)
		{
			Light_Ctrl(2);			
		}
		else
		{
			Light_Ctrl(0);		
		}
	}
	else
	{
		printf("appCfgIntens:%d\r\n",appLedCfg);
		Light_Ctrl(appLedCfg);
	}

	return;
}

void Light_adc_Init(void)	   
{
 	ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable ADC and GPIOA clock */
	RCC_APB2PeriphClockCmd(LIGHT_RCC_ADC | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12MHZ 
		
	/* Configure ADC Channel as analog input -------------------------*/
	GPIO_InitStructure.GPIO_Pin = LIGHT_ADC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(LIGHT_ADC_GPIO_PORT, &GPIO_InitStructure);
		
	ADC_DeInit(LIGHT_ADC);//
		
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(LIGHT_ADC, &ADC_InitStructure);
		
	/* Enable ADC1 */
	ADC_Cmd(LIGHT_ADC, ENABLE);
	
    /* Enable ADC1 reset calibration register */	 
    ADC_ResetCalibration(LIGHT_ADC);
    
    /* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(LIGHT_ADC));
	
	/* Start ADC1 calibration */
	ADC_StartCalibration(LIGHT_ADC);

	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(LIGHT_ADC));

	return;
}

u8 Light_SensorRead(void)
{	
	u16 LightVal;
	
	LightVal =	ADC_GetAvgVal(LIGHT_ADC_CHANNEL, 4, LIGHT_ADC);

	printf("light intensity value:%d \r\n", LightVal);

	return (LightVal >> LIGHT_VALUE_SHIFT);
}

void Light_Set_Th(u8 light_th)
{
	g_light_th = light_th;

	return;
}

