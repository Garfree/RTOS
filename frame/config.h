/*******************************************************************************
  * @file    config.h
  * @author  garfree
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   
  *****************************************************************************/
#ifndef  __CONFIG_H_ 
#define  __CONFIG_H_

/* for sleep() */
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "type.h"
#include "base.h"


//#define IWDG_En

#define TASK_A 			0
#define IR_RX_IRQ		0x01
#define RF_RX_IRQ		0x02

#define TASK_B 			1
#define UART1_RX_TASK	TASK_B
#define UART1_RX_EVENT	0x01
#define IR_RX_TASK      TASK_B
#define IR_RX_EVENT     0x02
#define RF_RX_TASK      TASK_B
#define RF_RX_EVENT     0x04
#define RF_TEST_TASK    TASK_B
#define TEST_EVENT   	0x08

#define TASK_C      	2
#define RF_TX_EVENT     0x01
#define IR_TX_EVENT     0x02

// void Systerm_Init(void);

#endif
