/*
 * CANRxInterruptTask.c
 *
 *  Created on: Feb 10, 2024
 *      Author: MacKante
 */

#include "CANRxInterruptTask.h"
#include "CAN.h"


void CANRxInterruptTask(void* arg)
{
	for(;;) {
		CANRxInterrupt();
		osDelay(100);
	}
}

void CANRxInterrupt()
{
	uint16_t GPIO_Pin = 0;
	osMessageQueueGet(CANInterruptQueue, &GPIO_Pin, 0, osWaitForever);

	uint32_t ID = 0;
	uint8_t DLC = 0;
	uint8_t data[8] = {0};

	if (osMutexWait(SPIMutexHandle, 0) == osOK)
	{
		if(GPIO_Pin == CAN_RX0BF_Pin)
		{
			receiveCANMessage(0, &ID, &DLC, data);
		}
		else if (GPIO_Pin == CAN_RX1BF_Pin)
		{
			receiveCANMessage(1, &ID, &DLC, data);
		}

		osMutexRelease(SPIMutexHandle);
	}

	// TODO: write documentation on how to use this for the above code
	// this is not necessary, this was for testing
	#if 0
	if(ID == 0xCFCFCFC)
	{
	//	blueStatus = data[0];
		HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
	}
	else
	{
	//	greenStatus = data[0];
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	}

	osDelay(250);
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	#endif
}

// ---------------------------------------- For testing purposes ----------------------------------------

void CANRxInterruptTask_2(void* arg)
{
	for(;;) {
		CANRxInterrupt_2();
		osDelay(100);
	}
}

void CANRxInterrupt_2()
{
	uint16_t GPIO_Pin = 0;
	osMessageQueueGet(CAN2InterruptQueue, &GPIO_Pin, 0, osWaitForever);

	uint32_t ID = 0;
	uint8_t DLC = 0;
	uint8_t data[8] = {0};

	if (osMutexWait(SPI2MutexHandle, 0) == osOK)
	{
		if(GPIO_Pin == CAN2_RX0BF_Pin)
		{
			receiveCANMessage_2(0, &ID, &DLC, data);
		}
		else if (GPIO_Pin == CAN2_RX1BF_Pin)
		{
			receiveCANMessage_2(1, &ID, &DLC, data);
		}

		osMutexRelease(SPI2MutexHandle);
	}
}
