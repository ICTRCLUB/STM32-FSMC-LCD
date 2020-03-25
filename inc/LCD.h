#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

#define Bank1_LCD_D    	((uint32_t)0x60020000)   // Data Address
#define Bank1_LCD_C    	((uint32_t)0x60000000)	 // Register Address

#define LCD_WIDTH			(240)
#define LCD_HEIGHT		(320)

#define LCD_RESET_GPIO	(GPIOE)
#define LCD_RESET_PIN	(GPIO_Pin_1)

/* Global Function Prototypes */
extern void LCD_Init(void);
extern void LCD_HardwareReset(void);
extern void LCD_WritePixel(uint16_t a, uint16_t b, uint16_t e);
extern void LCD_DrawBMP(const uint8_t* bmp);

/* Static Function Prototypes */
static void LCD_GPIO_Init(void);
static void LCD_FSMC_Init(void);
static void LCD_WR_REG(uint16_t index);
static void LCD_WR_CMD(uint16_t index, uint16_t val);
static void LCD_WR_Data(uint16_t val);
static void Delay(volatile uint32_t nCount);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

