
#include        <unistd.h> /* Needed for I2C port */
#include         <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <stdint.h>
#include      <sys/file.h>
#include         <fcntl.h> /* Needed for I2C port */
#include     <sys/ioctl.h> /* Needed for I2C port */
#include <linux/i2c-dev.h> /* Needed for I2C port */
#include         <errno.h>
#include           "i2c.h"

#define I2C_DEVICEFILE    "/dev/i2c-0"

int I2C_FileDescriptor;

int I2C_OpenDevice(void){
    errno = 0;
    I2C_FileDescriptor = open(I2C_DEVICEFILE, O_RDWR);
    if (I2C_FileDescriptor < 0){
        return -1;
    };
    errno = 0;
    if (flock(I2C_FileDescriptor, LOCK_EX | LOCK_NB)  == -1){
        close(I2C_FileDescriptor);
        return -1;
    };
    return I2C_FileDescriptor;
}

int I2C_CloseDevice(void){
    errno = 0;
    if (flock(I2C_FileDescriptor, LOCK_UN | LOCK_NB) == -1)
        return -1;
    int Status = close(I2C_FileDescriptor);
    I2C_FileDescriptor = 0;
    return Status;
}

uint8_t I2C_SetAddress(uint8_t Address){
    if (Address == 0){
        return 0;
    };
    if (ioctl(I2C_FileDescriptor, I2C_SLAVE, Address) < 0){
        return 0;
    } else {
        return Address;
    };
};

int I2C_WriteToDevice(uint8_t Address, uint8_t *Buffer, int BytesCount){
    if (I2C_FileDescriptor < 1){
        return 0;
    };
    if (I2C_SetAddress(Address)){
        errno = 0;
        if (write(I2C_FileDescriptor, Buffer, BytesCount) == BytesCount){
            return BytesCount;
        } else {
            return 0;
        };
    } else {
        return 0;
    };
};
