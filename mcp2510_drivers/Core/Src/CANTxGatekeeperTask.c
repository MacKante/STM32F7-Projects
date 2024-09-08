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

void CANTxGatekeeper() {
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
		if ((newMsg.extendedID == 0) && (newMsg.ID != 0))
		{
			sendCANMessage(&newMsg, &peripheral1);
		}
		else
		{
			sendExtendedCANMessage(&newMsg, &peripheral1);
		}
		osMutexRelease(SPIMutexHandle);
	}

}
