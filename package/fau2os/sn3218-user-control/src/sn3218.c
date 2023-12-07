/* sn3218.c */

#include 		<unistd.h> /* Needed for I2C port */
#include 		 <stdio.h>
#include 		<stdlib.h>
#include 		<string.h>
#include 		<stdint.h>
#include 		 <fcntl.h> /* Needed for I2C port */
#include 	 <sys/ioctl.h> /* Needed for I2C port */
#include <linux/i2c-dev.h> /* Needed for I2C port */
#include 		   "i2c.h"
#include 		"sn3218.h"

uint8_t sn3218_GammaIntencities[SN3218_GAMMA] = {
      0,   1,   2,   4,   6,  10,  13,  18,
     22,  28,  33,  39,  46,  53,  61,  69,
     78,  86,  96, 106, 116, 126, 138, 149, 
	161, 173, 186, 199, 212, 226, 240, 255
};

static uint8_t Buffer[SN3218_NREGS], CountBytes;

static uint8_t sn3218_UpdateRegisters(void);
static uint8_t sn3218_ResetRegisters(void);
static uint8_t sn3218_SetDeviceMode(uint8_t Mode);
static uint8_t sn3218_SetLcr(uint8_t BlkNumber, uint8_t Mode);
static uint8_t sn3218_SetAllLcrs(uint8_t Mode);


int sn3218_OpenDev(void){
	if (I2C_OpenDevice() == -1){
		return SN3218_ERROR;
	};
	if (sn3218_SetDeviceMode(SN3218_NORMAL) == SN3218_ERROR){
		return SN3218_ERROR;
	};
	sn3218_SetAllLcrs(SN3218_LCRON);
	return SN3218_OK;
};

static uint8_t sn3218_SetDeviceMode(uint8_t Mode){
	if (Mode != SN3218_SHUTDOWN && Mode != SN3218_NORMAL){
		return SN3218_ERROR;
	};
	Buffer[0] = SN3218_REG_MODE;
	Buffer[1] = Mode;
	CountBytes = 2;
	if (I2C_WriteToDevice(SN3218_I2C_ADDRESS, Buffer, CountBytes) == CountBytes){
	    return SN3218_OK;
	};
	return SN3218_ERROR;
};

int sn3218_CloseDev(void){
	sn3218_SetDeviceMode(SN3218_SHUTDOWN);
    if (I2C_CloseDevice()){
        return SN3218_ERROR;
	};
	return SN3218_OK;
};

uint8_t sn3218_SetOneLed(uint8_t LedNumber, uint8_t Intensity){
	if (LedNumber < 1 || LedNumber > 18){
		return SN3218_ERROR;
	};
	Buffer[0] = LedNumber;
	Buffer[1] = Intensity;
	CountBytes = 2;
	if (I2C_WriteToDevice(SN3218_I2C_ADDRESS, Buffer, CountBytes) == CountBytes){
        sn3218_UpdateRegisters();
        return SN3218_OK;
    };
	return SN3218_ERROR;
};

uint8_t sn3218_SetAllLeds(uint8_t Intensity){
	Buffer[0] = SN3218_REG_PWM0;
	memset(&Buffer[1], Intensity, SN3218_NLEDS);
	CountBytes = 1 + SN3218_NLEDS;
	if (I2C_WriteToDevice(SN3218_I2C_ADDRESS, Buffer, CountBytes) == CountBytes){
        sn3218_UpdateRegisters();
        return SN3218_OK;
    };
	return SN3218_ERROR;
};

static uint8_t sn3218_UpdateRegisters(void){
	Buffer[0] = SN3218_REG_UPDATE;
	Buffer[1] = 0xFF; /* any value will do here */
	CountBytes = 2;
	if (I2C_WriteToDevice(SN3218_I2C_ADDRESS, Buffer, CountBytes) == CountBytes){
		return SN3218_OK;
	};
    return SN3218_ERROR;
};

static uint8_t sn3218_ResetRegisters(void){
	Buffer[0] = SN3218_REG_RESET;
	Buffer[1] = 0xFF; /* any value will do here */
	CountBytes = 2;
	if (I2C_WriteToDevice(SN3218_I2C_ADDRESS, Buffer, CountBytes) == CountBytes){
		return SN3218_OK;
	};
	return SN3218_ERROR;
};

static uint8_t sn3218_SetLcr(uint8_t BlkNumber, uint8_t Mode){
    if (BlkNumber < 1 || BlkNumber > 3){
        return SN3218_ERROR;
	};
    if (Mode != SN3218_LCRON && Mode != SN3218_LCROFF){
		return SN3218_ERROR;
	};
    Buffer[0] = SN3218_REG_LCR0 + BlkNumber - 1;
	Buffer[1] = Mode;
	CountBytes = 2;
	if (I2C_WriteToDevice(SN3218_I2C_ADDRESS, Buffer, CountBytes) == CountBytes){
		sn3218_UpdateRegisters();
		return SN3218_OK;
	};
	return SN3218_ERROR;
};

static uint8_t sn3218_SetAllLcrs(uint8_t Mode){
    if (Mode != SN3218_LCRON && Mode != SN3218_LCROFF){
		return SN3218_ERROR;
	};
	Buffer[0] = SN3218_REG_LCR0;
	Buffer[1] = Buffer[2] = Buffer[3] = Mode;
	CountBytes = 4;
	if (I2C_WriteToDevice(SN3218_I2C_ADDRESS, Buffer, CountBytes) == CountBytes){
		sn3218_UpdateRegisters();
		return SN3218_OK;
	};
	return SN3218_ERROR;
};
