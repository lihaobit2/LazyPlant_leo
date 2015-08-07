#ifndef _HAL_PUMP_H
#define _HAL_PUMP_H

#define PUMP_ENABLE   1
#define PUMP_DISABLE  0
#define PUMP_NULL	   0xff	


#define PUMP_THRESHOLD 2000


#define GPIO_PUMP_CLK    RCC_APB2Periph_GPIOB
#define GPIO_PUMP_PORT   GPIOB
#define GPIO_PUMP_PIN    GPIO_Pin_6

void Pump_Init(void);
void Pump_Ctrl(u8 enableFlag);
void Pump_Proc(u16 moistValue, bool isAutoMode, bool pumpSwitch);

#endif


