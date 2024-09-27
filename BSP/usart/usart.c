/*************************************************************
 * Copyright (C) 2024-09-27 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
#include "usart.h"
#include "stdarg.h"


/*串口1初始化*/
void uart_init(uint32_t bound)
{
    /*结构体赋初值*/
    USART_InitTypeDef USART_InitStruct = {
        .USART_BaudRate = bound,
        .USART_WordLength =USART_WordLength_8b,
        .USART_StopBits = USART_StopBits_1,
        .USART_Parity = USART_Parity_No,
        .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None
    };
	NVIC_InitTypeDef NVIC_InitStruct = {
        .NVIC_IRQChannel = USART1_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 3,
        .NVIC_IRQChannelSubPriority = 3,
        .NVIC_IRQChannelCmd = ENABLE
    };
	GPIO_InitTypeDef GPIO_InitStruct_TX = {
        .GPIO_Pin = GPIO_Pin_9,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_Mode = GPIO_Mode_AF_PP
    };
	GPIO_InitTypeDef GPIO_InitStruct_RX = {
        .GPIO_Pin = GPIO_Pin_10,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_Mode = GPIO_Mode_IN_FLOATING
    };
	 
    /*使能时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
    
    /*初始化引脚*/
    GPIO_Init(GPIOA, &GPIO_InitStruct_TX);
    GPIO_Init(GPIOA, &GPIO_InitStruct_RX);
	
    /*设置中断优先级*/
    NVIC_Init(&NVIC_InitStruct);	
  
    /*使能串口和相应中断*/
    USART_Init(USART1,&USART_InitStruct); 
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART1,ENABLE);                   
}



/*中断服务函数*/
void USART1_IRQHandler(void)
{
    //uint8_t temp;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        //temp =USART_ReceiveData(USART1);
    }
}



/*发送一个字节*/
static inline void uart_SendByte(USART_TypeDef* USARTx,uint8_t ch)
{
    USART_SendData(USARTx,ch);
    while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET);
}


/*发送字符串*/
static inline void usart_SendStr(USART_TypeDef* USARTx,char *str)
{
    uint16_t k = 0;
    do{
        uart_SendByte(USARTx,str[k++]);
    }while(str[k] != '\0');
    while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
}


/*格式化打印输出*/
int print(const char *format,...)
{
    int ret;
    char String[128];
    va_list arg;
    va_start(arg,format);
    
    ret = vsprintf(String,format,arg);
    
    va_end(arg);
    usart_SendStr(USART1,String);
    
    return ret;
}



/*补充断言*/
void assert_failed(uint8_t* file, uint32_t line)
{
    /*User can add his own implementation to report the file name and line number*/
    print("Wrong parameters value:file %s on line %d\r\n",file,line);
    
    /*Infinite loop*/
    while(1)
    {
    }
}




