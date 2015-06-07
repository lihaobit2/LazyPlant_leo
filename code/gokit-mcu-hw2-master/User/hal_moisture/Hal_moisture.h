#ifndef _HAL_MOISTURE_H
#define _HAL_MOISTURE_H

#include "stm32f10x_adc.h"

#define MOIST_MAX_VALUE 4095
#define MOSIT_SHIFT 4


#define MOIST_ADC ADC1
#define MOIST_RCC_ADC RCC_APB2Periph_ADC1
#define MOIST_ADC_CHANNEL  ADC_Channel_1


void Moist_Init(void);
u16 Moist_Read(void);
u16 ADC_GetAvgVal(u8 ch,u8 n, ADC_TypeDef* ADCx); 
u16 ADC_GetVal(u8 ch, ADC_TypeDef* ADCx);

#endif

