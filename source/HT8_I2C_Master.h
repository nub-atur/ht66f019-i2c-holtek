/**
  ******************************************************************************
  * @file HT8_I2C_Master.h
  * @brief The header file of the I2C Master library.
  * @author Holtek Semiconductor Inc.
  * @version V1.0.0
  * @date 2019-05-10
  ******************************************************************************
  * @attention
  *
  * Firmware Disclaimer Information
  *
  * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
  *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
  *    other intellectual property laws.
  *
  * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
  *    other than HOLTEK and the customer.
  *
  * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
  *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
  *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
  *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
  *
  * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
  ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef _HT8_I2C_Master_h_
#define	_HT8_I2C_Master_h_

#include "HT8_MCU_IP_SEL.h"


/***** I2C SCL select PB6  *****/
#define	SCL			_pb6
#define	SCLC		_pbc6
#define	SCLPU		_pbpu6

/***** I2C SDA select PA3  *****/
#define	SDA			_pa3
#define	SDAC		_pac3
#define	SDAPU		_papu3


#define DatHi()		SDAC=1,SDAPU=1  
#define DatLo()		SDAC=0,SDA=0

#define DATA_NUM			4

#define ACK					0		//ACK
#define NACK				1		//NACK
#define RETRY_TIMES			5		//retry times
#define I2CSP				40		//V3 compiler,system clock 8MHz,I2C speed is 20Kbps,???15

#define	I2CFAIL_CNT			10	
#define	SLAVER_ADDRESS		0XD0	//Slave Address
#define	COMMEND_WORK_ID		0x3B	//command Byte


typedef union
{
	struct
	{      
		u8	ACK_Flag 		:1;
		u8	nc1				:1;
		u8	nc2				:1;
		u8	nc3				:1;
		u8	nc4				:1;
		u8	nc5				:1;
		u8	nc6				:1;
		u8  nc7				:1;
	}Bit;    
	u8 Byte;    
}_I2C_Flag;

extern volatile _I2C_Flag	I2C_Flag;

extern u8 Tx_Buff[DATA_NUM];	//I2C master transmit buff
extern u8 Tx_Data[DATA_NUM];	//I2C master transmit data



void I2C_Master_Init();
void I2C_Start();
void I2C_Stop();
void Wr_Byte(u8 I2CData);
u8 Rd_Byte(void);
void I2C_Write();
void I2C_Read(u8 *prt2,u8 cnt);


#endif

/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/