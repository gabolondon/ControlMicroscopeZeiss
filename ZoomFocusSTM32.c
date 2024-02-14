#include "stm32f1xx_hal.h"

ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

#define pinPOTfocus GPIO_PIN_7
#define pinPWMfocus GPIO_PIN_11
#define pinPOTzoom GPIO_PIN_6
#define pinPWMzoom GPIO_PIN_6
#define pinIN1 GPIO_PIN_7
#define pinIN2 GPIO_PIN_8
#define pinIN3 GPIO_PIN_9
#define pinIN4 GPIO_PIN_10
#define pinZoomUP GPIO_PIN_2
#define pinZoomDown GPIO_PIN_3
#define pinFocusDown GPIO_PIN_4
#define pinFocusUp GPIO_PIN_5

int valPWMfocus = 0;
int valPWMzoom = 0;

void setup()
{
  HAL_Init();
  SystemClock_Config();

  // Enable clock for GPIOA, GPIOB, and ADC1
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_ADC1_CLK_ENABLE();

  // Initialize ADC1
  ADC_Init();
  // Initialize PWM
  PWM_Init();

  // Configure digital outputs
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = pinIN1 | pinIN2 | pinIN3 | pinIN4;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Configure digital inputs with internal pull-up resistors
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;

  GPIO_InitStruct.Pin = pinZoomUP | pinZoomDown | pinFocusDown | pinFocusUp;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void loop()
{
  valPWMfocus = map(ADC_Read(pinPOTfocus), 0, 1023, 100, 255);
  printf("valor de PWM focus: %d\n", valPWMfocus);
  PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, valPWMfocus);

  valPWMzoom = map(ADC_Read(pinPOTzoom), 0, 1023, 100, 255);
  printf("valor de PWM zoom: %d\n", valPWMzoom);
  PWM_SetDutyCycle(&htim4, TIM_CHANNEL_1, valPWMzoom);

  if (HAL_GPIO_ReadPin(GPIOB, pinZoomUP) == GPIO_PIN_RESET)
  {
    printf("presionado pedal ZoomUP\n");
    zoomup();
  }
  if (HAL_GPIO_ReadPin(GPIOB, pinZoomDown) == GPIO_PIN_RESET)
  {
    printf("presionado pedal ZoomDOWN\n");
    zoomdown();
  }
  if (HAL_GPIO_ReadPin(GPIOB, pinFocusDown) == GPIO_PIN_RESET)
  {
    printf("presionado pedal FocusDOWN\n");
    focusdown();
  }
  if (HAL_GPIO_ReadPin(GPIOB, pinFocusUp) == GPIO_PIN_RESET)
  {
    printf("presionado pedal FocusUP\n");
    focusup();
  }
  if (HAL_GPIO_ReadPin(GPIOB, pinZoomUP) == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOB, pinZoomDown) == GPIO_PIN_SET)
  {
    pararzoom();
    HAL_Delay(100);
  }
  if (HAL_GPIO_ReadPin(GPIOB, pinFocusDown) == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOB, pinFocusUp) == GPIO_PIN_SET)
  {
    pararfocus();
    HAL_Delay(100);
  }
}

void zoomup()
{
  HAL_GPIO_WritePin(GPIOA, pinIN1, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, pinIN2, GPIO_PIN_RESET);
  printf("Moviendo zoom para arriba...\n");
}

void zoomdown()
{
  HAL_GPIO_WritePin(GPIOA, pinIN1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, pinIN2, GPIO_PIN_SET);
  printf("Moviendo zoom para abajo...\n");
}

void focusup()
{
  HAL_GPIO_WritePin(GPIOA, pinIN3, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, pinIN4, GPIO_PIN_RESET);
  printf("moviendo focus para arriba...\n");
}

void focusdown()
{
  HAL_GPIO_WritePin(GPIOA, pinIN3, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, pinIN4, GPIO_PIN_SET);
  printf("Moviendo focus para abajo...\n");
}

void pararzoom()
{
  HAL_GPIO_WritePin(GPIOA, pinIN1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, pinIN2, GPIO_PIN_RESET);
  printf("motores zoom detenidos\n");
}

void pararfocus()
{
  HAL_GPIO_WritePin(GPIOA, pinIN3, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, pinIN4, GPIO_PIN_RESET);
  printf("motores focus detenidos\n");
}

void ADC_Init()
{
  ADC_ChannelConfTypeDef sConfig;
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;

  HAL_ADC_Init(&hadc1);

  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;

  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

uint16_t ADC_Read(uint32_t channel)
{
  ADC_ChannelConfTypeDef sConfig;
  sConfig.Channel = channel;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;

  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
  uint16_t value = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);

  return value;
}

void PWM_Init()
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_TIM4_CLK_ENABLE();

  // Configure PWM GPIO pins
  GPIO_InitStruct.Pin = pinPWMfocus;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = pinPWMzoom;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Configure PWM timers
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 71; // Timer 3 clock frequency = 72MHz / (71+1) = 1MHz
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 255; // 1MHz / (255+1) = 3.9kHz
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&htim3);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 71; // Timer 4 clock frequency = 72MHz / (71+1) = 1MHz
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 255; // 1MHz / (255+1) = 3.9kHz
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&htim4);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);

  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  // Configure the main internal regulator output voltage
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  // Initializes the CPU, AHB and APB busses clocks
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  // Initializes the CPU, AHB and APB busses clocks
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  // Configure the Systick interrupt time
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

  // Configure the Systick
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}
