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
