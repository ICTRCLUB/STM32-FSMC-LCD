#ifndef DEFINES_H
#define DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef SET_BIT
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#endif

#ifndef CLEAR_BIT
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#endif

#ifndef TOGGLE_BIT
#define TOGGLE_BIT(REG, BIT)  ((REG) ^= (BIT))
#endif

#ifndef READ_BIT
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#endif

#ifndef CLEAR_REG
#define CLEAR_REG(REG)        ((REG) = (0x0))
#endif

#ifndef WRITE_REG
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#endif

#ifndef READ_REG
#define READ_REG(REG)         ((REG))
#endif

#ifndef MODIFY_REG
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#endif

#ifndef IS_BIT_SET
#define IS_BIT_SET(REG, BIT)  (((REG) & (BIT)) != RESET)
#endif

#ifndef IS_BIT_CLR
#define IS_BIT_CLR(REG, BIT)  (((REG) & (BIT)) == RESET)
#endif

#define LED1_PIN							(GPIO_Pin_6)
#define LED1_GPIO							(GPIOC)
#define LED1_On()							(GPIO_SetBits(LED1_GPIO, LED1_PIN))
#define LED1_Off()						(GPIO_ResetBits(LED1_GPIO, LED1_PIN))

#define LED2_PIN							(GPIO_Pin_7)
#define LED2_GPIO							(GPIOC)
#define LED2_On()							(GPIO_SetBits(LED2_GPIO, LED2_PIN))
#define LED2_Off()						(GPIO_ResetBits(LED2_GPIO, LED2_PIN))

#define LED3_PIN							(GPIO_Pin_13)
#define LED3_GPIO							(GPIOD)
#define LED3_On()							(GPIO_SetBits(LED3_GPIO, LED3_PIN))
#define LED3_Off()						(GPIO_ResetBits(LED3_GPIO, LED3_PIN))

#define LED4_PIN							(GPIO_Pin_6)
#define LED4_GPIO							(GPIOD)
#define LED4_On()							(GPIO_SetBits(LED4_GPIO, LED4_PIN))
#define LED4_Off()						(GPIO_ResetBits(LED4_GPIO, LED4_PIN))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32_RDP_H */

