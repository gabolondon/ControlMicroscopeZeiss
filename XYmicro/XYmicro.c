#include "stm32f1xx_hal.h"

#define pinIN3 GPIO_PIN_11
#define pinIN4 GPIO_PIN_12
#define pinTA3 GPIO_PIN_2
#define pinArriba GPIO_PIN_3
#define pinIzquierda GPIO_PIN_4
#define pinTA1 GPIO_PIN_5
#define pinAbajo GPIO_PIN_6
#define pinTA4 GPIO_PIN_7
#define pinTA2 GPIO_PIN_8
#define pinDerecha GPIO_PIN_9
#define pinBtnCentrar GPIO_PIN_10
#define pinIN2 GPIO_PIN_1
#define pinIN1 GPIO_PIN_0

bool centrando = 0;
GPIO_PinState pinState;

void setup()
{
  HAL_Init();

  // Enable clock for GPIOA and GPIOB
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  // Configure digital outputs
  GPIO_InitStruct.Pin = pinIN1 | pinIN2 | pinIN3 | pinIN4;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Configure digital inputs with internal pull-up resistors
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;

  GPIO_InitStruct.Pin = pinTA3 | pinArriba | pinIzquierda | pinTA1 | pinAbajo | pinTA4 | pinTA2 | pinDerecha | pinBtnCentrar;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void loop()
{
  if (HAL_GPIO_ReadPin(GPIOB, pinBtnCentrar) == GPIO_PIN_RESET)
  {
    centrando = 0;
    printf("Boton Centrado pulsado, centrando...............\n");
    while (!centrando)
    {
      printf("Estado de: TA1: %d TA2: %d TA3: %d TA4: %d\n", HAL_GPIO_ReadPin(GPIOB, pinTA1), HAL_GPIO_ReadPin(GPIOB, pinTA2),
             HAL_GPIO_ReadPin(GPIOB, pinTA3), HAL_GPIO_ReadPin(GPIOB, pinTA4));

      if (HAL_GPIO_ReadPin(GPIOB, pinTA1) == GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOB, pinTA2) == GPIO_PIN_SET)
      {
        abajo();
      }
      else if (HAL_GPIO_ReadPin(GPIOB, pinTA1) == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOB, pinTA2) == GPIO_PIN_RESET)
      {
        arriba();
      }
      else
      {
        pararY();
      }

      if (HAL_GPIO_ReadPin(GPIOB, pinTA3) == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOB, pinTA4) == GPIO_PIN_RESET)
      {
        derecha();
      }
      else if (HAL_GPIO_ReadPin(GPIOB, pinTA3) == GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOB, pinTA4) == GPIO_PIN_SET)
      {
        izquierda();
      }
      else
      {
        pararX();
      }

      if (HAL_GPIO_ReadPin(GPIOA, pinDerecha) == GPIO_PIN_RESET || HAL_GPIO_ReadPin(GPIOB, pinIzquierda) == GPIO_PIN_RESET ||
          HAL_GPIO_ReadPin(GPIOB, pinAbajo) == GPIO_PIN_RESET || HAL_GPIO_ReadPin(GPIOB, pinArriba) == GPIO_PIN_RESET)
      {
        pararX();
        pararY();
        centrando = 1;
      }
    }
  }
  else
  {
    if (HAL_GPIO_ReadPin(GPIOB, pinArriba) == GPIO_PIN_RESET)
    {
      arriba();
    }
    if (HAL_GPIO_ReadPin(GPIOB, pinAbajo) == GPIO_PIN_RESET)
    {
      abajo();
    }
    if (HAL_GPIO_ReadPin(GPIOB, pinIzquierda) == GPIO_PIN_RESET)
    {
      izquierda();
    }
    if (HAL_GPIO_ReadPin(GPIOA, pinDerecha) == GPIO_PIN_RESET)
    {
      derecha();
    }
    if (HAL_GPIO_ReadPin(GPIOA, pinDerecha) == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOB, pinIzquierda) == GPIO_PIN_SET &&
        HAL_GPIO_ReadPin(GPIOB, pinAbajo) == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOB, pinArriba) == GPIO_PIN_SET)
    {
      pararX();
      pararY();
      HAL_Delay(100);
    }
  }
}

void derecha()
{
  HAL_GPIO_WritePin(GPIOA, pinIN1, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, pinIN2, GPIO_PIN_RESET);
  printf("Moviendo a la derecha...\n");
}

void izquierda()
{
  HAL_GPIO_WritePin(GPIOA, pinIN1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, pinIN2, GPIO_PIN_SET);
  printf("Moviendo a la izquierda...\n");
}

void arriba()
{
  HAL_GPIO_WritePin(GPIOA, pinIN3, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, pinIN4, GPIO_PIN_RESET);
  // Serial.println("Moviendo a la arriba...");
}

void abajo()
{
  HAL_GPIO_WritePin(GPIOA, pinIN3, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, pinIN4, GPIO_PIN_SET);
  printf("Moviendo a la abajo...\n");
}

void pararY()
{
  HAL_GPIO_WritePin(GPIOA, pinIN3, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, pinIN4, GPIO_PIN_RESET);
  printf("motores en Y detenidos\n");
}

void pararX()
{
  HAL_GPIO_WritePin(GPIOA, pinIN1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, pinIN2, GPIO_PIN_RESET);
  printf("motores en X detenidos\n");
}