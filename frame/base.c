/*******************************************************************************
  * @file    base.c 
  * @author  garfree
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   basic task scheduler
  *****************************************************************************/

#include "config.h"

const u8 codetab[8]    = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
const u8 codenottab[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

clock_time_t OSClk, OSClkB;

//------------------------------------------
u8 OSTimerCreated;
struct _os_tcb OSTCBTbl[OS_MAX_TASKS]={0};
struct _os_tm_tcb OSTCBTim[OS_MAX_TIMERS]={0};

void OSTaskInit(void)
{
	OSClk = 0;
	OSTimerCreated = 0;

#ifdef IWDG_En
	/* set watch dog */
	IWDG_Enable();
#endif		
}

void delay_ms(clock_time_t ms)
{
	clock_time_t start;
	start = OSClk;
	while((OSClk-start)>ms)
		;
}

s8 OSTimerCreate(void(*task)(void), clock_time_t time)
{
	u8 i,tmp;
	tmp = OSTimerCreated;
	for(i=0;i<OS_MAX_TIMERS;i++)
	{
		if(!(tmp&0x01))
		{
			OSTCBTim[i].interval = time;
			OSTCBTim[i].start = OSClk;
			OSTCBTim[i].task = task;
			OSTimerCreated |= codetab[i];
			return i;
		}
		tmp >>= 1;
	}
	return -1;
}

void OSTaskCreate(u8 tid, u8(*task)(u8))
{
    OSTCBTbl[tid].events = 0;
    OSTCBTbl[tid].task = task;
}

void OSSetEvent(u8 tid, u8 events)
{
  OSTCBTbl[tid].events|=events;
}

u8 OSTaskRun(void)
{
	u8 tk=0;
	u8 i, events;
	for(i=0;i<OS_MAX_TASKS;i++)
	{
		if(OSTCBTbl[i].events)
		{
			//DISABLE_INT();
			events = OSTCBTbl[i].events;
			OSTCBTbl[i].events = 0;
			//ENABLE_INT();
			if(OSTCBTbl[i].task!=NULL)
			{
				events = OSTCBTbl[i].task(events);
				OSTCBTbl[i].events |= events;
			}
			tk=i+1;
			break;		//priority
		}
	}
	if((OSClk!=OSClkB)&&(tk!=1))  
	{
		OSClkB = OSClk;
		for(i=0;i<OS_MAX_TIMERS;i++)
		{
			if(OSTimerCreated&codetab[i])
			{
				if(OSClk - OSTCBTim[i].start >= OSTCBTim[i].interval)
				{
					OSTCBTim[i].start += OSTCBTim[i].interval;
					if(OSTCBTim[i].task!=NULL)
						OSTCBTim[i].task();
				}
			}
		}
#ifdef IWDG_En
		IWDG_ReloadCounter();
#endif
	}
	return tk;
}

