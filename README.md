# 移植LUA5.1.5到STM32F103C8T6

![图片待加载](E:\CODE\MCU\STM32\STM32移植Lua\image\logo.gif)

>  上位机串口助手显示（LUA脚本包括表的嵌套、变量访问、条件判断、循环）

![图片待加载](E:\CODE\MCU\STM32\STM32移植Lua\image\result.jpg)

> 不开优化编译结果

![图片待加载](E:\CODE\MCU\STM32\STM32移植Lua\image\O0.jpg)

> 开启2级优化编译结果

![图片待加载](E:\CODE\MCU\STM32\STM32移植Lua\image\O2.jpg)

## 环境与依赖

- 一款RAM大于16KB，ROM大于64KB的单片机（STM32F103C8T6及其以上均满足）
- KEIL（安装了STM32芯片包）
- LUA5.1.5源码
- 下载器或者调试器 

## 详细步骤

1. 去官网[www.lua.org](https://www.lua.org)下载**Lua5.1.5**源码

2. 解压，把里面的**src**目录拷贝到工程，并删除luac.c和lua.c（这俩里面有main函数，这里不需要）

3. 准备一份标准工程，能实现串口打印

4. 把**src**所有C文件加入工程，把**src**加入工程include项

5. 编译，会发现有三个报错（链接时期找不到函数实现导致的）

![图片待加载](E:\CODE\MCU\STM32\STM32移植Lua\image\error.jpg)

6. 在代码中找个地方或新建文件，写重定向代码（可参考附录）

7. 再次编译发现上次错误消失，但是出现内存不足的错误，做如下处理

    - 把**linit.c**里面**lualibs**表中除了**luaopen_base**和**NULL**的其他行注释掉
    - 打开芯片的**.s**启动文件
    - 把里面的**Stack_Size**设为0x00000800(2KB)
    - 把里面的**Heap_Size***设为0x00003400(13KB)

8. 写一个Lua脚本（详情参考附录）

9. 在main.c中编写代码（详情请参考目录）

10. 编译、下载（烧录、调试）、运行

## 测试结果

>参考大小16384(16KB)、65536(64KB)

|    优化情况    | 不优化（-O0） | -O2优化 |
| :------------: | :-----------: | :-----: |
| RAM(SRAM)占用  |   15960Byte   |  15960Byte  |
| ROM(FLASH)占用 |   65512Byte   |  55564Byte  |

**可见RAM占用在18KB以下，ROM占用在64KB以下，而我的测试芯片STM32F103C8T6的SRAM为20KB大小，FLASH为64KB大小。在RAM方面还有足够的余量**

## 附录

> 重定向代码

```c
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
```

> Lua代码

```lua
DEV = {
    id = 'STM32F103C8T6',
    owner = 'JerryYang',
    flash = 20e3,
    sram = 64e3,
    freq = 72e6,
    status = {
        tick = 'OK',
        sram = 'OK',
    },
    periph = {
        'IIC',
        'SPI',
        'UART'
    },
}
print(_VERSION .. '  Copyright (C) 1994-2012 Lua.org, PUC-Rio')
print('------Lua test on variable------')
print('id:\t' .. DEV.id)
print('------Lua test on condition------')
if DEV.owner == 'JerryYang' then
    print('you are legal')
else
    print('you are illegal')
end
print('------Lua test on loop------')
for i = 1, 3 do
    print(i)
end
```

> 主函数示范

```c
#include "sys.h"
#include "systick.h"
#include "usart.h"
#include "logs.h"
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

//Lua脚本
char buff[] = "@@@你的脚本写入这里@@@"

//程序入口
int main(void)
{
    //初始化串口
    uart_init(115200);
    //打开状态机
    lua_State *L = luaL_newstate();
    //打开标准库
    luaL_openlibs(L);
    
    //加载运行
    if (luaL_loadbuffer(L, buff, strlen(buff), "line")|| lua_pcall(L, 0, 0, 0))
    {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    printf("[1]OK\r\n");
    
    //结束
    lua_close(L);
    while(1);
}
```

作者：阳海峰 

BILIBILI昵称：風吹海浪 

邮箱：yang_hfff@qq.com 

致谢遇见的人...

