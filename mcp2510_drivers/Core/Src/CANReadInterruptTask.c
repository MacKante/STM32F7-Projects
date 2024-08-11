/*
 * CANInterruptTask.c
 *
 *  Created on: Jul 20, 2024
 *      Author: MacKante
 */

#include <CANReadInterruptTask.h>

void CANReadInterruptTask(void* arg) {
	for(;;) {
		CANReadInterrupt();
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

		// ERRIF: Error Interrupt Flag
		if (CANINTFStatus & 0b00100000) {
			CAN_INTERRUPT errif = ERRIF;
		}

		// MERRF: Message Error Interrupt Flag
		if (CANINTFStatus & 0b10000000) {
			CAN_INTERRUPT merrf = MERRF;
		}

		// WAKIF: Wakeup Interrupt Flag
		if (CANINTFStatus & 0b01000000) {
			CAN_INTERRUPT WAKIF = WAKIF;
		}

		// TX0IF: Transmit Buffer 0 Empty Interrupt Flag
		if (CANINTFStatus & 0b00000100) {
			CAN_INTERRUPT tx0if = TX0IF;
		}

		// TX1IF: Transmit Buffer 1 Empty Interrupt Flag
		if (CANINTFStatus & 0b00001000) {
			CAN_INTERRUPT tx1if = TX1IF;
		}

		// TX2IF: Transmit Buffer 2 Empty Interrupt Flag
		if (CANINTFStatus & 0b00010000) {
			CAN_INTERRUPT tx2if = TX2IF;
		}

	}

}
