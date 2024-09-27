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

//Ҫ�鿴�������ڹ���ctrl+F����//@config����
//�����ļ��� Stack_Size = 0x00000800(2KB)
//�����ļ��� Heap_Size = 0x00003400(13KB)
//���Ż�(-O0)
//������Program Size: Code=62328 RO-data=2584 RW-data=600 ZI-data=15360  
//SRAM_Cost = 15960 < 16384(16KB)
//FLASH_Cost = 65512 < 65536(64KB)
//������������

//Lua�ű�
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

//�û����
int main(void)
{
    //��ʼ������
    uart_init(115200);
    //��״̬��
    lua_State *L = luaL_newstate();
    //�򿪱�׼��
    luaL_openlibs(L);
    
    //��������
    if (luaL_loadbuffer(L, buff, strlen(buff), "line")|| lua_pcall(L, 0, 0, 0))
    {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    printf("[1]OK\r\n");
    
    //����
    lua_close(L);
    while(1);
}


