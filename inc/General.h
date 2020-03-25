/*==============================================================================
 *  @file     	General.h - Header File    
 *  @author   	Baran EKREM
 *  @email    	baranekrem@outlook.com
 *  @WebSite   www.baranekrem.net
 *  @compiler 	KEIL ARM MDK 5
 *  @hardware 	STM32F103C8T6
 *  @version  	v1.0
 *  @brief     
==============================================================================*/
#ifndef GENERAL_H
#define GENERAL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
   
#include "stm32f10x_conf.h"

extern void General_Init(void);

static void Clock_Config(void);
static void RCC_Config(void);
static void GPIO_Config(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

