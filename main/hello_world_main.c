/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

uint32_t task4Count = 0;
uint32_t task5Count = 0;

void task0(void* params)
{
	int level = 0;
	uint32_t delay = (uint32_t)(params);


	while (true) {
		gpio_set_level(GPIO_NUM_23, level);
		level = !level;
		vTaskDelay(delay / portTICK_PERIOD_MS);
	}
}

void task1(void* params)
{
	int level = 0;
	uint32_t delay = (uint32_t)(params);


	while (true) {
		gpio_set_level(GPIO_NUM_22, level);
		level = !level;
		vTaskDelay(delay / portTICK_PERIOD_MS);
	}
}

void task2(void* params)
{
	int level = 0;
	uint32_t delay = (uint32_t)(params);


	while (true) {
		gpio_set_level(GPIO_NUM_21, level);
		level = !level;
		vTaskDelay(delay / portTICK_PERIOD_MS);
	}
}

void task3(void* params)
{
	int level = 0;
	uint32_t delay = (uint32_t)(params);


	while (true) {
		gpio_set_level(GPIO_NUM_19, level);
		level = !level;
		vTaskDelay(delay / portTICK_PERIOD_MS);
	}
}

void task4(void* params)
{

	while (true) {
		task4Count++;
		taskYIELD();
	}
}

void task5(void* params)
{
	while (true) {
		task5Count++;
		taskYIELD();
	}
}



void app_main()
{
	BaseType_t retVal;
	printf("Hello world!\n");

	uint32_t t4Count;
	uint32_t t5Count;

	gpio_set_direction(GPIO_NUM_23, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_NUM_22, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_NUM_21, GPIO_MODE_OUTPUT);
	gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
	if ((retVal = xTaskCreate(task0, "Task0", 1024, (void *)250, tskIDLE_PRIORITY, NULL)) != pdPASS)
	{
		printf("task create failed\n");
	}
	if ((retVal = xTaskCreate(task1, "Task1", 1024, (void *)500, tskIDLE_PRIORITY, NULL)) != pdPASS)
	{
		printf("task create failed\n");
	}
	if ((retVal = xTaskCreate(task2, "Task2", 1024, (void *)1000, tskIDLE_PRIORITY, NULL)) != pdPASS)
	{
		printf("task create failed\n");
	}
	if ((retVal = xTaskCreate(task3, "Task3", 1024, (void *)2000, tskIDLE_PRIORITY, NULL)) != pdPASS)
	{
		printf("task create failed\n");
	}
	if ((retVal = xTaskCreate(task4, "Task4", 1024, NULL, tskIDLE_PRIORITY, NULL)) != pdPASS)
	{
		printf("task create failed\n");
	}
	if ((retVal = xTaskCreate(task5, "Task5", 1024, NULL, tskIDLE_PRIORITY, NULL)) != pdPASS)
	{
		printf("task create failed\n");
	}

	while (true)
	{
		printf("main running\n");
		vTaskSuspendAll();
		t4Count = task4Count;
		t5Count = task5Count;
		xTaskResumeAll();
		printf("task4 count = %d\n", t4Count);
		printf("task5 count = %d\n", t5Count);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
