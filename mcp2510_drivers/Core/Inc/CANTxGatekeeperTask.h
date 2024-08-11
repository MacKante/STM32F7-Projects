/*
 * CANTransmitTask.h
 *
 *  Created on: Feb 10, 2024
 *      Author: MacKante
 */


#pragma once

#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "CAN.h"

void CANTxGatekeeperTask(void* arg);
void CANTxGatekeeper(CANMsg *msg);

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;
extern osMutexId_t SPIMutexHandle;
extern osMessageQueueId_t CANTxMessageQueue;

extern CANPeripheral peripheral1;
extern CANPeripheral peripheral2;

extern uint8_t TXB0StatusFlag;
extern uint8_t TXB1StatusFlag;
extern uint8_t TXB2StatusFlag;
