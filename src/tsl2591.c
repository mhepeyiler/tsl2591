/*
 * tsl2591.c
 *
 *  Created on: Feb 25, 2021
 *      Author: Murat Hepeyiler
 *		 Email: murathepeyiler@gmail.com
 * Description:	TSL2591 functionality implementation. The struct has been declared in .h file.
 */

#include <error_type.h>
#include "tsl2591.h"

#ifdef __cplusplus
 extern "C" {
#endif

int enable(const TSL2591_t*);
int disable(const TSL2591_t*);

#ifdef __cplusplus
}
#endif


 /**
  * Initial configuration of sensor
  *
  * @param sensor it a pointer of configured struct TSL2591_t data type pointer
  * @return 	0 if success,
  * 			if I2C bus has an error, returns -1
  * 			if I2C device_ptr is not ready, return -2
  */
int tsl2591Init(void *sensor_vd) {

	TSL2591_t *sensor = (TSL2591_t*)sensor_vd;
	/* UNUSED VARIABLES */
	uint8_t ailtl_param = 0x00; /* ALS interrupt low threshold low byte */
	uint8_t ailth_param = 0x00; /* ALS interrupt low threshold high byte */
	uint8_t aihtl_param = 0x00; /* ALS interrupt high threshold low byte */
	uint8_t aihth_param = 0x00; /* ALS interrupt high threshold high byte */
	uint8_t npailtl_param = 0x00; /* No Persist ALS interrupt low threshold low byte */
	uint8_t npailth_param = 0x00; /* No Persist ALS interrupt low threshold high byte */
	uint8_t npaihtl_param = 0x00; /* No Persist ALS interrupt high threshold low byte */
	uint8_t npaihth_param = 0x00; /* No Persist ALS interrupt high threshold high byte */
	uint8_t persist_param = 0x00; /* Interrupt persistence filter */
	uint8_t control_reg_param = sensor->gain_param | sensor->timing_param;

	int error = 0;
	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, (CONTROL_COMMAND | CONFIG_REG), control_reg_param);
	if(error != I2C_OK)
		return (error);

	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, CONTROL_COMMAND | AILTL_REG, ailtl_param);
	if(error != I2C_OK)
		return (error);

	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, CONTROL_COMMAND | AILTH_REG, ailth_param);
	if(error != I2C_OK)
		return (error);

	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, CONTROL_COMMAND | AIHTL_REG, aihtl_param);
	if(error != I2C_OK)
		return (error);

	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, CONTROL_COMMAND | AIHTH_REG, aihth_param);
	if(error != I2C_OK)
		return (error);

	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, CONTROL_COMMAND | NPAILTL_REG, npailtl_param);
	if(error != I2C_OK)
		return (error);

	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, CONTROL_COMMAND | NPAILTH_REG, npailth_param);
	if(error != I2C_OK)
		return (error);

	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, CONTROL_COMMAND | NPAIHTL_REG, npaihtl_param);
	if(error != I2C_OK)
		return (error);

	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, CONTROL_COMMAND | NPAIHTH_REG, npaihth_param);
	if(error != I2C_OK)
		return (error);

	error = sensor->write8(sensor->device_ptr, sensor->sensor_address, CONTROL_COMMAND | PERSIST_REG, persist_param);
	if(error != I2C_OK)
		return (error);

	switch (sensor->timing_param) {
	case TIMING_PARAM_120_MS:
		sensor->_delay_time = DELAY_TIME_120_MS;
		break;

	case TIMING_PARAM_240_MS:
		sensor->_delay_time = DELAY_TIME_240_MS;
		break;

	case TIMING_PARAM_360_MS:
		sensor->_delay_time = DELAY_TIME_360_MS;
		break;

	case TIMING_PARAM_480_MS:
		sensor->_delay_time = DELAY_TIME_480_MS;
		break;

	case TIMING_PARAM_600_MS:
		sensor->_delay_time = DELAY_TIME_600_MS;
		break;

	case TIMING_PARAM_720_MS:
		sensor->_delay_time = DELAY_TIME_720_MS;
		break;

	default:
		break;
	}
	return (I2C_OK);
}

/**
 * Check the sensor is okay
 *
 * @param sensor it a pointer of configurated struct TSL2591_t data type pointer
 * @return 	SENSOR_OK if success,
 * 			return erros if it is fails
 */

int tsl2591Check(void *sensor_vd)
{
	TSL2591_t *sensor = (TSL2591_t*)sensor_vd;

	int error = 0;
	error = sensor->read8(sensor->device_ptr,  sensor->sensor_address, (CONTROL_COMMAND | ID_REG));
	if(error == I2C_STATE_NOT_READY || error == I2C_DEVICE_NOT_READY || error == I2C_OPERATION_NOT_COMPLETED)
		return (error);

	return SENSOR_OK;
}


/**
 * Enables the read functionality of sensor, it is implemented to use internal
 *
 * @param sensor it a pointer of configurated struct TSL2591_t data type pointer
 * @return 	0 if success,
 * 			if I2C bus has an error, returns -1
 * 			if I2C device_ptr is not ready, return -2
 */
int enable(const TSL2591_t *sensor) {
	int error = sensor->write8(sensor->device_ptr, sensor->sensor_address, (CONTROL_COMMAND | ENABLE_REG),
			(PON | AEN | AIEN | NPIEN));
	return (error);
}

/**
 * Disables the read functionality of sensor, it is implemented to use internal
 *
 * @param sensor it a pointer of configured struct TSL2591_t data type pointer
 * @return 	0 if success,
 * 			if I2C bus has an error, returns -1
 * 			if I2C device_ptr is not ready, return -2
 */
int disable(const TSL2591_t *sensor) {
	int error = sensor->write8(sensor->device_ptr, sensor->sensor_address, (CONTROL_COMMAND | ENABLE_REG), POFF);
	return (error);
}

/**
 * Read function of the sensor, calculate high and low value writes to struct _ch0_val and _ch1_val
 *
 * @param sensor it a pointer of configured struct TSL2591_t data type pointer
 * @return 	0 if success,
 * 			if I2C bus has an error, returns -1
 * 			if I2C device_ptr is not ready, return -2
 */
int tsl2591ReadAdc(void *sensor_vd) {
	TSL2591_t* sensor = (TSL2591_t*)sensor_vd;

	int error = enable(sensor);
	if(error != I2C_OK)
		return (error);

	sensor->delay(sensor->_delay_time);

	/* CH0 Read */
	error = sensor->read8(sensor->device_ptr, sensor->sensor_address, (CONTROL_COMMAND | C0DATAL_REG));
	if(error == I2C_STATE_NOT_READY || error == I2C_DEVICE_NOT_READY || error == I2C_OPERATION_NOT_COMPLETED)
		return (error);
	uint8_t low = error;

	error = sensor->read8(sensor->device_ptr, sensor->sensor_address, (CONTROL_COMMAND | C0DATAH_REG));
	if(error == I2C_STATE_NOT_READY || error == I2C_DEVICE_NOT_READY || error == I2C_OPERATION_NOT_COMPLETED)
		return (error);
	uint8_t high = error;

	sensor->_ch0_val = (high << 8) | low;

	/* CH1 Read */
	error = sensor->read8(sensor->device_ptr, sensor->sensor_address, (CONTROL_COMMAND | C1DATAL_REG));
	if(error == I2C_STATE_NOT_READY || error == I2C_DEVICE_NOT_READY || error == I2C_OPERATION_NOT_COMPLETED)
		return (error);
	low = error;

	error = sensor->read8(sensor->device_ptr, sensor->sensor_address, (CONTROL_COMMAND | C1DATAH_REG));
	if(error == I2C_STATE_NOT_READY || error == I2C_DEVICE_NOT_READY || error == I2C_OPERATION_NOT_COMPLETED)
		return (error);
	high = error;

	sensor->_ch1_val = (high << 8) | low;

	error = disable(sensor);
	if(error == I2C_STATE_NOT_READY || error == I2C_DEVICE_NOT_READY || error == I2C_OPERATION_NOT_COMPLETED)
		return (error);
	return (0);
}

/**
 * Getter function of Channel 0
 *
 * @param sensor it a pointer of configured struct TSL2591_t data type pointer
 * @return 	Channel 0 value
 */
uint16_t tsl2591GetAdcCh0(const void *sensor_vd) {
	TSL2591_t *sensor = (TSL2591_t*)sensor_vd;
	return (sensor->_ch0_val);
}

/**
 * Getter function of Channel 1
 *
 * @param sensor it a pointer of configured struct TSL2591_t data type pointer
 * @return 	Channel 1 value
 */
uint16_t tsl2591GetAdcCh1(const void *sensor_vd) {
	TSL2591_t *sensor = (TSL2591_t*)sensor_vd;
	return (sensor->_ch1_val);
}
