/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "ringbuffer.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum OnOffState
{
	STATE_OFF = 0,
	STATE_ON = 1
};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

RingBuffer txrb;
RingBuffer rxrb;
enum OnOffState currentState = STATE_OFF;

#define WELCOME_MSG "Welcome from STM32\n\r\n\r"
#define MAIN_MENU "Available Options:\n\r"
#define OPTION1 "1. Start LED blinking\n\r"
#define OPTION2 "2. Stop LED blinking\n\r"
#define PROMPT "Select Option >\n\r"

int UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, size_t len)
{
	if (HAL_UART_Transmit_IT(huart, pData, len) != HAL_OK) {
		if (!RingBuffer_Write(&txrb, pData, len)) {
			return 0;
		}
	}
	return 1;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	uint8_t txData;
	if (!RingBuffer_IsEmpty(&txrb)) {
		RingBuffer_Read(&txrb, &txData, 1);
		HAL_UART_Transmit_IT(huart, &txData, 1);
	}
}

void printMessages(void) {
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)WELCOME_MSG, strlen(WELCOME_MSG));
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)MAIN_MENU, strlen(MAIN_MENU));
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)OPTION1, strlen(OPTION1));
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)OPTION2, strlen(OPTION2));
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)PROMPT, strlen(PROMPT));
}

void printMessages2(void) {
	UART_Transmit(&huart2, (uint8_t*)WELCOME_MSG, strlen(WELCOME_MSG));
	UART_Transmit(&huart2, (uint8_t*)MAIN_MENU, strlen(MAIN_MENU));
	UART_Transmit(&huart2, (uint8_t*)OPTION1, strlen(OPTION1));
	UART_Transmit(&huart2, (uint8_t*)OPTION2, strlen(OPTION2));
	UART_Transmit(&huart2, (uint8_t*)PROMPT, strlen(PROMPT));
}

/////////////////////////////////////////////////////////////////////////
// Led task definitions and functions
/////////////////////////////////////////////////////////////////////////

enum LedTaskState
{
	LedOn,
	LedOff,
};

enum LedTaskState ledState;
int ledCount;
int ledMaxCount;

void ledTask()
{
	if (ledState == LedOn)
	{
		if (ledCount++ >= ledMaxCount)
		{
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			ledCount = 0;
		}
	}
	else if (ledState == LedOff)
	{
		//HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
	}
}

void ledStart(int maxCount)
{
	ledState = LedOn;
	ledMaxCount = maxCount;
}

void ledStop()
{
	ledState = LedOff;
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
}

/////////////////////////////////////////////////////////////////////////
// Communication task definitions and functions
/////////////////////////////////////////////////////////////////////////

#define MAX_BUFFER_LENGTH 100

uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
int cmdcount = 0;
int cmdprint = 0;
uint8_t ch;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// in this callback we know that we have received the data
	if (ch == '\r')
	{
		// this is the end of the input
		// notify that we ready to handle new command
		cmdcount = RING_BUFFER_SIZE - RingBuffer_FreeSpace(&rxrb);
	}
	else
	{
		// put char to rx buffer
		if (RingBuffer_Write(&rxrb, &ch, 1) != 1)
		{
			// no more space in buffer, clear it
			RingBuffer_Init(&rxrb);
		}

		// we can echo it because echo will use interrupt and will not stop this interrupt
		UART_Transmit(&huart2, &ch, 1);
	}

	// clear error if we have
	if ((huart2.Instance->ISR & USART_ISR_ORE) != 0)
	{
		__HAL_UART_CLEAR_OREFLAG(&huart2);
	}

	// start reading again
	/*HAL_StatusTypeDef Status = */HAL_UART_Receive_IT(&huart2, &ch, 1);
}

int Communication_commTask()
{
	// just wait for interrupt to set cmdcount
	if (!cmdcount)
	{
		return 0;
	}

	// read the command in buffer
	RingBuffer_Read(&rxrb, cmdbuffer, cmdcount);

	//UART_Transmit(&huart2, cmdbuffer, cmdcount);

	// echo EOL
	UART_Transmit(&huart2, (uint8_t*)"\r\n", 2);

	// now we can notify that command is received
	cmdbuffer[cmdcount] = 0;
	cmdcount = 0;
	cmdprint = 0;
	return 1;
}

void Communication_handleCommand()
{
  char cmd[20];
  int maxCount;

  int params = sscanf((const char*)cmdbuffer, "%s %d", cmd, &maxCount);

  if (params == 0)
  {
	  return;
  }

  if (strcmp(cmd, "start") == 0)
  {
	  ledStart(maxCount);
  }
  else if (strcmp(cmd, "stop") == 0)
  {
	  ledStop();
  }
  else
  {
	  printf("Invalid command\r\n");
  }
}

/////////////////////////////////////////////////////////////////////////
// Redirecting printf to UART
/////////////////////////////////////////////////////////////////////////
int _write(int fd, char* ptr, int len) {
    //HAL_UART_Transmit(&huart2, (uint8_t *) ptr, len, HAL_MAX_DELAY);
	UART_Transmit(&huart2, (uint8_t *) ptr, len);
    return len;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  RingBuffer_Init(&txrb);
  RingBuffer_Init(&rxrb);

  printMessages2();

  //
  // start communication be receiving one byte
  /*HAL_StatusTypeDef Status = */HAL_UART_Receive_IT(&huart2, &ch, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  ledTask();
	  if (Communication_commTask())
	  {
		  Communication_handleCommand();
	  }

	  //int isButtonPressed = getButton();

	  switch (currentState)
	  {
//	  case STATE_OFF:
//		  if (isButtonPressed) {
//			  currentState = STATE_ON;
//		  }
//		  break;
//
//	  case STATE_ON:
//		  if (!isButtonPressed) {
//			  currentState = STATE_OFF;
//		  }
//		  break;
	  default:
		  // invalid state:
		  break;
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
