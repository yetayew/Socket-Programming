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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_DMA_ACCESS_COUNT	(40960)

#define DMA_READ_SIZE	(128)

#define BUFFER_COUNT	(4)

#define STATE_STOP				1
#define STATE_RECORDING			2
#define STATE_START_RECORDING	3
#define STATE_PLAYING			4
typedef union {
	uint32_t w;
	char b[4];
} _WORD;
typedef union  {
	uint16_t hw;
	char b[2];
} _HALF_WORD;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 I2S_HandleTypeDef hi2s2;
I2S_HandleTypeDef hi2s3;
DMA_HandleTypeDef hdma_spi2_rx;
DMA_HandleTypeDef hdma_spi3_tx;

RTC_HandleTypeDef hrtc;

SD_HandleTypeDef hsd;
DMA_HandleTypeDef hdma_sdio_rx;
DMA_HandleTypeDef hdma_sdio_tx;

/* USER CODE BEGIN PV */
uint16_t DMA_TxRx_SIZE = DMA_READ_SIZE*2;
static uint16_t rcvBuf[DMA_READ_SIZE*2*BUFFER_COUNT];
static uint32_t rCount=0, wCount=0;
static uint8_t audio_state = STATE_STOP;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SDIO_SD_Init(void);
static void MX_DMA_Init(void);
static void MX_I2S2_Init(void);
static void MX_RTC_Init(void);
static void MX_I2S3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
typedef struct _WaveHeader{
	char riff[4];
	uint32_t size;
	char wave[4];
	char fmt[4];
	uint32_t fmt_size;
	uint16_t format; //1:PCM
	uint16_t channels; // channels
	uint32_t sampleRate;  // sample rate
	uint32_t rbc;//sampleRate*bitsPerSample*channels/8
	uint16_t bc; //bitsPerSample*channels/8
	uint16_t bitsPerSample; //bitsPerSample
	char data[4];
	uint32_t data_size;
} WAVE_HEADER;

void convertEndian(char* sd_path, char *file_in, char *file_out) {
	WAVE_HEADER wave_header;
	FRESULT res;
	FIL fin, fout;
	char fn[256];
	UINT bw, br;
	uint16_t bitsSample;
	uint8_t readBytes;
	_WORD *w_data;
	_HALF_WORD *h_data;

	  //res = f_mount(&SDFatFS, SDPath, 0);
	sprintf(fn, "%s%s", sd_path, file_in);
	res = f_open(&fin, fn, FA_OPEN_EXISTING|FA_READ);
	sprintf(fn, "%s%s", sd_path, file_out);
	res = f_open(&fout, fn, FA_CREATE_ALWAYS|FA_WRITE);
	f_read(&fin, (uint8_t*)&wave_header, sizeof(wave_header), &br);

	  bitsSample= wave_header.bitsPerSample;
	  if (bitsSample == 32) {
		  w_data = (_WORD*)malloc(512);
	  } else if (bitsSample == 16){
		  h_data = (_HALF_WORD*)malloc(512);
	  } else {
		  return;
	  }


	  f_write(&fout, (uint8_t*)&wave_header, sizeof(wave_header), &bw);
	  for (int i=0; i < wave_header.data_size; i+=512) {
		  if (bitsSample == 32) {
			  f_read(&fin, (uint8_t*)w_data, 512, &br);
			  for (int i = 0; i < br/4; i++) {
				  w_data[i].w = w_data[i].b[0] << 24 | w_data[i].b[1] << 16 | w_data[i].b[2] << 8 | w_data[i].b[3];
			  }
			  f_write(&fout, (uint8_t*)(w_data), br, &bw);
		  }
		  else {
			  f_read(&fin, (uint8_t*)h_data, 512, &br);
			  for (int i = 0; i < br/2; i++) {
				  h_data[i].hw = h_data[i].b[0] << 8 | h_data[i].b[1];
			  }
			  f_write(&fout, (uint8_t*)(h_data), br, &bw);
		  }
	  }
	  f_close(&fout);
	  f_close(&fin);
}


uint8_t txCplt = 0;

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s) {
	txCplt=1;
}
uint8_t rcvCplt = 0;
uint16_t* rpt, *wpt, *temppt;
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s){
	rCount++;
	rpt = (rcvBuf)+(rCount%BUFFER_COUNT)*DMA_TxRx_SIZE;
	HAL_I2S_Receive_DMA(hi2s, rpt, DMA_READ_SIZE);
}

FRESULT fwrite_wav_header(FIL* file, uint16_t sampleRate, uint8_t bitsPerSample, uint8_t channels) {
	UINT bw;
	WAVE_HEADER wave_header;
	wave_header.riff[0] = 'R';wave_header.riff[1] = 'I';
	wave_header.riff[2] = 'F';wave_header.riff[3] = 'F';
	wave_header.size = (uint32_t)0;
	wave_header.wave[0] = 'W';wave_header.wave[1] = 'A';
	wave_header.wave[2] = 'V';wave_header.wave[3] = 'E';
	wave_header.fmt[0] = 'f';wave_header.fmt[1] = 'm';
	wave_header.fmt[2] = 't';wave_header.fmt[3] = ' ';
	wave_header.fmt_size = 16;
	wave_header.format = 1; // PCM
	wave_header.channels = channels; // channels
	wave_header.sampleRate=sampleRate;  // sample rate
	wave_header.rbc = sampleRate*bitsPerSample*2/8;
	wave_header.bc =  bitsPerSample*2/8;
	wave_header.bitsPerSample = bitsPerSample; //bitsPerSample
	wave_header.data[0] = 'd'; wave_header.data[1] = 'a';
	wave_header.data[2] = 't'; wave_header.data[3] = 'a';
	wave_header.data_size = 0;
	return f_write(file, (uint8_t*)&wave_header, sizeof(wave_header), &bw);
}

void startRecord(char *filename) {
	UINT bw;
	UINT writeBytes;
	UINT skipCount=125;// skip 0.5 second
	FIL fp;
	FRESULT res;

	writeBytes = DMA_TxRx_SIZE*2;
	res = f_open(&fp, filename, FA_CREATE_ALWAYS|FA_WRITE);
	res = fwrite_wav_header(&fp, 16000, 32, 2);

	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	audio_state = STATE_RECORDING;
	rpt = rcvBuf;
	wpt = rpt;
	rCount=0; wCount=0;
	HAL_I2S_Receive_DMA(&hi2s2, rpt, DMA_READ_SIZE);

	while (1)
	{
		if (wCount < rCount ) {
			if (rCount > skipCount)
			{
				res = f_write(&fp, wpt, writeBytes, &bw);
			}
			 wCount++;
			 wpt = (rcvBuf)+(wCount%BUFFER_COUNT)*DMA_TxRx_SIZE;
		  }

		  if (audio_state == STATE_STOP || rCount > MAX_DMA_ACCESS_COUNT)
		  {
			  HAL_I2S_DMAStop(&hi2s2);
			  break;
		  }
	}
	uint32_t data_len = (wCount-1) * writeBytes;
	uint32_t total_len = data_len+36;
	f_lseek(&fp, 4);
	f_write(&fp, (uint8_t*)&total_len, 4, &bw);
	f_lseek(&fp, 40);
	f_write(&fp, (uint8_t*)&data_len, 4, &bw);
	f_close(&fp);
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
	audio_state = STATE_STOP;
}
void startPlay(char *filename) {

	FIL fp;
	WAVE_HEADER wave_header;
	UINT br;

	uint16_t *readpt, *writept, *temppt;
	FRESULT res;

	res = f_open(&fp, filename, FA_OPEN_EXISTING|FA_READ);

	res = f_read(&fp, (uint8_t*)&wave_header, sizeof(wave_header), &br);
	if (br != sizeof(wave_header)) {f_close(&fp);return; }

	audio_state = STATE_PLAYING;
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);

	readpt = rcvBuf;
	writept = (rcvBuf)+DMA_TxRx_SIZE;
	  txCplt=0;
	  f_read(&fp, (uint8_t*)readpt, DMA_TxRx_SIZE*2, &br);
	  temppt=writept;
	  writept=readpt;
	  readpt=temppt;
	  HAL_I2S_Transmit_DMA(&hi2s3, (uint16_t*)writept, DMA_READ_SIZE);
	  uint32_t *tu;
	  while (1) {
		  res = f_read(&fp, (uint8_t*)readpt, DMA_TxRx_SIZE*2, &br);
		  for (int i = 0; i < DMA_TxRx_SIZE; i+=2) {
			tu = (uint32_t*)&readpt[i];
			*tu = ((*tu)&0x80000000) | (((*tu) << 3)&0x7FFFFFFF);
		}

		  while(!txCplt) ;
		  txCplt=0;
		  temppt=writept;
		  writept=readpt;
		  readpt=temppt;

		  HAL_I2S_Transmit_DMA(&hi2s3, (uint16_t*)writept, DMA_READ_SIZE);
		  if (br < DMA_TxRx_SIZE*2) break;
	  }


	  HAL_I2S_DMAStop(&hi2s3);

	  f_close(&fp);
	  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	  audio_state = STATE_STOP;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == BUTTON_Pin) {
		switch (audio_state) {
		case STATE_STOP:
			audio_state = STATE_START_RECORDING;
			break;
		case STATE_RECORDING:
			audio_state = STATE_STOP;
			break;
		case STATE_PLAYING:
			break;
		case STATE_START_RECORDING:
			break;
		default:
			audio_state = STATE_STOP;
			break;
		}

	}
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

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SDIO_SD_Init();
  MX_DMA_Init();
  MX_FATFS_Init();
  MX_I2S2_Init();
  MX_RTC_Init();
  MX_I2S3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  FRESULT res;
  char filename[256];
  res = f_mount(&SDFatFS, SDPath, 0);

  uint16_t count;
   while (1)
  {
	    if (audio_state == STATE_START_RECORDING) {
	  		  HAL_Delay(1);
	  		  sprintf(filename, "%sr_%05d.wav", SDPath, count++);
	  		  startRecord(filename);

	  		  HAL_Delay(1000);
	  		  startPlay(filename);

	  	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  f_mount(&SDFatFS, "", 0);

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 50;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2S2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S2_Init(void)
{

  /* USER CODE BEGIN I2S2_Init 0 */

  /* USER CODE END I2S2_Init 0 */

  /* USER CODE BEGIN I2S2_Init 1 */

  /* USER CODE END I2S2_Init 1 */
  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_RX;
  hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_32B;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_16K;
  hi2s2.Init.CPOL = I2S_CPOL_LOW;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S2_Init 2 */
  //hi2s2.Instance->CR1 = hi2s2.Instance->CR1 | SPI_CR1_LSBFIRST;
  /* USER CODE END I2S2_Init 2 */

}

/**
  * @brief I2S3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S3_Init(void)
{

  /* USER CODE BEGIN I2S3_Init 0 */

  /* USER CODE END I2S3_Init 0 */

  /* USER CODE BEGIN I2S3_Init 1 */

  /* USER CODE END I2S3_Init 1 */
  hi2s3.Instance = SPI3;
  hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s3.Init.DataFormat = I2S_DATAFORMAT_32B;
  hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_16K;
  hi2s3.Init.CPOL = I2S_CPOL_LOW;
  hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S3_Init 2 */
  //hi2s3.Instance->CR1 = hi2s3.Instance->CR1 | SPI_CR1_LSBFIRST;
  /* USER CODE END I2S3_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
if (0) {
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0;
  sTime.Minutes = 0;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_MARCH;
  sDate.Date = 6;
  sDate.Year = 22;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
}
  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SDIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDIO_SD_Init(void)
{

  /* USER CODE BEGIN SDIO_Init 0 */

  /* USER CODE END SDIO_Init 0 */

  /* USER CODE BEGIN SDIO_Init 1 */

  /* USER CODE END SDIO_Init 1 */
  hsd.Instance = SDIO;
  hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
  hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
  hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
  hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
  hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd.Init.ClockDiv = 0;
  /* USER CODE BEGIN SDIO_Init 2 */

  /* USER CODE END SDIO_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA2_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
  /* DMA2_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

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
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_RED_Pin LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

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