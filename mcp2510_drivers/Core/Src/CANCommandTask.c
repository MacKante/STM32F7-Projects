/*
 * CANCommandTask.c
 *
 *  Created on: Jul 6, 2024
 *      Author: MacKante
 */

#include "CAN.h"
#include "CANCommandTask.h"

void CANInterruptTask(void* arg) {
	for(;;) {
		CAN_CLEAR_INTERRUPT(command, &peripheral1);
	}
}

void CAN_CLEAR_INTERRUPT(CANPeripheral* peripheral) {

    /* Receive interrupt to clear from queue */
    CAN_INTERRUPT canInterruptType;
    osStatus_t status = osMessageQueueGet(CANCommandQueue, &canInterruptType, NULL, osWaitForever);
    
    /* Handle interrupt */
    if( osMutexWait(SPIMutexHandle, 0) == osOK ) {
        switch(command) {
            case RX0IF:
                // receive buffer 0
                // may not need this
                receiveCANMessage(0, &RX0Buffer.ID, &RX0Buffer.DLC, RX0Buffer.data, peripheral);
            case RX1IF:
                // receive buffer 1
                // may not need this
                receiveCANMessage(1, &RX1Buffer.ID, &RX1Buffer.DLC, RX1Buffer.data, peripheral);
            case TX0IF:
                // clear bit
                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x04, 0x04, peripheral);
            case TX1IF:
                // clear bit
                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x8, 0x8, peripheral);
            case TX2IF:
                // clear bit
                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x10, 0x10, peripheral);
            case ERRIF:
                // check ELFG register - TODO
                // clear bit
                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x20, 0x20, peripheral);
            case WAKIF:
                // do nothing? Get out of sleep mode by clearing bit... Read more on this
                // For now clear bit
                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x40, 0x40, peripheral);
            case MERRF:
                // message failed to send check TXBnCTRL.TXERR bit - TODO
                // clear bit 
                CAN_IC_WRITE_REGISTER_BITWISE(CANINTF, 0x80, 0x80, peripheral);
        }
        osMutexRelease(SPIMutexHandle);
    }
}
