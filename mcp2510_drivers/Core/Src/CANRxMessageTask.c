/*
 * CANRxInterruptTask.c
 *
 *  Created on: Feb 10, 2024
 *      Author: MacKante
 */

#include <CANRxMessageTask.h>

void CANRxMessageTask(void* arg)
{
	for(;;) {
		CANRxInterrupt();
	}
}

void CANRxMessage()
{
	CAN_RX_Channel channel;
	osStatus_t status = osMessageQueueGet(CANRxMessageQueue, &channel, 0, osWaitForever);

	// add a switch case on where to send this
	uint32_t ID = 0;
	uint8_t DLC = 0;
	uint8_t data[8] = {0};

	if (osMutexWait(SPIMutexHandle, 0) == osOK)
	{
		receiveCANMessage(channel.pin, &ID, &DLC, data, &peripheral);
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
