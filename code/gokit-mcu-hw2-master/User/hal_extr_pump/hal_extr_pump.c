/**
  ******************************************************************************
  * @file    Hal_extr_pump.c
  * @author  Leo
  * @version 
  * @date  
  * @brief 
  ******************************************************************************/
#include "include.h"

uint8_t g_moist_th;

void Extr_Pump_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_EXTR_PUMP_CLK, ENABLE);
	  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	  
	GPIO_InitStructure.GPIO_Pin = GPIO_EXTR_PUMP_PIN;
	GPIO_Init(GPIO_EXTR_PUMP_PORT, &GPIO_InitStructure);

	return;
}

void Extr_Pump_Ctrl(u8 enableFlag)
{
	if(EXTR_PUMP_ENABLE == enableFlag)
	{
		GPIO_ResetBits(GPIO_EXTR_PUMP_PORT, GPIO_EXTR_PUMP_PIN);
	}
	else
	{
		GPIO_SetBits(GPIO_EXTR_PUMP_PORT, GPIO_EXTR_PUMP_PIN);
	}

	return;
}

void Extr_Pump_Proc(u8 moistValue, bool isAutoMode, bool pumpSwitch)
{
	if(TRUE == isAutoMode)
	{
		if(moistValue < g_moist_th)
		{
			Pump_Ctrl(PUMP_DISABLE);
			printf("auto disable pump, mositure:%d\r\n",moistValue);
		}
		else
		{
			Pump_Ctrl(PUMP_ENABLE);	
			printf("auto enable pump, mositure:%d\r\n",moistValue);		
		}
	}
	else
	{
		Extr_Pump_Ctrl(pumpSwitch);	
		printf("manual pump, pumpSwitch:%d\r\n",pumpSwitch);		
	}
	

	return;
}

void Extr_Pump_SetMoistTh(u8 moist_th)
{
	g_moist_th = moist_th;

	return;
}


