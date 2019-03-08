/*
Example for FRAM Click

    Date          : jan 2018.
    Author        : MikroE Team

Test configuration PIC :
    
    MCU             : P18F87K22
    Dev. Board      : EasyPIC PRO v7
    PIC Compiler ver : v7.1.0.0

---
Description :

The application is composed of three sections :

- System Initialization - GPIO and SPI module Initalization 
- Application Initialization -Fram Driver Initialization, initialization of click by setting mikorBUS pins to
  approprieate logic level, performing erase all and write enable functions. 
- Application Task - Writing data to click memory and displaying the read data via UART. 

*/

#include "Click_FRAM_types.h"
#include "Click_FRAM_config.h"

 

char wrData [10] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
char rdData [10];

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_PWM_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_spiInit( _MIKROBUS1, &_FRAM_SPI_CFG[0] );
    mikrobus_logInit( _MIKROBUS2, 9600 );

    Delay_ms( 100 );
}

void applicationInit()
{
    fram_spiDriverInit( (T_FRAM_P)&_MIKROBUS1_GPIO, (T_FRAM_P)&_MIKROBUS1_SPI );
    
    fram_eraseAll();
       
}

void applicationTask()
{
    mikrobus_logWrite("Writing MikroE to  Fram memory, from address 0x0150:",_LOG_LINE);
    fram_write (0x0150, &wrData[0], 9);
    mikrobus_logWrite("Reading 9 bytes of Fram memory, from address 0x0150:",_LOG_LINE);
    fram_read(0x0150,&rdData[0],9);
    mikrobus_logWrite("Data read: ",_LOG_TEXT);
    mikrobus_logWrite(rdData,_LOG_LINE);
    Delay_ms(1000);
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}