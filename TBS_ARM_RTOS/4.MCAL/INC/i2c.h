#ifndef __I2C_H__
#define __I2C_H__

typedef enum
{
	MASTER_ACK,
	MASTER_NACK
}i2c_master_ack_t;	

typedef enum
{
	ISSUE_START,
	CLEAR_START,
	ISSUE_STOP
}i2c_master_cmd_t;	


typedef enum
{
	ENABLE_I2C,
	DISABLE_I2C
}i2c_en_t;	


void Set_I2C_Master_Command(i2c_master_cmd_t cmd);
void Write_I2C_Byte(uint8_t data_byte);
uint8_t Read_I2C_Byte(void);
void Set_I2C_Master_Ack(i2c_master_ack_t option);
void Wait_I2C_Phase_Complete(void);
uint8_t Get_I2C_Status_Code(void);
uint8_t GetI2CStatus(void);
void Clear_I2C_Status(void);
void Set_I2C_Interface(i2c_en_t option);
void Init_I2C(void);


#endif
