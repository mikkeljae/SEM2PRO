/*
 * simulation.c
 *
 *  Created on: 10 Nov 2016
 *      Author: Catalin I. Ntemkas
 */

#include "simulation.h"
#include "can_network.h"

//=================================================== Handler Button Interrupts
void Handler_IPortInterrupts(void *InstancePtr)
{
	int hex = 0;

	XGpio_InterruptDisable(&IPORTInst, BTN_INT);

	// Ignore additional button presses
	if ((XGpio_InterruptGetStatus(&IPORTInst) & BTN_INT) != BTN_INT) { return; }

	hex = XGpio_DiscreteRead(&IPORTInst, 1);

	//XGpio_DiscreteWrite(&LEDInst, LED_CHANNEL, hex);

	SendFrame(CanInstPtr, hex);

    (void)XGpio_InterruptClear(&IPORTInst, BTN_INT);
    XGpio_InterruptEnable(&IPORTInst, BTN_INT);
}


//============================================================= Setup Functions
int setupInterruptSystem(XScuGic *XScuGicInstancePtr)
{
	// Enable interrupt
	XGpio_InterruptEnable(&IPORTInst, BTN_INT);
	XGpio_InterruptGlobalEnable(&IPORTInst);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			 	 	 	 	 	 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
			 	 	 	 	 	 XScuGicInstancePtr);
	Xil_ExceptionEnable();

	return XST_SUCCESS;

}

int init_IntrCtrlFunction(u16 DeviceId,  XGpio *GpioInstancePtr)
{
	XScuGic_Config *IntcConfig;
	int status;

	// Interrupt controller initialisation
	IntcConfig = XScuGic_LookupConfig(DeviceId);
	status = XScuGic_CfgInitialize(&INTCInst, IntcConfig, IntcConfig->CpuBaseAddress);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Call to interrupt setup
	status = setupInterruptSystem(&INTCInst);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Connect GPIO interrupt to handler
	status = XScuGic_Connect(&INTCInst,
					  	  	 INTC_GPIO_INTERRUPT_ID,
					  	  	 (Xil_ExceptionHandler)Handler_IPortInterrupts,
					  	  	 (void *)GpioInstancePtr);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Enable GPIO interrupts interrupt
	XGpio_InterruptEnable(GpioInstancePtr, 1);
	XGpio_InterruptGlobalEnable(GpioInstancePtr);

	// Enable GPIO and timer interrupts in the controller
	XScuGic_Enable(&INTCInst, INTC_GPIO_INTERRUPT_ID);


	return XST_SUCCESS;
}


//================================================ Initialise Simulation System
int init_SimulationSystem(){
	int status;

	// Initialise LEDs and Push Buttons
	//status = XGpio_Initialize(&LEDInst, LEDS_DEVICE_ID);
	//if(status != XST_SUCCESS) return XST_FAILURE;
	status = XGpio_Initialize(&IPORTInst, IPORT_DEVICE_ID);
	if(status != XST_SUCCESS) return XST_FAILURE;
	//status = XGpio_Initialize(&IPORTInst, IPORT_DEVICE_ID);
	//if(status != XST_SUCCESS) return XST_FAILURE;

	/* Set direction:
	 * 		LEDS -> Output		BTNS -> Input 		IPORT -> Input */
	XGpio_SetDataDirection(&LEDInst, 1, 0x00);
	XGpio_SetDataDirection(&IPORTInst, 1, 0xFF);
	//XGpio_SetDataDirection(&IPORTInst, 1, 0xFF);

	// Initialise interrupt controller
	status = init_IntrCtrlFunction(INTC_DEVICE_ID, &IPORTInst);
	if(status != XST_SUCCESS) return XST_FAILURE;
	//status = init_IntrCtrlFunction2(INTC_DEVICE_ID, &IPORTInst);
	//if(status != XST_SUCCESS) return XST_FAILURE;

	return XST_SUCCESS;
}

