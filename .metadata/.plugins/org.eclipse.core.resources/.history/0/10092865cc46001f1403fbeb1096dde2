/*
 * CANCommandTask.h
 *
 *  Created on: Jul 6, 2024
 *      Author: MacKante
 */

#pragma once

#include "CAN.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"

extern osMutexId_t SPIMutexHandle;
extern osMessageQueueId_t CANRxMessageQueue;

typedef enum {
    RX0IF,  // Receive Buffer 0 Full
    RX1IF,  // Receive Buffer 1 Full 
    TX0IF,  // Transmit Buffer 0 Empty 
    TX1IF,  // Transmit Buffer 1 Empty 
    TX2IF,  // Transmit Buffer 2 Empty 
    ERRIF,  // Error Interrupt Flag (check EFLG register)
    WAKIF,  // Wakeup Interrupt Flag (*** prolly dont need this)
    MERRF   // Message Error Interrupt
} CAN_COMMAND;

void CANCommandTask(void* arg);
void RUN_CAN_COMMAND(CAN_COMMAND command);

extern CANPeripheral peripheral1;
extern ReceiveMsg RX0Buffer;
extern ReceiveMsg RX1Buffer;
