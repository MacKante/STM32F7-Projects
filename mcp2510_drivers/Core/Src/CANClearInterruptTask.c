/*
 * CANCommandTask.c
 *
 *  Created on: Jul 6, 2024
 *      Author: MacKante
 */

#include <CANClearInterruptTask.h>
#include "CAN.h"

void CANClearInterruptTask(void* arg) {
	for(;;) {
		CAN_CLEAR_INTERRUPT(command, &peripheral1);
	}
}

void CAN_CLEAR_INTERRUPT(CANPeripheral* peripheral) {

    /* Receive interrupt to clear from queue */
    CAN_INTERRUPT CANInterruptType;
    osStatus_t status = osMessageQueueGet(CANInterruptQueue, &CANInterruptType, NULL, osWaitForever);
    
    /* Handle interrupt */
    if( osMutexWait(SPIMutexHandle, 0) == osOK ) {
        switch(command) {
        	case ERRIF:
				// check ELFG register - TODO
				// clear bit
				CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x20, 0x20, peripheral);
        	case MERRF:
				/* Message failed to send in one of the buffers, check all of TXBnCTRL registers - TODO */
        		// CASE 1 (TXBnCTRL.TXERR): Error occured after message started to transmit
        		// CASE 2 (TXBnCTRL.MLOA): Message was lost in arbitration
				// clear bit
				CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x80, 0x80, peripheral);
        	case WAKIF:
				// do nothing? Get out of sleep mode by clearing bit... Read more on this
				// For now clear bit
				CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x40, 0x40, peripheral);
            case TX0IF:
                // Optional: Enable flag to let MCU know that TXBuffer is free
                // clear bit
                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x04, 0x04, peripheral);
            case TX1IF:
                // Optional: Enable flag to let MCU know that TXBuffer is free

                // clear bit
                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x8, 0x8, peripheral);
            case TX2IF:
            	// Optional: Enable flag to let MCU know that TXBuffer is free

                // clear bit
                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x10, 0x10, peripheral);
            case RX0IF:
                // receive buffer 0
                // may not need this
                // receiveCANMessage(0, &RX0Buffer.ID, &RX0Buffer.DLC, RX0Buffer.data, peripheral);
            case RX1IF:
                // receive buffer 1
                // may not need this
                // receiveCANMessage(1, &RX1Buffer.ID, &RX1Buffer.DLC, RX1Buffer.data, peripheral);
        }
        osMutexRelease(SPIMutexHandle);
    }
}
