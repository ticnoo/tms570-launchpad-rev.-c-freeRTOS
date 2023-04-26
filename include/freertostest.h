/** @file freertostest.h
 * 	@brief freeRTOS test task
 */

#ifndef freertostest_h
#define freertostest_h

#define UART scilinREG

#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"
#include "os_queue.h"

#include "het.h"
#include "gio.h"
#include "sci.h"
#include "het.h"

#include "string.h"
#include "stdlib.h"

extern char UART_data[7];
extern SemaphoreHandle_t uart_semaphore;

xQueueHandle xUARTData;
xTaskHandle xTaskUARTRx;
xTaskHandle xTaskUARTTx;

void vTaskUARTTx(void *pvParametres);
void vTaskUARTRx(void *pvParametres);
void vTaskBlinky (void *pvParameters);


#endif

