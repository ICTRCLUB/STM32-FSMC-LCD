#include "stm32f10x_it.h"
#include "defines.h"
#include "main.h"
#include "General.h"
#include "LCD.h"
#include "Bitmaps.h"

int main(void)
{  
	/* General System Initialization */
	General_Init();
	
	LCD_Init();
	
	LCD_DrawBMP(bitmap1);
	
	for(;;)
	{
		
	}
}

