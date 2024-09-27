/*************************************************************
 * Copyright (C) 2024-09-27 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
#include "systick.h"


/*微秒延时*/
void systick_delay_us(__IO uint32_t us)
{
    uint32_t i;
    
    SysTick_Config(SystemCoreClock/1000000);
    
    for(i = 0;i < us;i++)
    {
        while(!((SysTick->CTRL)&(1<<16)));
    }
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}




/*毫秒延时*/
void systick_delay_ms(__IO uint32_t ms)
{
    uint32_t i;
    
    SysTick_Config(SystemCoreClock/1000);
    
    for(i = 0;i < ms;i++)
    {
        while(!((SysTick->CTRL)&(1<<16)));
    }
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    
}



/*中断服务函数*/
void SysTick_Handler(void)
{
    /*...*/
}


