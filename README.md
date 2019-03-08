![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# FRAM Click

---

- **CIC Prefix**  : FRAM
- **Author**      : MikroE Team
- **Verison**     : 1.0.0
- **Date**        : jan 2018.

---

### Software Support

We provide a library for the FRAM Click on our [LibStock](http://libstock.mikroe.com/projects/view/776/fram-click-example) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**


Key functions :

- ``` void fram_write(uint16_t address, uint8_t *buffer, uint16_t counter)  ``` - Function writes to sequential memory locations from buffer
- ``` void fram_read(uint16_t address, uint8_t *buffer, uint16_t count)   ``` - Function reads sequential memory locations to buffer
- ```void fram_writeEnable()   ``` - Function enables data writing in FRAM memory space

**Examples Description**

- System Initialization - GPIO and SPI module Initalization 
- Application Initialization -Fram Driver Initialization, initialization of click by setting mikorBUS pins to
  approprieate logic level, performing erase all and write enable functions. 
- Application Task - Writing data to click memory and displaying the read data via UART. 



```.c
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


```



The full application code, and ready to use projects can be found on our 
[LibStock](http://libstock.mikroe.com/projects/view/776/fram-click-example) page.

Other mikroE Libraries used in the example:

- SPI
- UART


**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
