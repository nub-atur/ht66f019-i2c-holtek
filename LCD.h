#ifndef _LCD_h_
#define	_LCD_h_

#include "HT8_Type.h"
#include "HT8_I2C_Master.h"

#define LCD_ADDR 0x3F                  //change it!!

void lcdsend(_Bool fgCD, u8 CD);
void lcdinit(void);
void lcdcursor(int row, int col);
void lcdprint(char* ptr);
void lcdprintf(float num);

#endif