/*
 * can_network.c
 *
 *  Created on: 10 Nov 2016
 *      Author: Catalin I. Ntemkas
 */

#include "can_network.h"
#include "simulation.h"


//================================================================ Init CAN Net
int init_CANNet(){

	int Status;
	CanInstPtr = &Can;
	XCanPs_Config *ConfigPtr;

	/*
	 * Initialize the Can device.
	 */
	ConfigPtr = XCanPs_LookupConfig(CAN_DEVICE_ID);
	if (CanInstPtr == NULL) {
		return XST_FAILURE;
	}
	Status = XCanPs_CfgInitialize(CanInstPtr,
					ConfigPtr,
					ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Run self-test on the device, which verifies basic sanity of the
	 * device and the driver.
	 */
	Status = XCanPs_SelfTest(CanInstPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enter Configuration Mode so we can setup Baud Rate Prescaler
	 * Register (BRPR) and Bit Timing Register (BTR).
	 */
	XCanPs_EnterMode(CanInstPtr, XCANPS_MODE_CONFIG);
	while(XCanPs_GetMode(CanInstPtr) != XCANPS_MODE_CONFIG);

	/*
	 * Setup Baud Rate Prescaler Register (BRPR) and
	 * Bit Timing Register (BTR).
	 */
	XCanPs_SetBaudRatePrescaler(CanInstPtr, TEST_BRPR_BAUD_PRESCALAR);
	XCanPs_SetBitTiming(CanInstPtr, TEST_BTR_SYNCJUMPWIDTH,
				TEST_BTR_SECOND_TIMESEGMENT,

				TEST_BTR_FIRST_TIMESEGMENT);

	/*
	 * Enter Loop Back or Normal Mode.
	 */
	XCanPs_EnterMode(CanInstPtr, XCANPS_MODE);
	while(XCanPs_GetMode(CanInstPtr) != XCANPS_MODE);

	/*
	 * Send a test frame.
	 */
	Status = SendFrame(CanInstPtr, 15);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	Status = RecvFrame(CanInstPtr);

	return Status;
}

//================================================================== Send Frame
int SendFrame(XCanPs *InstancePtr, int hex){
	u8 *FramePtr;
	int Status;

	/*
	 * Create correct values for Identifier and Data Length Code Register.
	 */
	TxFrame[0] = (u32)XCanPs_CreateIdValue((u32)NODE_ID, 0, 0, 0, 0);
	TxFrame[1] = (u32)XCanPs_CreateDlcValue((u32)FRAME_DATA_LENGTH);

	/*
	 * Now fill in the data field with known values so we can verify them
	 * on receive.
	 */

	FramePtr = (u8 *)(&TxFrame[2]);
	FramePtr[indexFR_PUID] = NODE_ID;
	FramePtr[indexFR_DATA] = hex;
	xil_printf("NodeID: %d -> Sending: %d\n", NODE_ID, FramePtr[indexFR_DATA]);

	/*
	 * Wait until TX FIFO has room.
	 */
	while (XCanPs_IsTxFifoFull(InstancePtr) == TRUE);

	/*
	 * Now send the frame.
	 *
	 * Another way to send a frame is keep calling XCanPs_Send() until it
	 * returns XST_SUCCESS. No check on if TX FIFO is full is needed anymore
	 * in that case.
	 */
	Status = XCanPs_Send(InstancePtr, TxFrame);

	return Status;
}

//=============================================================== Receive Frame
int RecvFrame(XCanPs *InstancePtr)
{
	u8 *FramePtr;
	int Status;

	/*
	 * Wait until a frame is received.
	 */
	while (XCanPs_IsRxEmpty(InstancePtr) == TRUE){

	}

	/*
	 * Receive a frame and verify its contents.
	 */
	Status = XCanPs_Recv(InstancePtr, RxFrame);
	if (Status == XST_SUCCESS) {
		/*
		 * Verify Identifier and Data Length Code.
		 */
		if (RxFrame[0] !=
			(u32)XCanPs_CreateIdValue((u32)NODE_ID, 0, 0, 0, 0)){
			return XST_LOOPBACK_ERROR;
		}
		if ((RxFrame[1] & ~XCANPS_DLCR_TIMESTAMP_MASK) != TxFrame[1])
			return XST_LOOPBACK_ERROR;

		/*
		 * Verify Data field contents.
		 */
		FramePtr = (u8 *)(&RxFrame[2]);
		if( amISubscribed(NODE_ID, FramePtr[indexFR_PUID]) ){
			xil_printf("NodeID: %d -> Received: %d from Publisher %d.\n", NODE_ID, FramePtr[indexFR_DATA], FramePtr[indexFR_PUID]);
			XGpio_DiscreteWrite(&LEDInst, LED_CHANNEL, FramePtr[indexFR_DATA]);
		}
	}

	return Status;
}

//============================================================= Am I Subscribed
int amISubscribed(int nodeID, int publisherID){
	/*=========================== Subscriptions using NODE_IDs as indexes.
	 *		Publishers->|	Node_0	|	Node_1	|	Node_2	|	Node_3	|
	 *		Subscribers	|===============================================|
	 *			Node_0	|		0	|		1	|		0	|		1	|	<- Example
	 *			Node_1	|		x	|		x	|		x	|		x	|
	 *			Node_2	|...
	 *			Node_3	|...
	 */

	int subscriptions[NODES_NUM][NODES_NUM] = {
			{0, 1, 1, 1},
			{1, 0, 0, 0},
			{1, 0, 1, 0},
			{0, 1, 0, 0}
	};

	if( subscriptions[nodeID][publisherID] == 1 )
		return SUBSCRIBED;
	else{
		xil_printf("Node %d not subscribed to publisher %d.\n", nodeID, publisherID);
		return NOT_SUBSCRIBED;
	}
}
