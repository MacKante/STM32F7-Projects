/*
 * CANInterruptTask.c
 *
 *  Created on: Jul 20, 2024
 *      Author: MacKante
 */

#include "CANInterruptTask.h"

void CANReadInterruptTask(void* arg) {
	for(;;) {
		CANReadInterrupt()
	}
}

void CANReadInterrupt() {
	// TODO: Probably best to wait for a flag and then read the register

	// Retrieve mutex
	if ( osMutexWait(SPIMutexHandle, 0) == osOK ) {

		// Read status of CANINTF Register
		uint8_t CANINTFStatus;
		CAN_IC_READ_REGISTER(CANINTF, &CANINTFStatus, &peripheral);

		// If status is clear then return
		if ( CANINTFStatus == 0 ) {
			return;
		}

		// Add interrupt to queue starting with MSB
		for (uint8_t i = 0; i < 8; i++) {
			if (CANINTFStatus & (1 << (7 - i))) {
				osMessageQueuePut(CANCommandQueue, )
			}
		}
	}

}