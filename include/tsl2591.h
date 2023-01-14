/*
 * tsl2591.h
 *
 *  Created on: Feb 25, 2021
 *      Author: Murat Hepeyiler
 *		 Email: murathepeyiler@gmail.com
 */

#ifndef INC_TSL2591_H_
#define INC_TSL2591_H_

#include "tsl2591_param.h"
#include "stdint.h"

/* TODO update for sensor.h */
typedef struct
{
	int (*read8)(void*, uint8_t, uint8_t);
	int (*write8)(void*, uint8_t, uint8_t, uint8_t);
	void (*delay)(uint32_t);
	int (*checkBus)(void*);
	int (*checkSlave)(void*);
	void* device_ptr;

	unsigned int _ch0_val;
	unsigned int _ch1_val;
	unsigned long _delay_time;
	unsigned char sensor_address;
	unsigned char timing_param; /* 1-6 */
	unsigned char gain_param; /* 5 */
} TSL2591_t;

#ifdef __cplusplus
 extern "C" {
#endif

int tsl2591Init(void *sensor_vd);
int tsl2591Check(void *sensor_vd);
int tsl2591ReadAdc(void *sensor_vd);
uint16_t tsl2591GetAdcCh0(const void *sensor_vd);
uint16_t tsl2591GetAdcCh1(const void *sensor_vd);

#ifdef __cplusplus
}
#endif

#endif /* INC_TSL2591_H_ */
