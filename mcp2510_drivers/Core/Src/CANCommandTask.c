/*
 * CANCommandTask.c
 *
 *  Created on: Jul 6, 2024
 *      Author: MacKante
 */

#include "CAN.h"
#include "CANCommandTask.h"


void CANCommandTask(void* arg) {
	for(;;) {
		uint8_t command;
		osStatus_t status = osMessageQueueGet(CANCommandQueue, &command, NULL, osWaitForever);
		RUN_CAN_COMMAND(command, &peripheral1);
	}
}

void RUN_CAN_COMMAND(CAN_COMMAND command, CANPeripheral* peripheral) {
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
            // check ELFG register
            // clear bit
        case WAKIF:
            // do nothing
        case MERRF:
            // message failed to send check TXBnCTRL.TXERR bit
            // clear bit
    }
}
