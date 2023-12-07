
extern int I2C_FileDescriptor;

int I2C_OpenDevice(void);
int I2C_CloseDevice(void);
uint8_t I2C_SetAddress(uint8_t Address);
int I2C_WriteToDevice(uint8_t Address, uint8_t *Buffer, int BytesCount);

