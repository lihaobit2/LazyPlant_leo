/**
  ******************************************************************************
  * @file    Hal_moisture.c
  * @author  Leo
  * @version 
  * @date  
  * @brief 
  ******************************************************************************/
#include "include.h"
#include "stm32f10x_adc.h"


void Moist_Init(void)	   
{
 	ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable MOIST_ADC and GPIOA clock */
	RCC_APB2PeriphClockCmd(MOIST_RCC_ADC | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12MHZ 
		
	/* Configure PA.1 (ADC Channel) as analog input -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	//ADC_DeInit(MOIST_ADC);//
		
	/* MOIST_ADC configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(MOIST_ADC, &ADC_InitStructure);
		
	/* Enable MOIST_ADC */
	ADC_Cmd(MOIST_ADC, ENABLE);
	
    /* Enable MOIST_ADC reset calibration register */	 
    ADC_ResetCalibration(MOIST_ADC);
    
    /* Check the end of MOIST_ADC reset calibration register */
	while(ADC_GetResetCalibrationStatus(MOIST_ADC));
	
	/* Start MOIST_ADC calibration */
	ADC_StartCalibration(MOIST_ADC);

	/* Check the end of MOIST_ADC calibration */
	while(ADC_GetCalibrationStatus(MOIST_ADC));

	return;
}

u16 Moist_Read(void)
{	
	u16 MoistVal;
	
	MoistVal =	ADC_GetAvgVal(MOIST_ADC_CHANNEL, 4, MOIST_ADC);

	printf("Moisture value:%d  \r\n", MoistVal);

	/*为了便于理解，即湿度越大，值越大，做一个转换再返回*/
	return ((MOIST_MAX_VALUE - MoistVal) >> MOSIT_SHIFT);
}

u16 ADC_GetVal(u8 ch, ADC_TypeDef* ADCx)
{
	u16 DataValue;
	
	/*  regular channel14 configuration */ 
    ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_239Cycles5);
			
	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);

	/* Test if the ADC1 EOC flag is set or not */ 
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));

	/*Returns the ADC1 Master data value of the last converted channel*/
	DataValue = ADC_GetConversionValue(ADCx); 

	return DataValue; 
}	 

u16 ADC_GetAvgVal(u8 ch,u8 n, ADC_TypeDef* ADCx) 
{	
	u32 ad_sum = 0; 
	u8 i; 
	for(i=0;i<n;i++)

	{
		ad_sum += ADC_GetVal(ch, ADCx);
		Delay_ms(5); 
	}

	return (ad_sum/n);
}
