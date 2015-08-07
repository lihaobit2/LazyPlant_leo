#ifndef _HAL_EXTR_PUMP_H
#define _HAL_EXTR_PUMP_H

#define EXTR_PUMP_ENABLE   1
#define EXTR_PUMP_DISABLE  0
#define EXTR_PUMP_NULL	   0xff	


#define EXTR_PUMP_THRESHOLD 2000


#define GPIO_EXTR_PUMP_CLK    RCC_APB2Periph_GPIOA
#define GPIO_EXTR_PUMP_PORT   GPIOA
#define GPIO_EXTR_PUMP_PIN    GPIO_Pin_6

void Extr_Pump_Init(void);
void Extr_Pump_Ctrl(u8 enableFlag);
void Extr_Pump_Proc(bool isAutoMode, bool pumpSwitch);

#endif


