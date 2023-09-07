#include "HT66F019.h"
#include "LCD.h"
#include "mpu6050.h"
#include "HT8_it.h"


void I2C_Master_Init();
void _delay_ms(unsigned long time);

void main()
{
	
	u8 z[14];
	char text[]= "TaiwanChip gg ez";
	char text2[] = " t = ";
	//_wdtc=0b10101111;
	//EXIT_Init(
	_wdtc=0b10101111;
	I2C_Master_Init();
	//INT0_CLEAR_FLAG();		//clear external interrupt 0 flag
	//INT0_ISR_ENABLE();		//enable external interrupt 0
	//I2C_Master_Init();
	//lcdinit();
	//lcdcursor(0,0);
	//lcdsend(1,'a');
	lcdinit();
	mpu_init();
	while(1){
		//mpu_read(AX, AY, AZ, t, GX, GY, GZ);
		//while(_pa2){	
		_delay_ms(200);
		lcdcursor(1,0);
		lcdprint(text2);
		I2C_Read(z, 13);
		//lcdprintf(/16384);
		//lcdprintf(z);
		_delay_ms(2000);
		//	_pac2 = 0;_pa2 = 0;
		//}				
	//}
	//SysClockDivision_Init();
		lcdcursor(0,0);
		lcdprint(text);
		_delay_ms(1000);	
	//lcdsend(0,0x01); _delay_ms(2);		//??LCM???????	
	//lcdcursor(1,0);						
		//lcdsend(0,0x04);						//????:Decrease, Not Shift 
		//lcdsend(0,0xCF);						//Set Line 2, Position 0 
 		//??"2"????????2?0
	}
}