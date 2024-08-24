/*
 * CANTransmitTask.c
 *
 *  Created on: Feb 10, 2024
 *      Author: MacKante
 */

#include "CANTxGatekeeperTask.h"

void CANTxGatekeeperTask(void* arg) {
    for (;;) {
        CANTxGatekeeper();
    }
}

void CANTxGatekeeper(CANMsg *msg) {
	// Acquire message to send from queue
	CANMsg newMsg;
	osStatus_t status = osMessageQueueGet(CANTxMessageQueue, &newMsg, NULL, osWaitForever);
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
			sendCANMessage(msg, &peripheral2);
		}
		else
		{
			sendExtendedCANMessage(msg, &peripheral2);
		}
		osMutexRelease(SPIMutexHandle);
	}

}
