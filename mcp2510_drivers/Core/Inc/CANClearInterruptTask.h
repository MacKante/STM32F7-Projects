/*
 * CANCommandTask.h
 *
 *  Created on: Jul 6, 2024
 *      Author: MacKante
 */

#pragma once

#include "main.h"
#include <stdint.h>
#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "CAN.h"

extern osMutexId_t SPIMutexHandle;
extern osMessageQueueId_t CANInterruptQueue;
extern osMessageQueueId_t CANRxMessageQueue;

extern uint8_t CANReadInterruptFlag;

extern CANPeripheral peripheral1;
extern CANPeripheral peripheral2;

extern uint8_t TXB0StatusFlag;
extern uint8_t TXB1StatusFlag;
extern uint8_t TXB2StatusFlag;

typedef enum {
	INVALID_INT, // In case of invalid interrupt trigger
    RX0IF,  // Receive Buffer 0 Full
    RX1IF,  // Receive Buffer 1 Full 
    TX0IF,  // Transmit Buffer 0 Empty 
    TX1IF,  // Transmit Buffer 1 Empty 
    TX2IF,  // Transmit Buffer 2 Empty 
    ERRIF,  // Error Interrupt Flag (check EFLG register)
    WAKIF,  // Wakeup Interrupt Flag (*** prolly dont need this)
    MERRF   // Message Error Interrupt
} CAN_INTERRUPT;

void CANClearInterruptTask(void* arg);
void CAN_CLEAR_INTERRUPT(CANPeripheral* peripheral);
void CAN_CLEAR_EFLG(CANPeripheral* peripheral);

