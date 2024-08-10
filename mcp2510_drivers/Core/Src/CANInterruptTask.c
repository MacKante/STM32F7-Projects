/*
 * CANInterruptTask.c
 *
 *  Created on: Jul 20, 2024
 *      Author: MacKante
 */

#include "CANInterruptTask.h"


void CANInterruptTask(void* arg) {
	for(;;) {

	}
}

void CANReadInterrupt() {
	uint8_t CANINTFStatus;
	CAN_IC_READ_REGISTER(CANINTF, &CANINTFStatus, &peripheral);

	// Read status of CANINTF Register starting with MSB and add to queue if its there
	for (uint8_t i = 0; i < 8; i++) {
		if (CANINTFStatus & (1 << (7 - i))) {
			osMessageQueuePut(CANCommandQueue, )
		}
	}
}