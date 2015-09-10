#ifndef _HAL_EXTR_PUMP_H
#define _HAL_EXTR_PUMP_H

#define EXTR_PUMP_ENABLE   1
#define EXTR_PUMP_DISABLE  0
#define EXTR_PUMP_NULL	   0xff	


#define EXTR_PUMP_THRESHOLD 2000


#define GPIO_EXTR_PUMP_CLK    RCC_APB2Periph_GPIOA
#define GPIO_EXTR_PUMP_PORT   GPIOA
#define GPIO_EXTR_PUMP_PIN    GPIO_Pin_6

extern u8 g_moist_th;

void Extr_Pump_Init(void);
void Extr_Pump_Ctrl(u8 enableFlag);
void Extr_Pump_Proc(u8 moistValue, bool isAutoMode, bool pumpSwitch);
void Extr_Pump_SetMoistTh(u8 moist_th);

#endif


