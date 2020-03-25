#include "main.h"
#include "defines.h"
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

