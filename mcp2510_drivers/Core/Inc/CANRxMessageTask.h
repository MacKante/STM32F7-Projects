/*
 * CANRxMessageTask.h
 *
 *  Created on: Feb 10, 2024
 *      Author: MacKante
 */

#pragma once

#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "CAN.h"

void CANRxMessageTask(void* arg);
void CANRxMessage();

typedef struct {
	uint8_t pin;
} CAN_RX_Channel;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;
extern osMutexId_t SPIMutexHandle;
extern osMessageQueueId_t CANRxMessageQueue;

extern CANPeripheral peripheral1;
extern CANPeripheral peripheral2;

extern ReceiveMsg RX0Buffer;
extern ReceiveMsg RX1Buffer;
