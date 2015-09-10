/**
  ******************************************************************************
  * @file    Hal_pump.c
  * @author  Leo
  * @version 
  * @date  
  * @brief 
  ******************************************************************************/
#include "include.h"

uint8_t g_cycle_pump_peri;

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

void Pump_Proc(bool isAutoMode, bool pumpSwitch)
{

	if(TRUE == isAutoMode)
	{
	}
	else
	{
		Pump_Ctrl(pumpSwitch);	
		printf("manual pump, pumpSwitch:%d\r\n",pumpSwitch);	
	}
	return;
}


