/*******************************************************************************
  * @file    main.c 
  * @author  garfree
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   Main program body
  *****************************************************************************/
  
/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* simulate a CLK source */
void clk_source(void)
{
	/* second */
	sleep(1);

	/* microsecond */
	//usleep(100);
	OSTime();
}


u8 Task_UART(u8 event)
{
	//u8 type;
	//int len, n;
	//u8 buf[300+16];
	//
	if(event&UART1_RX_EVENT)
	{
		printf("this is UART1_RX_EVENT \n");
	}

	//receive IR signal
	if(event&IR_RX_EVENT)   
	{
		printf("this is IR_RX_EVENT  \n");
	}
  
	//receive RF signal
	if(event&RF_RX_EVENT)
	{
		printf("this is RF_RX_EVENT  \n");
	}
	return 0;
}

u8 Task_Send(u8 event)
{
	//RF test
	if(event&TEST_EVENT)
	{
		printf("---------- \n");
	}
	return 0;
}

void Task_1S(void)
{
	static u8 num;
	if(num++ >24)
		num=0;
	printf("num =%d\n",num);
	
	
	switch(num)
	{
	case 1:
		OSSetEvent(TASK_A,IR_RX_IRQ);
		break;
	case 2:
		OSSetEvent(TASK_A,RF_RX_IRQ);
		break;
	case 11:
		OSSetEvent(UART1_RX_TASK,UART1_RX_EVENT);
		break;
	case 12:
		OSSetEvent(IR_RX_TASK,IR_RX_EVENT);
		break;
	case 14:
		OSSetEvent(RF_RX_TASK,RF_RX_EVENT);
		break;
	case 21:
		OSSetEvent(TASK_C,RF_TX_EVENT);
		break;
	default:
		OSSetEvent(TASK_C,TEST_EVENT);
		break;
	}
}

u8 TaskIRQ(u8 event)
{
	if(event&IR_RX_IRQ) 
	{
		printf("this is IR_RX_IRQ  \n");
	}
	if(event&RF_RX_IRQ)
	{
		printf("this is RF_RX_IRQ  \n");
	}
	return 0;
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	//Systerm_Init();
	
	OSTaskInit();
	OSTaskCreate(TASK_A,TaskIRQ);
	OSTaskCreate(TASK_B,Task_UART);
	OSTaskCreate(TASK_C,Task_Send);
	
	OSTimerCreate(Task_1S,1);
	while(1){
		OSTaskRun();
		clk_source();
	}
}

/******************************************* END OF FILE **********************/
