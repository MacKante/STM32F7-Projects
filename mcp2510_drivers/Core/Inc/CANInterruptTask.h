/*
 * CANInterruptTask.h
 *
 *  Created on: Jul 20, 2024
 *      Author: MacKante
 */

#pragma once

#include "CAN.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"

extern osMessageQueueId_t CANCommandQueue;
extern CANPeripheral peripheral1;
extern CANPeripheral peripheral2;

extern osMutexId_t SPIMutexHandle;

void CANReadInterruptTask(void* arg);
void CANReadInterrupt();

typedef struct {
	CAN_COMMAND command;
} CAN_COMMAND_MSG;