/*
 * CANRxMessageTask.h
 *
 *  Created on: Feb 10, 2024
 *      Author: MacKante
 */

#pragma once

#include "main.h"
#include <stdint.h>
#include "CAN.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"


void CANRxMessageTask(void* arg);
void CANRxMessage();

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;
extern osMutexId_t SPIMutexHandle;
extern osMessageQueueId_t CANRxMessageQueue;

extern CANPeripheral peripheral1;
extern CANPeripheral peripheral2;

extern uint8_t RX0Flag;
extern uint8_t RX1Flag;
