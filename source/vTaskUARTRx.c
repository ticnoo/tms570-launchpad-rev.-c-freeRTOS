#include "freertostest.h"


/** @fn void vTaskUARTRx(void *pvParametres)
 *  @brief UART Resive task
 *
 * 	Recive data, add it to queue, start new UART reacive 
 * 
 */

void vTaskUARTRx(void *pvParametres)
{
	for(;;)
	{
		xSemaphoreTake(uart_semaphore, portMAX_DELAY);

		xQueueSendToBack(xUARTData, UART_data, portMAX_DELAY);


		sciReceive(UART, 7, (uint8_t*) UART_data);
	}
}
