#include "freertostest.h"

/** @fn void vTaskUARTTx(void *pvParametres)
 *  @brief UART Transmit + param task
 *
 * 	Take parameters from the queue, decrypt it, change parameters 
 * 	and send params back via UART 
 * 
 */


void vTaskUARTTx(void *pvParametres)
{

	char pwm_duty_buff[40] = "PWM set duty: ";
	char config_buff[50] = "CONFIG:\n\rLED - ";
	char UARTRx_buff[7];
	bool led = 0;
	bool pwm = 1;
	char duty[3] = "50";

	for(;;)
	{
		
		xQueueReceive(xUARTData, UARTRx_buff, portMAX_DELAY);

		
		if (strncmp(UARTRx_buff, "LED", 3) == 0)
	    {
			if (strncmp(UARTRx_buff+4, "ON", 2) == 0)
			{
				gioSetBit(gioPORTA, 2, 1);
				led = 1;
				sciSend(UART, 8, "LED ON\n\r");
			}
			else if (strncmp(UARTRx_buff+4, "OFF", 2) == 0)
			{
				gioSetBit(gioPORTA, 2, 0);
				led = 0;
				sciSend(UART, 9, "LED OFF\n\r");
			}
	    	
		}
		else if (strncmp(UARTRx_buff, "PWM", 3) == 0)
		{
			if (strncmp(UARTRx_buff+4, "ON", 2) == 0)
			{
				pwmStart(hetRAM1, pwm0);
				pwm = 1;
				sciSend(UART, 8, "PWM ON\n\r");
			}
			else if (strncmp(UARTRx_buff+4, "OFF", 3) == 0)
			{
				pwmStop(hetRAM1, pwm0);
				pwm = 0;
				sciSend(UART, 9, "PWM OFF\n\r");
			}
			else
			{
				memset(duty, '\0', 3);
				strncat(duty, UARTRx_buff+4, 3);
				pwmSetDuty(hetRAM1, pwm0, strtol(UARTRx_buff+4, NULL, 10));
				memset(pwm_duty_buff+14, '\0', 5);
				strcat(pwm_duty_buff, duty);
				strcat(pwm_duty_buff, "\n\r");
				sciSend(UART, 20, (uint8_t*) pwm_duty_buff);
			}
			
		}
		else if (strncmp(UARTRx_buff, "CONFIG", 6) == 0)
		{
			memset(config_buff+15, '\0', 30);
			if (led)
			{
				strcat(config_buff, "ON \n\r");
			}
			else
			{
				strcat(config_buff, "OFF\n\r");
			}
			strcat(config_buff, "PWM - ");
			if (pwm)
			{
				strcat(config_buff, "ON \n\r");
			}
			else
			{
				strcat(config_buff, "OFF\n\r");
			}
			strcat(config_buff, "PWM duty - ");
			strcat(config_buff, duty);
			strcat(config_buff, "\n\r");

			sciSend(UART, strlen(config_buff), (uint8_t*) config_buff);
		}


	}
}

