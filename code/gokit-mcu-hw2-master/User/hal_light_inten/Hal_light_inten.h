#ifndef _HAL_LIGHT_INTEN_H
#define _HAL_LIGHT_INTEN_H

#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

#define FAN_STOP        0

#define LIGHT_ARR 899 //8kHZ
#define LIGHT_MAX 100
#define LIGHT_MAX1 -100
#define LIGHT_MIN 0


#define LIGHT_INTENS_LEVEL_THRESHOLD 3
#define LIGHT_INTENS_LEVEL_MIN 0
#define LIGHT_INTENS_LEVEL_MAX 6


#define LIGHT_INTENS_SENSOR_THRESHOLD 1000
#define LIGHT_INTENS_SENSOR_MAX_VAL 4095
#define LIGHT_INTENS_SENSOR_MIN_VAL 0

#define LIGHT_APP_CFG_THRESHOLD 5
#define LIGHT_APP_CFG_MAX_VAL 10
#define LIGHT_APP_CFG_MIN_VAL 0


#define LIGHT_VALUE_SHIFT 4


#define LIGHT_ADC ADC1
#define LIGHT_RCC_ADC RCC_APB2Periph_ADC1
#define LIGHT_ADC_CHANNEL ADC_Channel_0
#define LIGHT_ADC_GPIO_PIN GPIO_Pin_0
#define LIGHT_ADC_GPIO_PORT GPIOA

#define LIGHT_GPIO_CLK    RCC_APB2Periph_GPIOB
#define LIGHT_GPIO_PORT1   GPIOB
#define LIGHT_GPIO_PIN1    GPIO_Pin_11
//#define LIGHT_GPIO_PORT2   GPIOB
//#define LIGHT_GPIO_PIN2    GPIO_Pin_13
#define LIGHT_GPIO_CLK2    RCC_APB2Periph_GPIOA
#define LIGHT_GPIO_PORT2   GPIOA
#define LIGHT_GPIO_PIN2    GPIO_Pin_5


void Light_Init(void);
void Light_status(u16 status);
u8 Light_SensorRead(void);
void Light_Proc(u16 meaIntens, u16 appCfgIntens, bool isAutoMode);
void Light_Ctrl(u16 intensLevel);
void Light_adc_Init(void);	   
void Light_gpio_Init(void);

#endif /*_HAL_Inten_H*/




