#ifndef _HAL_FAN_H
#define _HAL_FAN_H


#define FAN_ENABLE   1
#define FAN_DISABLE  0
#define FAN_NULL	   0xff	

#define GPIO_FAN_CLK    RCC_APB2Periph_GPIOA
#define GPIO_FAN_PORT   GPIOA
#define GPIO_FAN_PIN    GPIO_Pin_4

void Fan_Init(void);	
void Fan_Ctrl(u8 enable);
void Fan_Proc(bool isAutoMode, bool enable);


#if 0
#define FAN_STOP        0

#define FAN_ARR 899 //8kHZ
#define FAN_MAX 100
#define FAN_MAX1 -100
#define FAN_MIN 0

void Fan_Init(void);
void Fan_status(uint16_t status);
#endif
#endif /*_HAL_Fan_H*/
