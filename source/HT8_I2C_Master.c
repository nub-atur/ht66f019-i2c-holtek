/**
  ******************************************************************************
  * @file HT8_I2C_Master.c
  * @brief This file provides all the I2C Master firmware functions.
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

/* Includes ------------------------------------------------------------------*/


#include "HT8_I2C_Master.h"

volatile _I2C_Flag		I2C_Flag;
u8 Tx_Buff[DATA_NUM];	//I2C transmit buff
u8 Tx_Data[DATA_NUM];	//I2C transmit data

/**
  * @brief I2C master initialization function.
  * @param[in] None.
  * @retval None.
  */
void I2C_Master_Init()
{
	_csel = 0;
	_cos = 1;
	SCL  = 1;
	SDA  = 1;	
	SCLC = 0;
	SDAC = 0;
	SCLPU = 1;
	SDAPU = 1;
	I2C_Flag.Byte = 0x00;
}


/**
  * @brief I2C Start function.
  * @param[in] None.
  * @retval None.
  */
//I2C Start signal,when SCL is high，SDA changes from high to low(falling edge) 
void I2C_Start()
{
	DatHi();	GCC_DELAY(I2CSP);	//V3 compiler,system clock 8MHz,I2C speed is about 20Kbps
	SCL = 1;	GCC_DELAY(I2CSP);
	DatLo();	GCC_DELAY(I2CSP);
	SCL = 0;	GCC_DELAY(I2CSP);
	GCC_NOP();
}//end of I2C_Start()


/**
  * @brief I2C Stop function.
  * @param[in] None.
  * @retval None.
  */
//I2C Stop signal,when SCL is high，SDA changes from low to high(rising edge) 
void I2C_Stop()    //
{
//	SCL = 0;
	DatLo();	GCC_DELAY(I2CSP);
	SCL = 1;	GCC_DELAY(I2CSP);
	DatHi();	GCC_DELAY(I2CSP);
}//end of I2C_Stop()


/**
  * @brief I2C write byte function.
  * @param[in] The data that you want to write.
  * @retval None.
  */
void Wr_Byte(u8 I2CData)
{
	u8 temp = 0b10000000;
	SCL = 0;
	do
	{
		if(I2CData & temp)
			DatHi();
		else
			DatLo();
			
		GCC_DELAY(I2CSP/2);
		SCL = 1;	GCC_DELAY(I2CSP);  
		SCL = 0;	GCC_DELAY(I2CSP/2);
		temp >>= 1;	
	}while(temp != 0);
	GCC_NOP();
}


/**
  * @brief I2C read data(one byte) function.
  * @param[in] None.
  * @retval The data read from I2C bus.
  */
u8 Rd_Byte(void)
{
	u8 I2CData = 0,temp = 0b10000000;
	SDAC = 1;
	do
	{
		SCL = 1;	GCC_DELAY(I2CSP);
		if (1 == SDA)	
			I2CData |= temp;
		SCL = 0;	GCC_DELAY(I2CSP);
		temp >>= 1;
	}while(temp != 0);
	return I2CData;
}//end of Rd_Byte()


/**
  * @brief Check slave ACK function.
  * @param[in] None.
  * @retval The status that slaver ACK.
  * 1:ACK, 0:No ACK.
  */
_Bool CheckACK()
{
	u8 CheckCnt = 20;			//check times counter
	_Bool I2C_ACK_Flag = 0;
	while(CheckCnt--)
	{
		SDAC = 1;	GCC_DELAY(I2CSP);
		SCL = 1;	GCC_DELAY(I2CSP);
		if(!SDA)
		{
			I2C_ACK_Flag = ACK;	//SDA = 0,slave respond ACK
			break;
		}
		I2C_ACK_Flag = NACK;	//SDA = 1,slave not respond or respond NACK,check again
		GCC_DELAY(I2CSP);	
	}
	SCL = 0;
	GCC_DELAY(I2CSP);
	return I2C_ACK_Flag;
}//end of CheckACK()


/**
  * @brief I2C transmit data function.
  * @param[in] None.
  * @retval None.
  */
void I2C_Write()
{
	u8 Wr_CheckSum = 0,CheckAddressCnt = RETRY_TIMES;
	I2C_Flag.Bit.ACK_Flag = 0;

	//--- write data ---
	while( CheckAddressCnt > 0 )
	{
		I2C_Start();						//general I2C start signal
		Wr_Byte(SLAVER_ADDRESS|0);			//transmit slave address and write command
		if(CheckACK() == ACK)				//slave respond ACK
		{
			GCC_DELAY(200);
			I2C_Flag.Bit.ACK_Flag = 0;
			
			Wr_Byte(COMMEND_WORK_ID);			//send header code 0x11
			I2C_Flag.Bit.ACK_Flag = CheckACK();	//waiting ACK
			GCC_DELAY(200);
			if (I2C_Flag.Bit.ACK_Flag == ACK)	
			{
				I2C_Flag.Bit.ACK_Flag = 0;
				Wr_Byte(Tx_Buff[0]);				//send byte1
				I2C_Flag.Bit.ACK_Flag = CheckACK();	//waiting ACK
				GCC_DELAY(200);
				
				if (I2C_Flag.Bit.ACK_Flag == ACK)
				{	
					I2C_Flag.Bit.ACK_Flag = 0;
					Wr_Byte(Tx_Buff[1]);				//send byte2
					I2C_Flag.Bit.ACK_Flag = CheckACK();	//waiting ACK	
					GCC_DELAY(200);
					
					if (I2C_Flag.Bit.ACK_Flag == ACK)
					{
						I2C_Flag.Bit.ACK_Flag = 0;
						Wr_Byte(Tx_Buff[2]);				//send byte3
						I2C_Flag.Bit.ACK_Flag = CheckACK();	//waiting ACK
						GCC_DELAY(200);	
									
						if (I2C_Flag.Bit.ACK_Flag == ACK)
						{
							Wr_CheckSum = (u8)(Tx_Buff[0] + Tx_Buff[1] + Tx_Buff[2]);
							Wr_Byte(Wr_CheckSum);				//send CheckSum
							I2C_Flag.Bit.ACK_Flag = CheckACK();	//waiting ACK		
							break;
						}
						else
						{
						/* slave not respond or respond NACK,stop transmit 
						   data,user can set error flag in here */							
							I2C_Stop();
							GCC_DELAY(10);
							return;
						}
					}
					else
					{
					/* slave not respond or respond NACK,stop transmit 
					   data,user can set error flag in here */						
						I2C_Stop();
						GCC_DELAY(10);
						return;
					}
				}
				else
				{
				/* slave not respond or respond NACK,stop transmit 
				   data,user can set error flag in here */					
					I2C_Stop();
					GCC_DELAY(10);
					return;
				}
			}
			else
			{
			/* slave not respond or respond NACK,stop transmit 
			   data,user can set error flag in here */
				I2C_Stop();		
				GCC_DELAY(10);
				return;
			}
		}
		else			//slave not respond or respond NACK,check again
		{
			I2C_Stop();
			GCC_DELAY(200);
			CheckAddressCnt--;
		}
	}
	I2C_Stop();
	GCC_DELAY(10);
}


/**
  * @brief I2C read data function.
  * @param[in] read data buff.
  * @param[in] read data number.
  * @retval None.
  */
void I2C_Read(u8 *prt2,u8 cnt )
{
	volatile u8 i,CheckAddressCnt = 0;
	
	//------- read data --------
	for (CheckAddressCnt = 0; CheckAddressCnt < 5; CheckAddressCnt++)
	{
		I2C_Start();			
		Wr_Byte(SLAVER_ADDRESS|0);		//send slave address and write command  
		if(NACK == CheckACK())			//check ACK,slave not respond,check again
		{	
			I2C_Stop();
			GCC_DELAY(200);
			CheckAddressCnt--;
			/* user define，such as set a NACK error flag */
		}
		else							//slave respond ACK
		{
			/* if you set NACK error flag,you need clear flag */
			break;						
		}
	}
	Wr_Byte(COMMEND_WORK_ID);			//send header code
	I2C_Flag.Bit.ACK_Flag = CheckACK();	
			
	I2C_Start();	
	Wr_Byte(SLAVER_ADDRESS|1);			//send slave address and read command  
	if(NACK == CheckACK())					//check ACK
	{
		I2C_Stop();
		GCC_DELAY(200);
	}
	else
	{
		for(i = 0 ; i < cnt ; i++)		//read data
		{
			*(prt2 + i) = Rd_Byte();	//receive one byte from slave
			SDAC = 0;					//receive not finished,respond ACK
			if(i >= (cnt - 1))			//receive last one byte and respond NACK
				SDA = 1;
			else
				SDA = 0;		
			SDAC = 0;	GCC_DELAY(I2CSP);
			SCL = 1; 	GCC_DELAY(I2CSP);
			SCL = 0;	GCC_DELAY(I2CSP);
		}
		I2C_Stop();						//release I2C BUS	
	}
	//------- end of receive data --------
}

/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/