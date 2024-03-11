/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// EQEP1 -> Rail_enc Pinmux
//
//
// EQEP1_A - GPIO Settings
//
#define GPIO_PIN_EQEP1_A 44
#define Rail_enc_EQEPA_GPIO 44
#define Rail_enc_EQEPA_PIN_CONFIG GPIO_44_EQEP1_A
//
// EQEP1_B - GPIO Settings
//
#define GPIO_PIN_EQEP1_B 37
#define Rail_enc_EQEPB_GPIO 37
#define Rail_enc_EQEPB_PIN_CONFIG GPIO_37_EQEP1_B
//
// EQEP1_INDEX - GPIO Settings
//
#define GPIO_PIN_EQEP1_INDEX 43
#define Rail_enc_EQEPINDEX_GPIO 43
#define Rail_enc_EQEPINDEX_PIN_CONFIG GPIO_43_EQEP1_INDEX
//
// GPIO31 - GPIO Settings
//
#define LED4_pin_GPIO_PIN_CONFIG GPIO_31_GPIO31
//
// GPIO34 - GPIO Settings
//
#define LED5_pin_GPIO_PIN_CONFIG GPIO_34_GPIO34
//
// GPIO27 - GPIO Settings
//
#define Test_pin0_GPIO_PIN_CONFIG GPIO_27_GPIO27

//*****************************************************************************
//
// EQEP Configurations
//
//*****************************************************************************
#define Rail_enc_BASE EQEP1_BASE
void Rail_enc_init();

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define LED4_pin 31
void LED4_pin_init();
#define LED5_pin 34
void LED5_pin_init();
#define Test_pin0 27
void Test_pin0_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_Rail_enc
#define INT_Rail_enc INT_EQEP1
#define INT_Rail_enc_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP5
extern __interrupt void INT_Rail_enc_ISR(void);

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	EQEP_init();
void	GPIO_init();
void	INTERRUPT_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
