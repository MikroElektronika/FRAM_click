/*
    __fram_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __fram_driver.h
@brief    FRAM Driver
@mainpage FRAM Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   FRAM
@brief      FRAM Click Driver
@{

| Global Library Prefix | **FRAM** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **jan 2018.**      |
| Developer             | **MikroE Team**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _FRAM_H_
#define _FRAM_H_

/** 
 * @macro T_FRAM_P
 * @brief Driver Abstract type 
 */
#define T_FRAM_P    const uint8_t*

/** @defgroup FRAM_COMPILE Compilation Config */              /** @{ */

   #define   __FRAM_DRV_SPI__                            /**<     @macro __FRAM_DRV_SPI__  @brief SPI driver selector */
//  #define   __FRAM_DRV_I2C__                            /**<     @macro __FRAM_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __FRAM_DRV_UART__                           /**<     @macro __FRAM_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup FRAM_VAR Variables */                           /** @{ */

// OP-CODEs
extern const uint8_t _FRAM_WREN    ;
extern const uint8_t _FRAM_WRDI    ;
extern const uint8_t _FRAM_RDSR    ;
extern const uint8_t _FRAM_WRSR    ;
extern const uint8_t _FRAM_READ    ;
extern const uint8_t _FRAM_WRITE   ;

// Status register bits
extern const uint8_t _FRAM_WPEN     ;
extern const uint8_t _FRAM_BP1      ;
extern const uint8_t _FRAM_BP0      ;
extern const uint8_t _FRAM_WEL      ;

extern const uint16_t _FRAM_MEM_SIZE ;


                                                                       /** @} */
/** @defgroup FRAM_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup FRAM_INIT Driver Initialization */              /** @{ */

#ifdef   __FRAM_DRV_SPI__
void fram_spiDriverInit(T_FRAM_P gpioObj, T_FRAM_P spiObj);
#endif
#ifdef   __FRAM_DRV_I2C__
void fram_i2cDriverInit(T_FRAM_P gpioObj, T_FRAM_P i2cObj, uint8_t slave);
#endif
#ifdef   __FRAM_DRV_UART__
void fram_uartDriverInit(T_FRAM_P gpioObj, T_FRAM_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void fram_gpioDriverInit(T_FRAM_P gpioObj);
                                                                       /** @} */
/** @defgroup FRAM_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Fram click init
 *
 * Function that initializes Fram click by setting Chip select
 *
 */
void fram_init(); 

/**
 * @brief Fram click Write Enable
 *
 * Function that sends write enable command to the chip
 *
 */
void fram_writeEnable(); 
/**
 * @brief Fram click Write Disable
 *
 * Function that sends write disable command to the chip
 *
 */
void fram_writeDisable();
/**
 * @brief Fram click Read Status
 *
 *Function returns content of FRAM status register
 *
 */
uint8_t fram_readStatus();
/**
 * @brief Fram click Write Status
 *
 * Function writes in FRAM status register
 * NOTE: It is only allowed to write bits 2 and 3. 
 * Others will be ignored.
 *
 */
void fram_writeStatus(uint8_t value);

/**
 * @brief Fram read
 *
 * @param in : address - desired starting address (0x0000 to _FRAM_MEM_SIZE)
 * @param in : buffer - pointer to read buffer
 * @param in : count - number of bytes to be read
 * 
 *  Function reads sequential memory locations to buffer
 * 
 */
void fram_read(uint16_t address, uint8_t *buffer, uint16_t count);
/**
 * @brief Fram write
 *
 * @param in : address - desired starting address (0x0000 to _FRAM_MEM_SIZE)
 * @param in : buffer - pointer to write buffer
 * @param in : counter - number of bytes to be write
 * 
 * Function writes to sequential memory locations from buffer
 * 
 */
void fram_write(uint16_t address, uint8_t *buffer, uint16_t counter); 

/**
 * 
 * @brief Fram erase all
 * Function flushes whole data memory and resets status reg
 * 
 */
void fram_eraseAll(); 
                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_FRAM_STM.c
    @example Click_FRAM_TIVA.c
    @example Click_FRAM_CEC.c
    @example Click_FRAM_KINETIS.c
    @example Click_FRAM_MSP.c
    @example Click_FRAM_PIC.c
    @example Click_FRAM_PIC32.c
    @example Click_FRAM_DSPIC.c
    @example Click_FRAM_AVR.c
    @example Click_FRAM_FT90x.c
    @example Click_FRAM_STM.mbas
    @example Click_FRAM_TIVA.mbas
    @example Click_FRAM_CEC.mbas
    @example Click_FRAM_KINETIS.mbas
    @example Click_FRAM_MSP.mbas
    @example Click_FRAM_PIC.mbas
    @example Click_FRAM_PIC32.mbas
    @example Click_FRAM_DSPIC.mbas
    @example Click_FRAM_AVR.mbas
    @example Click_FRAM_FT90x.mbas
    @example Click_FRAM_STM.mpas
    @example Click_FRAM_TIVA.mpas
    @example Click_FRAM_CEC.mpas
    @example Click_FRAM_KINETIS.mpas
    @example Click_FRAM_MSP.mpas
    @example Click_FRAM_PIC.mpas
    @example Click_FRAM_PIC32.mpas
    @example Click_FRAM_DSPIC.mpas
    @example Click_FRAM_AVR.mpas
    @example Click_FRAM_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __fram_driver.h

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