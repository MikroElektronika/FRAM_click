/*
    __fram_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__fram_driver.h"
#include "__fram_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __FRAM_DRV_I2C__
static uint8_t _slaveAddress;
#endif

// OP-CODEs
const uint8_t _FRAM_WREN     =  0x06;
const uint8_t _FRAM_WRDI     =  0x04;
const uint8_t _FRAM_RDSR     =  0x05;
const uint8_t _FRAM_WRSR     =  0x01;
const uint8_t _FRAM_READ     =  0x03;
const uint8_t _FRAM_WRITE    =  0x02;

// Status register bits
const uint8_t _FRAM_WPEN     =  0x80;
const uint8_t _FRAM_BP1      =  0x08;
const uint8_t _FRAM_BP0      =  0x04;
const uint8_t _FRAM_WEL      =  0x02;

const uint16_t _FRAM_MEM_SIZE  =  0x8000;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __FRAM_DRV_SPI__

void fram_spiDriverInit(T_FRAM_P gpioObj, T_FRAM_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
    hal_gpio_csSet(1);
}

#endif
#ifdef   __FRAM_DRV_I2C__

void fram_i2cDriverInit(T_FRAM_P gpioObj, T_FRAM_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __FRAM_DRV_UART__

void fram_uartDriverInit(T_FRAM_P gpioObj, T_FRAM_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

// GPIO Only Drivers - remove in other cases
void fram_gpioDriverInit(T_FRAM_P gpioObj)
{
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
}

/* ----------------------------------------------------------- IMPLEMENTATION */

void fram_init() 
{
  hal_gpio_csSet(1);

}
             
//************************************************************
//  @summary: Function enables data writing in FRAM memory space
//  @version: 1.00 (M.V.)
//  @param: None
//  @return: None
//************************************************************
void fram_writeEnable() 
{
    uint8_t temp[1];
    temp[0] = _FRAM_WREN;
    hal_gpio_csSet(0);
    hal_spiWrite(temp,1);
    hal_gpio_csSet(1);
  
    
}

//************************************************************
//  @summary: Function disables data writing in FRAM memory space
//  @version: 1.00 (M.V.)
//  @param: None
//  @return: None
//************************************************************
void fram_writeDisable() 

{
    uint8_t temp[1];
    temp[0] = _FRAM_WRDI;
    
    hal_gpio_csSet(0);
    hal_spiWrite(temp,1);
    hal_gpio_csSet(1);
  
    return;
}

//************************************************************
//  @summary: Function returns content of FRAM status register
//  @version: 1.00 (M.V.)
//  @param: None
//  @return: Content of FRAM status register
//************************************************************
uint8_t fram_readStatus() 
{
  
    uint8_t temp[1];
    temp[0] = _FRAM_RDSR;
    
    hal_gpio_csSet(0);
    hal_spiWrite(temp,1);
    hal_spiRead(temp,1);
    hal_gpio_csSet(1);
  
    return temp[0];
}

//************************************************************
//  @summary: Function writes in FRAM status register
//  @version: 1.00 (M.V.)
//  @param: _Value - desired status register value; NOTE: It is
//                   only allowed to write bits 2 and 3. Others
//                   will be ignored.
//  @return: None
//************************************************************
void fram_writeStatus(uint8_t value) 

{
    
    uint8_t temp[2];
    temp[0] = _FRAM_WRSR;
    temp[1] = value;
    fram_writeEnable();
    hal_gpio_csSet(0);
    hal_spiWrite(temp,2);
    hal_gpio_csSet(1);
  
   
}

//************************************************************
//  @summary: Function reads sequential memory locations to buffer
//  @version: 1.00 (M.V.)
//  @param: _Start_Address - desired starting address (0x0000 to MEM_SIZE)
//  @param: _Read_Buffer - pointer to read buffer
//  @param: _Read_Number - number of bytes to be read
//  @return: None
//************************************************************
void fram_read(uint16_t address, uint8_t *buffer, uint16_t count) 
{
   
    uint8_t *dataPtr;
    uint8_t temp[3];

    dataPtr  = buffer;

    temp[0] = _FRAM_READ;
    temp[1] = (uint8_t)(address >> 8);
    temp[2] = (uint8_t)(address & 0x00FF);
    fram_writeEnable(); 
    hal_gpio_csSet(0);
    hal_spiWrite(temp,3);
    hal_spiRead(dataPtr,count);
    hal_gpio_csSet(1);
  
}

//************************************************************
//  @summary: Function writes to sequential memory locations from buffer
//  @version: 1.00 (M.V.)
//  @param: _Start_Address - desired starting address (0x0000 to MEM_SIZE)
//  @param: _Write_Buffer - pointer to write buffer
//  @param: _Read_Number - number of bytes to be written
//  @return: None
//************************************************************
void fram_write(uint16_t address, uint8_t *buffer, uint16_t counter) 
{
    
    uint8_t *dataPtr;
    uint8_t temp[3];

    dataPtr  = buffer;
    
    temp[0] = _FRAM_WRITE;
    temp[1] = (uint8_t)(address >> 8);
    temp[2] = (uint8_t)(address & 0x00FF);
    fram_writeEnable();
    hal_gpio_csSet(0);
    hal_spiWrite(temp,3);
    hal_spiWrite(dataPtr,counter);
    hal_gpio_csSet(1);

  
}

//************************************************************
//  @summary: Function flushes whole data memory and resets status reg
//  @version: 1.00 (M.V.)
//  @param: None
//  @return: None
//************************************************************
void fram_eraseAll() 
{
  uint16_t _cntr;
  uint8_t temp[3];

  temp[0] = _FRAM_WRITE;
  temp[1] = 0x00;
  temp[2] = 0x00;
  fram_writeStatus(0x00);
  fram_writeEnable();
  
  hal_gpio_csSet(0);
  hal_spiWrite(temp,3);

  temp[0] = 0x00;
  for(_cntr=0; _cntr<=_FRAM_MEM_SIZE; _cntr++)
    hal_spiWrite(temp,1);
    
  hal_gpio_csSet(1);
  
  fram_writeDisable();

  
}





/* -------------------------------------------------------------------------- */
/*
  __fram_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */