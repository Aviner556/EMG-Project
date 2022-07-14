#include <main.h>
#include <codes.h>
#include "stdio.h"
#include <LED.h>

extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim3;
extern Led blue;
extern Led red;


uint8_t errorCnt[1] = {0};
uint32_t checkCode;
int flag3error = 0, flag5error = 0;

void setCode(uint32_t mainCode)
{
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x10, 1, (uint8_t *)&mainCode, sizeof(mainCode), 0Xff);
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x14, 1, errorCnt, sizeof(errorCnt), 0Xff);
	printf("code determined\r\n");
}


void errorCode(uint32_t pass)
{
	HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x14, 1, errorCnt, sizeof(errorCnt), 0Xff);
	errorCnt[0] += 1;
	printf("attempts: %d\r\n",errorCnt[0]);
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x14, 1, errorCnt, sizeof(errorCnt), 0Xff);
 	if(errorCnt[0] == 3){
		flag3error = 1;
	}
	else if(errorCnt[0] >= 5){
		flag3error = 0;
		flag5error = 1;
	}
 	if(flag3error == 1){
		printf("wait 15 seconds before trying again\r\n");
 	}
 	else if(flag5error >= 1){
 		printf("wait 5 minutes before trying again\r\n");
 	}
}


void getCode(uint32_t pass)
{
	HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x10, 1, (uint8_t *)&checkCode, sizeof(checkCode), 0Xff);
	if(checkCode == pass){
		Led_on(&blue);
		Led_off(&red);
		printf("permission granted\r\n");

		errorCnt[0] = 0;
		HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x14, 1, errorCnt, sizeof(errorCnt), 0Xff);
		flag3error = 0;
		flag5error = 0;
	}
	else{
		errorCode(pass);
		Led_on(&red);
		Led_off(&blue);
		HAL_TIM_Base_Start(&htim3);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

		printf("wrong password\r\n");
	}
}
