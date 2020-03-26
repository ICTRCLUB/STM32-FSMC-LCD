#include "stm32f10x_it.h"
#include "LCD.h"

void LCD_Init(void)
{
	LCD_GPIO_Init();
	LCD_FSMC_Init();
	
	LCD_HardwareReset();

	//############# void Power_Set(void) ################//
	LCD_WR_CMD(0x0000,0x0001);
	Delay(10);

	LCD_WR_CMD(0x0015,0x0030);
	LCD_WR_CMD(0x0011,0x0040);
	LCD_WR_CMD(0x0010,0x1628);
	LCD_WR_CMD(0x0012,0x0000);
	LCD_WR_CMD(0x0013,0x104d);
	Delay(10);
	LCD_WR_CMD(0x0012,0x0010);
	Delay(10);
	LCD_WR_CMD(0x0010,0x2620);
	LCD_WR_CMD(0x0013,0x344d); //304d
	Delay(10);

	LCD_WR_CMD(0x0001,0x0100);
	LCD_WR_CMD(0x0002,0x0300);
	LCD_WR_CMD(0x0003,0x1030);
	LCD_WR_CMD(0x0008,0x0604);
	LCD_WR_CMD(0x0009,0x0000);
	LCD_WR_CMD(0x000A,0x0008);

	LCD_WR_CMD(0x0041,0x0002);
	LCD_WR_CMD(0x0060,0x2700);
	LCD_WR_CMD(0x0061,0x0001);
	LCD_WR_CMD(0x0090,0x0182);
	LCD_WR_CMD(0x0093,0x0001);
	LCD_WR_CMD(0x00a3,0x0010);
	Delay(10);

	//################# void Gamma_Set(void) ####################//
	LCD_WR_CMD(0x30,0x0000);		
	LCD_WR_CMD(0x31,0x0502);		
	LCD_WR_CMD(0x32,0x0307);		
	LCD_WR_CMD(0x33,0x0305);		
	LCD_WR_CMD(0x34,0x0004);		
	LCD_WR_CMD(0x35,0x0402);		
	LCD_WR_CMD(0x36,0x0707);		
	LCD_WR_CMD(0x37,0x0503);		
	LCD_WR_CMD(0x38,0x1505);		
	LCD_WR_CMD(0x39,0x1505);
	Delay(10);

	//################## void Display_ON(void) ####################//
	LCD_WR_CMD(0x0007,0x0001);
	Delay(10);
	LCD_WR_CMD(0x0007,0x0021);
	LCD_WR_CMD(0x0007,0x0023);
	Delay(10);
	LCD_WR_CMD(0x0007,0x0033);
	Delay(10);
	LCD_WR_CMD(0x0007,0x0133);
}

static void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* LCD Reset */
	GPIO_InitStructure.GPIO_Pin = LCD_RESET_PIN; 
	GPIO_Init(LCD_RESET_GPIO, &GPIO_InitStructure);  	

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	
	/* D2-D3-RW-RD-D13-D14-D15-D0-D1 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
		  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
		  GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* D4-D5-D6-D7-D8-D9-D10-D11-D12 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
		  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
		  GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 

	/* FSMC NE1 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* FSMC RS */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 

	GPIO_SetBits(GPIOD, GPIO_Pin_7);			// CS
	GPIO_SetBits(GPIOD, GPIO_Pin_14| GPIO_Pin_15 |GPIO_Pin_0 | GPIO_Pin_1);
	GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_ResetBits(GPIOE, GPIO_Pin_0);
	GPIO_ResetBits(LCD_RESET_GPIO, LCD_RESET_PIN);		// RESET
	GPIO_SetBits(GPIOD, GPIO_Pin_4);		   // RD=1
	GPIO_SetBits(GPIOD, GPIO_Pin_5);			// WR=1
}

static void LCD_FSMC_Init(void)
{
	FSMC_NORSRAMInitTypeDef  			FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  	FSMC_NORSRAMTimingInitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime 		= 0x02;
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime 			= 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime 			= 0x05;
	FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration 	= 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision 				= 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency 				= 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode 				= FSMC_AccessMode_B;

	FSMC_NORSRAMInitStructure.FSMC_Bank 						= FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux			= FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType 				= FSMC_MemoryType_NOR;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth 			= FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode 			= FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity 		= FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode 					= FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive 		= FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation 			= FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal 				= FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode 				= FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst 				= FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct 	= &FSMC_NORSRAMTimingInitStructure;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct 		= &FSMC_NORSRAMTimingInitStructure;	  

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 
}

void LCD_HardwareReset(void)
{
	GPIO_ResetBits(LCD_RESET_GPIO, LCD_RESET_PIN);
	Delay(0xAFFFFF);					   
	GPIO_SetBits(LCD_RESET_GPIO, LCD_RESET_PIN );		 	 
	Delay(0xAFFFFF);	
}

static void Delay(volatile uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}

static void LCD_WR_REG(uint16_t index)
{
	*(__IO uint16_t *) (Bank1_LCD_C) = index;
}

static void LCD_WR_CMD(uint16_t index, uint16_t val)
{	
	*(__IO uint16_t *)(Bank1_LCD_C) = index;	
	*(__IO uint16_t *)(Bank1_LCD_D) = val;
}

static void LCD_WR_Data(uint16_t val)
{   
	*(__IO uint16_t *)(Bank1_LCD_D) = val; 	
}

void LCD_WritePixel(uint16_t a, uint16_t b, uint16_t e)    
{
	LCD_WR_CMD(0x20, a);
	LCD_WR_CMD(0x21, b);
	
	LCD_WR_Data(e);
}

void LCD_DrawBMP(const uint8_t* bmp)
{
	uint16_t temp = 0;
	uint32_t n = 0;

	LCD_WR_CMD(0x0003, 0x1018);
	LCD_WR_CMD(0x0050, 0);
	LCD_WR_CMD(0x0051, 239); 	
	LCD_WR_CMD(0x0052, 0); 
	LCD_WR_CMD(0x0053, 319);
	LCD_WR_CMD(32, 0);
	LCD_WR_CMD(33, 0);
	LCD_WR_REG(34);
	
	while(n < 153600)
	{
		temp = (uint16_t)(bmp[n] << 8) + bmp[n+1];		
		LCD_WR_Data(temp);
		n += 2;
	}
}




