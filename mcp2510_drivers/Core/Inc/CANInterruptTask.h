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

void CANInterruptTask(void* arg);
