/*
 * CANTransmitTask.h
 *
 *  Created on: Feb 10, 2024
 *      Author: MacKante
 */


#pragma once

#include "cmsis_os.h"
#include "CAN.h"

void CANTxGatekeeperTask(void* arg);
void CANTxGatekeeper(CANMsg *msg);

extern SPI_HandleTypeDef hspi1;
extern osMutexId_t SPIMutexHandle;
extern osMessageQueueId_t CANTxMessageQueue;


// ------------------------------------

void CANTxGatekeeperTask_2(void* arg);
void CANTxGatekeeper_2(CANMsg *msg);

extern SPI_HandleTypeDef hspi4;
extern osMutexId_t SPI2MutexHandle;
extern osMessageQueueId_t CAN2TxMessageQueue;
