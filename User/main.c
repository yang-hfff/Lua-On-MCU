/*************************************************************
 * Copyright (C) 2024-09-27 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
#include "sys.h"
#include "systick.h"
#include "usart.h"
#include "logs.h"
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

//要查看配置请在工程ctrl+F输入//@config查找
//启动文件中 Stack_Size = 0x00000800(2KB)
//启动文件中 Heap_Size = 0x00003400(13KB)
//关优化(-O0)
//编译结果Program Size: Code=62328 RO-data=2584 RW-data=600 ZI-data=15360  
//SRAM_Cost = 15960 < 16384(16KB)
//FLASH_Cost = 65512 < 65536(64KB)
//程序运行正常

//Lua脚本
char buff[] = "\
DEV = {\
    id = 'STM32F103C8T6',\
    owner = 'JerryYang',\
    flash=20e3,\
    sram=64e3,\
    freq = 72e6,\
    status = {\
        tick = 'OK',\
        sram = 'OK',\
    },\
    periph = {\
        'IIC',\
        'SPI',\
        'UART'\
    },\
}\
print(_VERSION..'  Copyright (C) 1994-2012 Lua.org, PUC-Rio')\
print('------Lua test on variable------')\
print('id:\t'..DEV.id)\
print('------Lua test on condition------')\
if DEV.owner == 'JerryYang' then\
    print('you are legal')\
else\
    print('you are illegal')\
end \
print('------Lua test on loop------')\
for i = 1, 3 do\
    print(i)\
end\
";

//用户入口
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


