#include "LCD.h"
#include "stdlib.h"
               
#define NULL ((void *)0)

void _delay_us(unsigned long time){
	unsigned long i; 
	for(i =time; i>0; i--)
	{
		GCC_DELAY(2);
	}
}
   /*One instruction cycle is equal to 4 system clock cycles, therefore in the case of an 8MHz system oscillator, most instructions 
would be implemented within 0.5us and branch or call instructions would be implemented within 1us. 
													===> Gcc_delay() cost us 0.5us   */

void _delay_ms(unsigned long time)
{	u16 i;										//@fSYS=8MH,??del*1ms
	for(i=0;i<time;i++) GCC_DELAY(2000);
}

void I2C_Master_Init();
void I2C_Start();
void I2C_Stop();
void Wr_Byte(u8 I2CData);

void Check_ACK(void)
{	SDAC=1;							     		//SDA ?????
	SCL=1; 							     		//?? SCL=1
	while(SDA);									//?? ACK(Low)
	SCL=0;					   					//?? SCL=0
}

void lcdsend(_Bool fgCD, u8 CD){				//0: command, 1: send character
	volatile u8 tmp,i=1;						//could be change without notice
	I2C_Start();								//START Condition
	Wr_Byte((LCD_ADDR << 1)|0);	Check_ACK();			//Write
	tmp=(fgCD) ? 0x09 : 0x08;					//P3=1,EN=0,RW=0,RS=fgCD	
	tmp|=(CD & 0xF0);					//P3=1,EN=0,RW=0,RS=fgCD								//Get Hi-nibble 
	if((tmp & 0b00110001)== 0x20) i=2; else i = 1;			//If Function Set is Issued
	while(i--)
	{	Wr_Byte(tmp); Check_ACK();				//Write Hi-nibble
		tmp|=(1<<2);							//Set P2(->EN)=1
		Wr_Byte(tmp);	Check_ACK();
		tmp&=(~(1<<2));							//Set P2(->EN)=0
		Wr_Byte(tmp);	Check_ACK();
	}
	tmp&=0x0F;									//Keep Lo-nibble Unchanged
	tmp|=(CD<<4);								//Get Lo-nibble
	Wr_Byte(tmp); Check_ACK();					//Write Lo-nibble
	tmp|=(1<<2);								//Set P2(->EN)=1
	Wr_Byte(tmp);	Check_ACK();							
	tmp&=(~(1<<2));								//Set P2(->EN)=0
	Wr_Byte(tmp); Check_ACK();								
	I2C_Stop();		
}

void lcdinit(void){
	_delay_ms(40);								//LCD Power-On Time
	I2C_Start(); I2C_Stop();
	lcdsend(0,0x28); 							//????:4-Bit, 2-Line, 5*7
	lcdsend(0,0x0F); 							//????:Display/Cursor Blinking On
	lcdsend(0,0x06); 							//????:Increse, Not Shift
	lcdsend(0,0x01); _delay_ms(2);
}

void lcdcursor(int row, int col){
	u8 temp = 0;
	switch (row){
		case 0: 
			temp = 0x80 + 0x00 + (u8)(col);
			break;
		case 1:
			temp = 0x80 + 0x40 + (u8)(col);
			break;
	}
	lcdsend(0, temp);
}

void lcdprint(char* ptr){
	int i = 0;
      while (ptr[i] != '\0') {
         lcdsend(1, ptr[i]);
         i++;
         _delay_us(40);
      }
}

/*char digitToChar(int num) {
	// num must be in 0..9
	return num + '0';
}

void reverse(char* str, int start, int end) {
	while(start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}


char* fl_str (float num)   // float to string 32.434 to "32.434"
{
    //int sizeOfStr = 5;
	//char mystr[r\]="\0";
	char* str;//=(char*) malloc(sizeOfStr + sizeof(char));
	//char 
	//double 
	int integerPart = (int) num;
	float fractionalPart = num - integerPart;
	
	int currentIndex = 0;
	//while (currentIndex<=10){
		while(integerPart > 0) {
			int digit = integerPart % 10;
			str[currentIndex] = digitToChar(digit);
			integerPart /= 10;
			currentIndex++;
		}		
	
		reverse(str, 0, currentIndex - 1);
		str[currentIndex++] = '.';
	
		//int tempBegin = currentIndex;
	
		while(fractionalPart > 0) {
			fractionalPart = fractionalPart * 10;
			int digit = (int) fractionalPart;	
			fractionalPart = fractionalPart - digit;
			str[currentIndex] = digitToChar(digit);
			currentIndex++;
		}
	//}
	
    //printf("tempbegin: %d\n", tempBegin);
	//reverse(str, tempBegin, currentIndex - 1);

    //printf("cur index: %d\n", currentIndex);
	str[currentIndex] = '\0';
	return str;
}*/
