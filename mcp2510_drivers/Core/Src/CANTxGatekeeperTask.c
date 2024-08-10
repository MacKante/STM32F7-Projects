/*
 * CANTransmitTask.c
 *
 *  Created on: Feb 10, 2024
 *      Author: MacKante
 */

#include "CANTxGatekeeperTask.h"

void CANTxGatekeeperTask(void* arg) {

	// This block is to initialize a message queue of CAN Messages to send for testing
    CANMsg newMsg;
    for (;;) {
        CANTxGatekeeper(&newMsg);
    }
}

void CANTxGatekeeper(CANMsg *msg) {
	// Acquire message to send from queue
	osStatus_t status = osMessageGet(CANTxMessageQueue, msg, NULL, osWaitForever);
	if (status != osOK) {
		// Handle if not ok
	}

	// Wait for mutex
	if ( osMutexWait(SPIMutexHandle, 0) == osOK )
	{
		// check if CAN message is standard/extended
		// if extendedID == 0, then message is standard
		if ((msg->extendedID == 0) && (msg->ID != 0))
		{
			sendCANMessage(msg, &peripheral);
		}
		else
		{
			sendExtendedCANMessage(msg, &peripheral);
		}
		osMutexRelease(SPIMutexHandle);
	}

}
