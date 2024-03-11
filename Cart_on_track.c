//#############################################################################
//
// FILE:   empty_driverlib_main.c
//
//! \addtogroup driver_example_list
//! <h1>Empty Project Example</h1> 
//!
//! This example is an empty project setup for Driverlib development.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "DCL.h"
#include "math.h"

//
// Defines
//
#define ENCODER_SLOTS   1000U           // LVSERVOMTR is a 1000-line encoder
#define UNIT_PERIOD     10000U          // Unit period in microseconds
#define ENC_radius      1            // Encoder radius in centimeters

//
// Globals
//
uint32_t oldCount = 0;                  // stores the previous position counter value
uint32_t newCount = 0;                  // stores the new position counter value for frequency calculation
uint32_t currentEncoderPosition = 0;    // stores the current encoder position
int32_t frequency = 0;                  // measured quadrature signal frequency of motor using eQEP
float32_t speed = 0.0f;                 // measured speed of motor in rpm
int32_t direction = 0;                  // direction of rotation of motor
float distance = 0;                   //linear distance travelled

//
// Main
//
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        DEVICE_DELAY_US(500000);
        GPIO_togglePin(LED4_pin);
        GPIO_togglePin(LED5_pin);
    }
}


__interrupt void INT_Rail_enc_ISR(void){

    //
    // Save current encoder position value for monitoring
    GPIO_togglePin(Test_pin0);
    //
    currentEncoderPosition = EQEP_getPosition(Rail_enc_BASE);
    //
    // Get position counter value latched on unit time-out event
    //
    newCount = EQEP_getPositionLatch(Rail_enc_BASE);
    //
    // Gets rotation direction of motor
    //
    direction = EQEP_getDirection(Rail_enc_BASE);

    if (direction > 0 ){
          if (newCount >= oldCount)
              newCount = newCount - oldCount;
          else
              newCount = ((4 * ENCODER_SLOTS - 1) - oldCount) + newCount;
          }
      else {
          if (newCount <= oldCount)
              newCount = oldCount - newCount;
          else
              newCount = ((4 * ENCODER_SLOTS - 1) - newCount) + oldCount;
          }
      //
      // Stores the current position count value to oldCount variable
      //
      oldCount = currentEncoderPosition;
      distance = distance+ direction*(2*3.14159F/4000*(newCount));


    EQEP_clearInterruptStatus(Rail_enc_BASE,EQEP_INT_UNIT_TIME_OUT|EQEP_INT_GLOBAL);
    Interrupt_clearACKGroup(INT_Rail_enc_INTERRUPT_ACK_GROUP);

}
//
// End of File
//
