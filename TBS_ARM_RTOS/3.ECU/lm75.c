#include <stdint.h>
#include <lpc11xx.h>
#include <clocks.h>
#include <i2c.h>
#include <lm75.h>

uint8_t i2c_status;
uint32_t ReadLM75(void)
{
 

 uint8_t lm75_temp[2];
 uint32_t lm75_data;
 // uint32_t lm75_measured;


 /***** START Phase Starts ***********/
 // Issue start command
 Set_I2C_Master_Command(ISSUE_START);

 // Wait for the Status Update
 while(!GetI2CStatus());

 // Read the Status Code
 i2c_status = Get_I2C_Status_Code();

 // Clear START
 Set_I2C_Master_Command(CLEAR_START);

 // Clear I2C Status
 Clear_I2C_Status();
 /***** START Phase Ends ***********/

 /***** SLAW Phase Starts ***********/
 // Initiate SLAW
 Write_I2C_Byte(0x90); // LM75 SlaveID = 0x90

 // Wait for the Status Update
 while(!GetI2CStatus());

 // Read the Status Code
 i2c_status = Get_I2C_Status_Code();

 // Clear I2C Status
 Clear_I2C_Status();
 /***** SLAW Phase Ends ***********/

 /*** Master Write Byte Phase Starts ***/
 // Select the Slave Internal Register
 Write_I2C_Byte(0x00); // LM75 Temperature Register

 // Wait for the Status Update
 while(!GetI2CStatus());

 // Read the Status Code
 i2c_status = Get_I2C_Status_Code();

 // Clear I2C Status
 Clear_I2C_Status();
 /***** Master Write Byte Phase Ends ***********/

 /***** RESTART Phase Starts ***********/
 // Issue start command
 Set_I2C_Master_Command(ISSUE_START);

 // Wait for the Status Update
 while(!GetI2CStatus());

 // Read the Status Code
 i2c_status = Get_I2C_Status_Code();

 // Clear START
 Set_I2C_Master_Command(CLEAR_START);

 // Clear I2C Status
 Clear_I2C_Status();
 /***** RESTART Phase Ends ***********/

 /***** SLAR Phase Starts ***********/
 // Initiate SLAR
 Write_I2C_Byte(0x91); // LM75 SlaveID = 0x90

 // Wait for the Status Update
 while(!GetI2CStatus());

 // Read the Status Code
 i2c_status = Get_I2C_Status_Code();

 // Clear I2C Status
 Clear_I2C_Status();
 /***** SLAR Phase Ends ***********/

/*** Master Read Bytes Phase Starts ****/
 // Assert Master ACK to receive the first byte
 Set_I2C_Master_Ack(MASTER_ACK);

 // Wait for the Status Update
 while(!GetI2CStatus());

 // Read the Status Code
 i2c_status = Get_I2C_Status_Code();

 // Read the first Byte from the slave
 lm75_temp[0] = Read_I2C_Byte(); // MSB Byte

 // Clear I2C Status
 Clear_I2C_Status();

 // Assert Master NACK to receive the Last byte
 Set_I2C_Master_Ack(MASTER_NACK);

 // Wait for the Status Update
 while(!GetI2CStatus());

 // Read the Status Code
 i2c_status = Get_I2C_Status_Code();

 // Read the Last Byte from the slave
 lm75_temp[1] = Read_I2C_Byte();

 // Clear I2C Status
 Clear_I2C_Status();
 /*** Master Read Bytes Phase Ends ****/

 // Issue STOP
 Set_I2C_Master_Command(ISSUE_STOP);

 lm75_data = (lm75_temp[0]<<8) | (lm75_temp[1]);

 // lm75_measured = lm75_data/256;

 return (lm75_data >> 5)*125/1000;
}

