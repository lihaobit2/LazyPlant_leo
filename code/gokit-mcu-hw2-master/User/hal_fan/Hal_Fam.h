#ifndef _HAL_FAN_H
#define _HAL_FAN_H

#include <stdio.h>


#define FAN_STOP        0

#define FAN_ARR 899 //8kHZ
#define FAN_MAX 100
#define FAN_MAX1 -100
#define FAN_MIN 0

void Fan_Init(void);
void Fan_status(uint16_t status);

#endif /*_HAL_Fan_H*/



