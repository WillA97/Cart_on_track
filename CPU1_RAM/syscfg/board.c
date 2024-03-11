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

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	EQEP_init();
	GPIO_init();
	INTERRUPT_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	//
	// EQEP1 -> Rail_enc Pinmux
	//
	GPIO_setPinConfig(Rail_enc_EQEPA_PIN_CONFIG);
	GPIO_setPadConfig(Rail_enc_EQEPA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(Rail_enc_EQEPA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(Rail_enc_EQEPB_PIN_CONFIG);
	GPIO_setPadConfig(Rail_enc_EQEPB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(Rail_enc_EQEPB_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(Rail_enc_EQEPINDEX_PIN_CONFIG);
	GPIO_setPadConfig(Rail_enc_EQEPINDEX_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(Rail_enc_EQEPINDEX_GPIO, GPIO_QUAL_SYNC);

	// GPIO31 -> LED4_pin Pinmux
	GPIO_setPinConfig(GPIO_31_GPIO31);
	// GPIO34 -> LED5_pin Pinmux
	GPIO_setPinConfig(GPIO_34_GPIO34);
	// GPIO27 -> Test_pin0 Pinmux
	GPIO_setPinConfig(GPIO_27_GPIO27);

}

//*****************************************************************************
//
// EQEP Configurations
//
//*****************************************************************************
void EQEP_init(){
	Rail_enc_init();
}

void Rail_enc_init(){
	//
	// Disable, clear all flags and interrupts
	//
	EQEP_disableInterrupt(Rail_enc_BASE,
		(EQEP_INT_GLOBAL     		|   
		EQEP_INT_POS_CNT_ERROR		|      
		EQEP_INT_PHASE_ERROR    	| 
		EQEP_INT_DIR_CHANGE    		| 
		EQEP_INT_WATCHDOG          	|   
		EQEP_INT_UNDERFLOW         	|
		EQEP_INT_OVERFLOW        	|
		EQEP_INT_POS_COMP_READY    	|	
		EQEP_INT_POS_COMP_MATCH   	|
		EQEP_INT_STROBE_EVNT_LATCH	| 
		EQEP_INT_INDEX_EVNT_LATCH 	|
		EQEP_INT_UNIT_TIME_OUT   	|
		EQEP_INT_QMA_ERROR));
	EQEP_clearInterruptStatus(Rail_enc_BASE,
		(EQEP_INT_GLOBAL     		|   
		EQEP_INT_POS_CNT_ERROR		|      
		EQEP_INT_PHASE_ERROR    	| 
		EQEP_INT_DIR_CHANGE    		| 
		EQEP_INT_WATCHDOG          	|   
		EQEP_INT_UNDERFLOW         	|
		EQEP_INT_OVERFLOW        	|
		EQEP_INT_POS_COMP_READY    	|	
		EQEP_INT_POS_COMP_MATCH   	|
		EQEP_INT_STROBE_EVNT_LATCH	| 
		EQEP_INT_INDEX_EVNT_LATCH 	|
		EQEP_INT_UNIT_TIME_OUT   	|
		EQEP_INT_QMA_ERROR));
	EQEP_SourceSelect source_Rail_enc =
	{
		EQEP_SOURCE_DEVICE_PIN, 		// eQEPA source
		EQEP_SOURCE_DEVICE_PIN,		// eQEPB source
		EQEP_SOURCE_DEVICE_PIN,  	// eQEP Index source 
	};
	//
	// Selects the source for eQEPA/B/I signals
	//
	EQEP_selectSource(Rail_enc_BASE, source_Rail_enc);
	//
	// Set the strobe input source of the eQEP module.
	//
	EQEP_setStrobeSource(Rail_enc_BASE,EQEP_STROBE_FROM_GPIO);
	//
	// Sets the polarity of the eQEP module's input signals.
	//
	EQEP_setInputPolarity(Rail_enc_BASE,false,false,false,false);
	//
	// Configures eQEP module's quadrature decoder unit.
	//
	EQEP_setDecoderConfig(Rail_enc_BASE, (EQEP_CONFIG_QUADRATURE | EQEP_CONFIG_1X_RESOLUTION | EQEP_CONFIG_NO_SWAP | EQEP_CONFIG_IGATE_DISABLE));
	//
	// Set the emulation mode of the eQEP module.
	//
	EQEP_setEmulationMode(Rail_enc_BASE,EQEP_EMULATIONMODE_RUNFREE);
	//
	// Configures eQEP module position counter unit.
	//
	EQEP_setPositionCounterConfig(Rail_enc_BASE,EQEP_POSITION_RESET_IDX,3999U);
	//
	// Sets the current encoder position.
	//
	EQEP_setPosition(Rail_enc_BASE,0U);
	//
	// Enables the eQEP module unit timer.
	//
	EQEP_enableUnitTimer(Rail_enc_BASE,10000U);
	//
	// Disables the eQEP module watchdog timer.
	//
	EQEP_disableWatchdog(Rail_enc_BASE);
	//
	// Configures the quadrature modes in which the position count can be latched.
	//
	EQEP_setLatchMode(Rail_enc_BASE,(EQEP_LATCH_UNIT_TIME_OUT|EQEP_LATCH_RISING_STROBE|EQEP_LATCH_RISING_INDEX));
	//
	// Set the quadrature mode adapter (QMA) module mode.
	//
	EQEP_setQMAModuleMode(Rail_enc_BASE,EQEP_QMA_MODE_BYPASS);
	//
	// Disable Direction Change During Index
	//
	EQEP_disableDirectionChangeDuringIndex(Rail_enc_BASE);
	//
	// Enables individual eQEP module interrupt sources.
	//
	EQEP_enableInterrupt(Rail_enc_BASE,(EQEP_INT_UNIT_TIME_OUT));
	//
	// Configures the mode in which the position counter is initialized.
	//
	EQEP_setPositionInitMode(Rail_enc_BASE,(EQEP_INIT_RISING_INDEX));
	//
	// Sets the software initialization of the encoder position counter.
	//
	EQEP_setSWPositionInit(Rail_enc_BASE,false);
	//
	// Sets the init value for the encoder position counter.
	//
	EQEP_setInitialPosition(Rail_enc_BASE,0U);
	//
	// Enables the eQEP module.
	//
	EQEP_enableModule(Rail_enc_BASE);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	LED4_pin_init();
	LED5_pin_init();
	Test_pin0_init();
}

void LED4_pin_init(){
	GPIO_setPadConfig(LED4_pin, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(LED4_pin, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED4_pin, GPIO_DIR_MODE_OUT);
}
void LED5_pin_init(){
	GPIO_setPadConfig(LED5_pin, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(LED5_pin, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED5_pin, GPIO_DIR_MODE_OUT);
}
void Test_pin0_init(){
	GPIO_writePin(Test_pin0, 0);
	GPIO_setPadConfig(Test_pin0, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(Test_pin0, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(Test_pin0, GPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Setings for INT_Rail_enc
	Interrupt_register(INT_Rail_enc, &INT_Rail_enc_ISR);
	Interrupt_enable(INT_Rail_enc);
}
