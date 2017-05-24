#ifndef __BASE_H__
#define __BASE_H__

//---------------------------------
#define PT_STATE_INIT     0x80		//
#define PT_STATE_WAITING  0x40		//
#define PT_STATE_ENDED    0x00		//

//PT task
struct pt {
  u16 line;
};

#define PT_INIT(pt)         (pt)->line = 0
#define PT_START(pt,flag)   if(flag&PT_STATE_INIT) PT_INIT(pt)
#define PT_BEGIN(pt)        switch((pt)->line) { case 0:
#define PT_END(pt)          };PT_INIT(pt); return PT_STATE_ENDED
#define PT_SET(pt)          (pt)->line = __LINE__; case __LINE__:
	
#define PT_WAIT_UNTIL(pt, condition)	 PT_SET(pt) if(!(condition)) return PT_STATE_WAITING
#define PT_WAIT_WHILE(pt, cond)  PT_WAIT_UNTIL((pt), !(cond))

//PT timer
#define clock_time_t u32
extern clock_time_t OSClk;
struct _timer{
	clock_time_t start;
	clock_time_t interval;
};

#define OSTime()	OSClk++
#define PT_TIME_SET(t,timer) (t)->interval = timer;(t)->start = OSClk
#define PT_TIME_RESET(t) (t)->start += (t)->interval
#define PT_TIME_RESTART(t) (t)->start = OSClk
#define PT_TIME_EXPIRED(t) (OSClk - (t)->start) >= (t)->interval	

//suspend
#define PT_WAIT_TIME(pt,t,time)   PT_TIME_SET(t,time);PT_WAIT_WHILE(pt, PT_TIME_EXPIRED(t))

//semaphore
#define PT_SEM_INIT(s, c) (s)->count = c

#define PT_SEM_WAIT(pt,s,timeout)	\
  do {						\
  	(s)->interval = timeout;                  \
  	(s)->start = OSClk + timeout;                     \
    PT_WAIT_WHILE(pt, ((s)->count==0)&&(PT_TIME_EXPIRED(t)));		\
    if((s)->count)--(s)->count;				\
  } while(0)
  
#define PT_SEM_SIGNAL(pt, s) ++(s)->count


#define OS_MAX_TASKS    4
struct _os_tcb {
	u8 events;				//event
	u8 (*task)(u8 events);	//task function
};

#define OS_MAX_TIMERS    4
struct _os_tm_tcb {
	clock_time_t start;
	clock_time_t interval;
	void (*task)(void);	//timer function
};

//---------------------------------
//#define DISABLE_INT() __asm("CPSID  I")   
//#define ENABLE_INT()	__asm("CPSIE  I")   


//bit 
extern  const u8 codetab[];
extern  const u8 codenottab[];

//--------------------------------
void OSTaskInit(void);
void OSTaskCreate(u8 tid, u8(*task)(u8));
void OSSetEvent(u8 tid, u8 events);
s8 OSTimerCreate(void(*task)(void), clock_time_t time);
u8 OSTaskRun(void);

void delay_ms(clock_time_t ms);

#endif
