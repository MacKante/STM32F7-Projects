#pragma once

#include "main.h"
#include <stdint.h>
#include "cmsis_os.h"
#include "CANRegisters.h"

typedef struct {
    uint8_t DLC;
    uint16_t ID;
    uint64_t extendedID;
    uint8_t data[8];
} CANMsg;

typedef struct {
    GPIO_TypeDef *CS_PORT;
    uint16_t CS_PIN;
    SPI_HandleTypeDef *hspi;
} CANPeripheral;

#define TX_CHANNEL_CHECK_DELAY 1

#define CAN_TEST_SETUP 1

void CAN_IC_READ_REGISTER(uint8_t address, uint8_t* buffer, CANPeripheral *peripheral);
void CAN_IC_WRITE_REGISTER_BITWISE(uint8_t address, uint8_t mask, uint8_t value, CANPeripheral *peripheral);
void CAN_IC_WRITE_REGISTER(uint8_t address, uint8_t value, CANPeripheral *peripheral);
void ConfigureCANSPI(CANPeripheral *peripheral);
uint8_t sendCANMessage(CANMsg *msg, CANPeripheral *peripheral);
uint8_t sendExtendedCANMessage(CANMsg *msg, CANPeripheral *peripheral);
void receiveCANMessage(uint8_t channel, uint32_t* ID, uint8_t* DLC, uint8_t* data, CANPeripheral *peripheral);
uint8_t checkAvailableTXChannel(CANPeripheral *peripheral);

extern uint8_t canReceive;

extern SPI_HandleTypeDef hspi1;
extern osMutexId_t SPIMutexHandle;
extern osMessageQueueId_t CANInterruptQueue;
extern osMessageQueueId_t CANTxMessageQueue;

extern uint8_t blueStatus;
extern uint8_t greenStatus;

// https://www.codesdope.com/blog/article/making-a-queue-using-linked-list-in-c/
