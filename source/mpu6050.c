#include "mpu6050.h"
#include "HT8_I2C_Master.h"

u8 Rx_Buff[DATA_NUM];	//I2C receive buff
u8 Rx_Data[DATA_NUM];	//I2C receive data
u8 Rd_CheckSum;			//I2C checksum

void I2C_Master_Init();
void I2C_Start();
void I2C_Stop();
void Wr_Byte(u8 I2CData);
void _delay_ms(unsigned long time);
void Check_ACK(void);

void mpu_cmd(u8 RA, u8 data){
	I2C_Start();								//START Condition
	Wr_Byte((MPU6050_ADDRESS << 1)|0);	Check_ACK();
	Wr_Byte(RA); Check_ACK();
	Wr_Byte(data); Check_ACK();
	I2C_Stop();
	_delay_ms(10);
}

void mpu_init(){
	_delay_ms(100);
	mpu_cmd(SMPLRT_DIV,0x07);        // Setting The Sample (Data) Rate
	mpu_cmd(PWR_MGMT_1,0x01);		//setting the clock source
	mpu_cmd(CONFIG,0x00);			// Configure The DLPF (Digital Low Pass Filter)
	mpu_cmd(ACCEL_CONFIG,0x00);		//Configure The Accelerometer
	mpu_cmd(GYRO_CONFIG,0x18);		// config gyros
	mpu_cmd(INT_ENABLE,0x00);		//en INT
	_delay_ms(10);
}

void mpu_read(float AX,float AY,float AZ,float t,float GX,float GY,float GZ){
	 int Ax,Ay,Az,T,Gx,Gy,Gz;
  // Prepare For Reading, Starting From ACCEL_XOUT_H
  I2C_Start();
  Wr_Byte((MPU6050_ADDRESS<<1)|0); Check_ACK();
  Wr_Byte(ACCEL_XOUT_H);	Check_ACK();
  I2C_Stop();
  I2C_Start();
  Wr_Byte((MPU6050_ADDRESS<<1)|1); Check_ACK();
  Ax = ((int)Rd_Byte()<<8) | (int)Rd_Byte();
  Ay = ((int)Rd_Byte()<<8) | (int)Rd_Byte();
  Az = ((int)Rd_Byte()<<8) | (int)Rd_Byte();
  T  = ((int)Rd_Byte()<<8) | (int)Rd_Byte();
  Gx = ((int)Rd_Byte()<<8) | (int)Rd_Byte();
  Gy = ((int)Rd_Byte()<<8) | (int)Rd_Byte();
  Gz = ((int)Rd_Byte()<<8) | (int)Rd_Byte();
  I2C_Stop();
  
  AX = (float)Ax/16384.0;
  AY = (float)Ay/16384.0;
  AZ = (float)Az/16384.0;
  GX = (float)Gx/131.0;
  GY = (float)Gy/131.0;
  GZ = (float)Gz/131.0;
  t = ((float)T/340.00)+36.53;
}

u8 read(void){
	u8 i;
	for (i=0;i<DATA_NUM;i++)
	{
		Rx_Buff[i] = 0;			//clear receive buff
	}
	i = 0;
	I2C_Read(Rx_Buff,sizeof(Rx_Buff)/sizeof(Rx_Buff[0]));  //I2C receive data
	GCC_CLRWDT();	
	Rd_CheckSum = Rx_Buff[0] + Rx_Buff[1] + Rx_Buff[2];			//calculate Rd_CheckSum
	GCC_NOP();
				
	if( (Rd_CheckSum == Rx_Buff[3]))	//Rd_CheckSum is OK
	{
		Rd_CheckSum = 0;
		Rx_Data[0] = Rx_Buff[0];		//
		Rx_Data[1] = Rx_Buff[1];		// 
		Rx_Data[2] = Rx_Buff[2]; 		//
		Rx_Data[3] = Rx_Buff[3];    	//
		for (i=0; i<DATA_NUM; i++)
		{
			Rx_Buff[i] = 0;				//clear receive buff
		}
		GCC_DELAY(1);
	}
	else							//CheckSum error
	{
		GCC_NOP();
					/* user define,such as set a checksum error flag */
	}
	return Rx_Data;
}