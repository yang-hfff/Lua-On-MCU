/*************************************************************
 * Copyright (C) 2024-09-27 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
#include "sys.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"


#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io__putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
#endif /*__GNUC__*/


/*避免半主机模式*/
//#pragma import(__use_no_semihosting)             

struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
 
/*加入支持函数*/
void _sys_exit(int x) 
{ 
	x = x; 
} 


//@config<function>
PUTCHAR_PROTOTYPE
{      
	while((USART1->SR&0X40)==0)
    {
        /*...*/
    }
    USART1->DR = (u8) ch;      
	return ch;
}

//@config<function>
time_t time(time_t *timer)
{
    return 0;
}


//@config<function>
void exit(int status)
{
}


//@config<function>
int  system(const char *string)
{
    return 0;
}



