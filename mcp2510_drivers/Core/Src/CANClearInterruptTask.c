/*
 * CANCommandTask.c
 *
 *  Created on: Jul 6, 2024
 *      Author: MacKante
 * 
 * The job of this task is to handle interrupts
 * TODO: Rename this to CANInterruptHandlerTask
 */

#include "CANClearInterruptTask.h"

void CANClearInterruptTask(void* arg) {
	for(;;) {
		CAN_CLEAR_INTERRUPT(&peripheral1);
	}
}

void CAN_CLEAR_INTERRUPT(CANPeripheral* peripheral) {

	// Using flag rn
    /* Receive interrupt to clear from queue */
    // CAN_INTERRUPT CANInterruptType;
    // osStatus_t status = osMessageQueueGet(CANInterruptQueue, &CANInterruptType, NULL, osWaitForever);
    
	// Check if interrupt flag has been set
	if (CANReadInterruptFlag == 0) {
		return;
	}

	// TODO this is messed up, figure out best way to read interrupt register
	uint8_t CANINTF_STATUS = 0;
	CAN_IC_READ_REGISTER(CANINTF, &CANINTF_STATUS, peripheral);

	for (uint8_t i = 7; i >  1; i--) {
		CAN_INTERRUPT CANInterruptType;
		// Go through each flag
		if ( (1 << i) & CANINTF_STATUS ) {
			CANInterruptType = (CAN_INTERRUPT)(i + 1);
		} else {
			CANInterruptType = INVALID_INT;
		}

		// Perform action based on interrupt
		if( osMutexWait(SPIMutexHandle, 0) == osOK ) {
		        switch(CANInterruptType) {
		        	case ERRIF:
		                // overflow condition occured or if the error state of transmitter or receiver has changed
						// check ELFG register - TODO
		        		CAN_CLEAR_EFLG(peripheral);
						// clear bit
						CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x20, 0x00, peripheral);
		        	case MERRF:
						/* Message failed to send in one of the buffers, check all of TXBnCTRL registers - TODO */
		        		// CASE 1 (TXBnCTRL.TXERR): Error occured after message started to transmit
		                // TODO: either reset the TXBnCTRL.TXREQ to cancel transmitting the message, or to leave it alone and it will attempt to resend itself
						// clear bit
						CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x80, 0x00, peripheral);
		        	case WAKIF:
						// do nothing? Get out of sleep mode by clearing bit... Read more on this
						// For now clear bit
						CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x40, 0x00, peripheral);
		            case TX0IF:
		                // Optional: Enable flag to let MCU know that TXBuffer is free
		                // clear bit
		                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x04, 0x00, peripheral);
		            case TX1IF:
		                // Optional: Enable flag to let MCU know that TXBuffer is free
		                // clear bit
		                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x08, 0x00, peripheral);
		            case TX2IF:
		            	// Optional: Enable flag to let MCU know that TXBuffer is free
		                // clear bit
		                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x10, 0x00, peripheral);
		            case RX0IF:
		                // receive buffer 0
		                // may not need this
		                // receiveCANMessage(0, &RX0Buffer.ID, &RX0Buffer.DLC, RX0Buffer.data, peripheral);
		            case RX1IF:
		                // receive buffer 1
		                // may not need this
		                // receiveCANMessage(1, &RX1Buffer.ID, &RX1Buffer.DLC, RX1Buffer.data, peripheral);
		            default:
		            	// faulty INT trigger
		            	// reset all flags except RxBuffer flags
		            	CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0xFC, 0x00, peripheral);
		        }
		        osMutexRelease(SPIMutexHandle);
		}
	}
}

void CAN_CLEAR_EFLG(CANPeripheral* peripheral) {
    // Read EFLG register
    uint8_t EFLG_Status = 0;
    CAN_IC_READ_REGISTER(EFLG, &EFLG_Status, peripheral);

    // Temp counter, just to see if error check works
    uint8_t counter = 0;

    if (EFLG_Status & (1 << 7)) { 
        // Handle RX1OVR (Receive Buffer 1 Overflow)
        // - Set when a valid message is received for RXB1 and CANINTF.RX1IF = 1
        // - Must be reset by MCU
        counter++;
    }
    if (EFLG_Status & (1 << 6)) { 
        // Handle RX0OVR (Receive Buffer 0 Overflow)
        // - Set when a valid message is received for RXB0 and CANINTF.RX0IF = 1
        // - Must be reset by MCU
        counter++;
    }
    if (EFLG_Status & (1 << 5)) { 
        // Handle TXBO (Transmit Bus-Off)
        // - Bit set when TEC reaches 255
        // - Reset after a successful bus recovery sequence
        counter++;
    }
    if (EFLG_Status & (1 << 4)) { 
        // Handle TXEP (Transmit Error-Passive)
        // - Set when TEC is equal to or greater than 128
        // - Reset when TEC is less than 128
        counter++;
    }
    if (EFLG_Status & (1 << 3)) { 
        // Handle RXEP (Receive Error-Passive)
        // - Set when REC is equal to or greater than 128
        // - Reset when REC is less than 128
        counter++;
    }
    if (EFLG_Status & (1 << 2)) { 
        // Handle TXWAR (Transmit Error Warning)
        // - Set when TEC is equal to or greater than 96
        // - Reset when TEC is less than 96
        counter++;
    }
    if (EFLG_Status & (1 << 1)) { 
        // Handle RXWAR (Receive Error Warning)
        // - Set when REC is equal to or greater than 96
        // - Reset when REC is less than 96
        counter++;
    }
    if (EFLG_Status & (1 << 0)) { 
        // Handle EWARN (Error Warning)
        // - Set when TEC or REC is equal to or greater than 96 (TXWAR or RXWAR = 1)
        // - Reset when both REC and TEC are less than 96
        counter++;
    }

    CAN_IC_WRITE_REGISTER(EFLG, 0x00, peripheral);
}
