#include "fs_task.h"
#include "stm32f2xx.h"
#include "BA_board.h"
#include "task.h"
#include <stdlib.h>
#include "fileSystem.h"

static FS fileSystem;

static void FSTaskFunc(void *pParams);

void setupFS() {

}

void FSHardwareInit(void *pParam) {
	reset_sector(0);
	f_mount(&fileSystem, 0, 0);
	f_mkfs(0);
	f_mount(&fileSystem, 0, 1);
}

void FSStartTask(unsigned short nStackDepth, unsigned portBASE_TYPE nPriority,
		void *pParams) {
	xTaskCreate(FSTaskFunc, "FS", nStackDepth, pParams, nPriority, NULL);
}

void read_file() {
	FS fileSystem;
	FIL fp;
	BYTE buff[40];
	f_mount(&fileSystem, 0, 1);
	f_open(&fp, "ex1.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

	int i;
	UINT readed = 0;
	for (i = 0; i < 4; i++) {
		f_read(&fp, &buff, 37, &readed);
	}
}

// FS
void test_FS() {
	FIL fp;

	f_open(&fp, "ex1.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

	Delay(500);
	GPIO_ResetBits(LEDS_GPIO_PORT, LEDR_PIN);
	Delay(500);
	GPIO_SetBits(LEDS_GPIO_PORT, LEDR_PIN);

	uint8_t toWrite[100];
	uint8_t toRead[100];
	int i;
	UINT writed, readed;
	for (i = 0; i < 100; i++) {
		toWrite[i] = '2';
		toRead[i] = '1';
	}

	Delay(500);
	GPIO_ResetBits(LEDS_GPIO_PORT, LEDR_PIN);
	Delay(500);
	GPIO_SetBits(LEDS_GPIO_PORT, LEDR_PIN);

	for (i = 0; i < 100; i++) {
		f_write(&fp, toWrite, 100, &writed);
	}

	Delay(500);
	GPIO_ResetBits(LEDS_GPIO_PORT, LEDR_PIN);
	Delay(500);
	GPIO_SetBits(LEDS_GPIO_PORT, LEDR_PIN);

	f_close(&fp);

	Delay(500);
	GPIO_ResetBits(LEDS_GPIO_PORT, LEDR_PIN);
	Delay(500);
	GPIO_SetBits(LEDS_GPIO_PORT, LEDR_PIN);

	f_open(&fp, "ex1.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

	for (i = 0; i < 100; i++) {
		f_read(&fp, toRead, 100, &readed);
	}

	Delay(500);
	GPIO_ResetBits(LEDS_GPIO_PORT, LEDR_PIN);
	Delay(500);
	GPIO_SetBits(LEDS_GPIO_PORT, LEDR_PIN);

	f_close(&fp);

	Delay(500);
	GPIO_ResetBits(LEDS_GPIO_PORT, LEDR_PIN);
	Delay(500);
	GPIO_SetBits(LEDS_GPIO_PORT, LEDR_PIN);
}

void FSTaskFunc(void *pParams) {

	FSHardwareInit(pParams);
	Delay(2000);

	while (1) {
		test_FS();
	}

}