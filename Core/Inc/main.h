/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OLDE_CS_Pin GPIO_PIN_4
#define OLDE_CS_GPIO_Port GPIOA
#define T1_SCL_Pin GPIO_PIN_1
#define T1_SCL_GPIO_Port GPIOB
#define T1_SDA_Pin GPIO_PIN_2
#define T1_SDA_GPIO_Port GPIOB
#define T2_SCL_Pin GPIO_PIN_10
#define T2_SCL_GPIO_Port GPIOB
#define T2_SDA_Pin GPIO_PIN_11
#define T2_SDA_GPIO_Port GPIOB
#define KEY_MODE_Pin GPIO_PIN_12
#define KEY_MODE_GPIO_Port GPIOB
#define KEY_DOWN_Pin GPIO_PIN_13
#define KEY_DOWN_GPIO_Port GPIOB
#define KEY_UP_Pin GPIO_PIN_14
#define KEY_UP_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_15
#define BEEP_GPIO_Port GPIOB
#define FAN_CTTL_Pin GPIO_PIN_12
#define FAN_CTTL_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
