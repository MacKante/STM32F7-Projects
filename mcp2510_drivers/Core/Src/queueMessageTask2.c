#include "queueMessageTask.h"

void queueMessageTask2(void* arg) {
	CANMsg msg2 = {
		.DLC = 1,
		.ID = 0,
		.extendedID = 0xAFAFAFA,
		.data = {0xAA}
	};

	for(;;) {
		osStatus_t status = osMessageQueuePut(CANTxMessageQueue, &msg2, 0U, osWaitForever);
		if (status != osOK) {
			// do something
		}
		osDelay(1500);
	}
}
