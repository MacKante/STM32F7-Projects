/*
 * CANRxInterruptTask.c
 *
 *  Created on: Feb 10, 2024
 *      Author: MacKante
 */

#include "CANRxMessageTask.h"

void CANRxMessageTask(void* arg)
{
	for(;;) {
		CANRxMessage();
	}
}

void CANRxMessage()
{
	// Receive pin that triggered receive interrupt
	uint16_t pin;
	osStatus_t status = osMessageQueueGet(CANRxMessageQueue, &pin, NULL, osWaitForever);
	if (status != osOK) {
		// Handle if not ok
	}

	// Find what channel to use
	uint8_t channel;
	switch (pin) {
		case CAN_RX0BF_Pin:
			channel = 0;
			break;
		case CAN_RX1BF_Pin:
			channel = 1;
			break;
	}

	uint32_t ID = 0;
	uint8_t DLC = 0;
	uint8_t data[8] = {0};

	// Attain mutex then read message
	if ( osMutexWait(SPIMutexHandle, 0) == osOK)
	{
		receiveCANMessage(channel, &ID, &DLC, data, &peripheral1);
		osMutexRelease(SPIMutexHandle);
	}

	// Add cases depending on ID of message
	// switch (ID) {
	// 	default:
	// 		// Do nothing?
	// 		continue;
	// }
}
