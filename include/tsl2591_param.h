/*
 * tsl2591_param.h
 *
 *  Created on: Mar 18, 2020
 *      Author: Murat Hepeyiler
 *		 Email: murathepeyiler@gmail.com
 */

#ifndef INC_TSL2591_PARAM_H_
#define INC_TSL2591_PARAM_H_

#include <stdint.h>

#define I2C_SPEED   100000

enum ADDRESS
{
  SENSOR_ADDRESS        =   (uint8_t)0x29, /* I2C Standard Address */
};

enum REGISTER_ADDRESS
{
	CONTROL_COMMAND     =   (uint8_t)0xA0,  /* bit.7=1 & bit.5=1 */
    ENABLE_REG          =   (uint8_t)0x00,
    CONFIG_REG          =   (uint8_t)0x01,
    AILTL_REG           =   (uint8_t)0x04,
    AILTH_REG           =   (uint8_t)0x05,
    AIHTL_REG           =   (uint8_t)0x06,
    AIHTH_REG           =   (uint8_t)0x07,
    NPAILTL_REG         =   (uint8_t)0x08,
    NPAILTH_REG         =   (uint8_t)0x09,
    NPAIHTL_REG         =   (uint8_t)0x0a,
    NPAIHTH_REG         =   (uint8_t)0x0b,
    PERSIST_REG         =   (uint8_t)0x0c,
    PID_REG             =   (uint8_t)0x11,
    ID_REG              =   (uint8_t)0x12,
    STATUS_REG          =   (uint8_t)0x13,
    C0DATAL_REG         =   (uint8_t)0x14,
    C0DATAH_REG         =   (uint8_t)0x15,
    C1DATAL_REG         =   (uint8_t)0x16,
    C1DATAH_REG         =   (uint8_t)0x17
};

enum ENABLE_REGISTER_FUNC
{
    NPIEN               =   (uint8_t)0x80,
    SAI                 =   (uint8_t)0x40,
    AIEN                =   (uint8_t)0x10,
    AEN                 =   (uint8_t)0x02,
    PON                 =   (uint8_t)0x01,
    POFF                =   (uint8_t)0x00
};

enum CONTROL_REGISTER_FUNC
{
    SRESET              =   (uint8_t)0x80,
    MAX_GAIN            =   (uint8_t)0x30,
    HIGH_GAIN           =   (uint8_t)0x20,
    MED_GAIN            =   (uint8_t)0x10,
    LOW_GAIN            =   (uint8_t)0x00,
    ATIME_100_MS        =   (uint8_t)0x00,
    ATIME_200_MS        =   (uint8_t)0x01,
    ATIME_300_MS        =   (uint8_t)0x02,
    ATIME_400_MS        =   (uint8_t)0x03,
    ATIME_500_MS        =   (uint8_t)0x04,
    ATIME_600_MS        =   (uint8_t)0x05
};

enum PERSIST_REGISTER_FUNC
{
    APERS_EVERY_VAL     =   (uint8_t)0x00,
    APERS_ANY_VAL       =   (uint8_t)0x01,
    APERS_2_VAL         =   (uint8_t)0x02,
    APERS_3_VAL         =   (uint8_t)0x03,
    APERS_5_VAL         =   (uint8_t)0x04,
    APERS_10_VAL        =   (uint8_t)0x05,
    APERS_15_VAL        =   (uint8_t)0x06,
    APERS_20_VAL        =   (uint8_t)0x07,
    APERS_25_VAL        =   (uint8_t)0x08,
    APERS_30_VAL        =   (uint8_t)0x09,
    APERS_35_VAL        =   (uint8_t)0x0a,
    APERS_40_VAL        =   (uint8_t)0x0b,
    APERS_45_VAL        =   (uint8_t)0x0c,
    APERS_50_VAL        =   (uint8_t)0x0d,
    APERS_55_VAL        =   (uint8_t)0x0e,
    APERS_60_VAL        =   (uint8_t)0x0f
};


enum DELAY_TIME
{
	DELAY_TIME_120_MS = 120,
	DELAY_TIME_240_MS = 240,
	DELAY_TIME_360_MS = 360,
	DELAY_TIME_480_MS = 480,
	DELAY_TIME_600_MS = 600,
	DELAY_TIME_720_MS = 720,
};

enum TIMING_PARAM
{
	TIMING_PARAM_120_MS = (uint8_t)0x00,
	TIMING_PARAM_240_MS = (uint8_t)0x01,
	TIMING_PARAM_360_MS = (uint8_t)0x02,
	TIMING_PARAM_480_MS = (uint8_t)0x03,
	TIMING_PARAM_600_MS = (uint8_t)0x04,
	TIMING_PARAM_720_MS = (uint8_t)0x05,
};
#endif /* INC_TSL2591_PARAM_H_ */
