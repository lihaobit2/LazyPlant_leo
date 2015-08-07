/**
  ******************************************************************************
  * @file    Hal_pump.c
  * @author  Leo
  * @version 
  * @date  
  * @brief 
  ******************************************************************************/
#include "include.h"


void Pump_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_PUMP_CLK, ENABLE);
	  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	  
	GPIO_InitStructure.GPIO_Pin = GPIO_PUMP_PIN;
	GPIO_Init(GPIO_PUMP_PORT, &GPIO_InitStructure);

	return;
}

void Pump_Ctrl(u8 enableFlag)
{
	if(PUMP_ENABLE == enableFlag)
	{
		GPIO_ResetBits(GPIO_PUMP_PORT, GPIO_PUMP_PIN);
	}
	else
	{
		GPIO_SetBits(GPIO_PUMP_PORT, GPIO_PUMP_PIN);
	}

	return;
}

void Pump_Proc(u16 moistValue, bool isAutoMode, bool pumpSwitch)
{

	if(TRUE == isAutoMode)
	{
		if(moistValue < PUMP_THRESHOLD)
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
			Pump_Ctrl(pumpSwitch);	
			printf("manual pump, pumpSwitch:%d\r\n",pumpSwitch);	
	}
	return;
}


