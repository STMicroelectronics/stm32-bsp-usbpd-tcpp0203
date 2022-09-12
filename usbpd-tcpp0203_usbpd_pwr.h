/**
  ******************************************************************************
  * @file    usbpd-tcpp0203_usbpd_pwr.h
  * @author  MCD Application Team
  * @brief   Header file for usbpd-tcpp0203_usbpd_pwr.c file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef USBPD_TCPP0203_USBPD_PWR_H
#define USBPD_TCPP0203_USBPD_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbpd-tcpp0203_conf.h"

#if defined(USE_STM32G4XX_NUCLEO)
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_exti.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_nucleo_errno.h"
#elif defined(USE_STM32G0XX_NUCLEO)
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_system.h"
/* STM32G0 series using BSP V1 framework, no conf template file, no error definitions, ... */
#include "usbpd-tcpp0203_errno.h"
#else
#warning "Please select include files according to HW setup"
#endif /* USE_STM32G4XX_NUCLEO */

#include "usbpd-tcpp0203_conf.h"
/* Include TCPP0203 component driver */
#include "../Components/tcpp0203/tcpp0203.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup USBPD-TCPP0203
  * @{
  */

/** @addtogroup USBPD-TCPP0203_USBPD_PWR
  * @{
  */

/** @defgroup USBPD-TCPP0203_USBPD_PWR_Exported_Types Exported Types
  * @{
  */

/**
  * @brief  Power role
  */
typedef enum
{
  POWER_ROLE_SOURCE = 0,
  POWER_ROLE_SINK,
  POWER_ROLE_DUAL
} USBPD_PWR_PowerRoleTypeDef;

/**
  * @brief  Low Power Mode of TypeC ports
  */
typedef enum
{
  USBPD_PWR_MODE_OFF = 0,
  USBPD_PWR_MODE_HIBERNATE,
  USBPD_PWR_MODE_LOWPOWER,
  USBPD_PWR_MODE_NORMAL
} USBPD_PWR_PowerModeTypeDef;

/**
  * @brief  VBUS connection status
  */
typedef enum
{
  VBUS_CONNECTED = 0,
  VBUS_NOT_CONNECTED
} USBPD_PWR_VBUSConnectionStatusTypeDef;

/**
  * @brief  ADC buffer identifiers
  */
typedef enum
{
  ADCBUF_VSENSE = 0,
  ADCBUF_ISENSE
} USBPD_PWR_ADCBufIDTypeDef;

/**
  * @brief VBUS Detection Callback
  */
typedef void USBPD_PWR_VBUSDetectCallbackFunc(uint32_t PortNum,
                                              USBPD_PWR_VBUSConnectionStatusTypeDef VBUSConnectionStatus);

/**
  * @}
  */

/** @defgroup USBPD-TCPP0203_USBPD_PWR_Exported_Constants Exported Constants
  * @{
  */
/**
  * @brief  HW configuration type of TypeC ports
  */
#define USBPD_PWR_HW_CONFIG_TYPE_DEFAULT          (0U)       /*!< Default configuration :
                                                                  Port available natively on board, no protection  */
#define USBPD_PWR_HW_CONFIG_TYPE_TCPP01           (1U)       /*!< TypeC Port protection available
                                                                  thanks to a TCPP01 component                     */
#define USBPD_PWR_HW_CONFIG_TYPE_TCPP02           (2U)       /*!< TypeC Port protection available
                                                                  thanks to a TCPP02 component                     */
#define USBPD_PWR_HW_CONFIG_TYPE_TCPP03           (3U)       /*!< TypeC Port protection available
                                                                  thanks to a TCPP03 component                     */


/**
  * @brief  Number of TypeC ports
  */
#define USBPD_PWR_INSTANCES_NBR           (1U)

/**
  * @brief  Type-C port identifier
  */
#define USBPD_PWR_TYPE_C_PORT_1           (0U)
#define USBPD_PWR_TYPE_C_PORT_2           (1U)
#define USBPD_PWR_TYPE_C_PORT_3           (2U)

/**
  * @brief  CC pin identifier
  */
#define USBPD_PWR_TYPE_C_CC1              (1U)
#define USBPD_PWR_TYPE_C_CC2              (2U)

/**
  * @brief  VBUS disconnection threshold values (in mV)
  */
#define USBPD_PWR_HIGH_VBUS_THRESHOLD     (2800U)
#define USBPD_PWR_LOW_VBUS_THRESHOLD      (750U)
#define USBPD_PWR_VBUS_THRESHOLD_5V       (3900U)
#define USBPD_PWR_VBUS_THRESHOLD_9V       (7000U)
#define USBPD_PWR_VBUS_THRESHOLD_15V      (12500U)
#define USBPD_PWR_VBUS_THRESHOLD_20V      (17000U)
#define USBPD_PWR_VBUS_THRESHOLD_APDO     (2150U)

/**
  * @brief  VBUS discharge parameters
  */
#define USBPD_PWR_DISCHARGE_MARGIN        (500U)
#define USBPD_PWR_DISCHARGE_TIME          (6U)

/**
  * @brief  Standard VBUS voltage levels
  */
#define USBPD_PWR_VBUS_5V                 5000U
#define USBPD_PWR_VBUS_9V                 9000U
#define USBPD_PWR_VBUS_15V                15000U

/**
  * @brief  power timeout
  */
#define USBPD_PWR_TIMEOUT_PDO             250U         /* Timeout for PDO to PDO or PDO to APDO at 250ms */
#define USBPD_PWR_TIMEOUT_APDO            25U          /* Timeout for APDO to APDO at 25ms */

/**
  * @brief  Invalid value set during issue with voltage setting
  */
#define USBPD_PWR_INVALID_VALUE           0xFFFFFFFFU

/**
  * @}
  */

/** @addtogroup USBPD-TCPP0203_USBPD_PWR_Exported_Variables
  * @{
  */
/**
  * @}
  */

/** @defgroup USBPD-TCPP0203_USBPD_PWR_Exported_Functions Exported Functions
  * @{
  */
/* Common functions */
int32_t BSP_USBPD_PWR_Init(uint32_t PortNum);
int32_t BSP_USBPD_PWR_Deinit(uint32_t PortNum);

int32_t BSP_USBPD_PWR_SetRole(uint32_t PortNum, USBPD_PWR_PowerRoleTypeDef Role);
int32_t BSP_USBPD_PWR_SetPowerMode(uint32_t PortNum, USBPD_PWR_PowerModeTypeDef PwrMode);
int32_t BSP_USBPD_PWR_GetPowerMode(uint32_t PortNum, USBPD_PWR_PowerModeTypeDef *PwrMode);

int32_t BSP_USBPD_PWR_VBUSInit(uint32_t PortNum);
int32_t BSP_USBPD_PWR_VBUSDeInit(uint32_t PortNum);

int32_t BSP_USBPD_PWR_VBUSOn(uint32_t PortNum);
int32_t BSP_USBPD_PWR_VBUSOff(uint32_t PortNum);
int32_t BSP_USBPD_PWR_VBUSIsOn(uint32_t PortNum, uint8_t *pState);

int32_t BSP_USBPD_PWR_VBUSSetVoltage_Fixed(uint32_t PortNum, uint32_t VbusTargetInmv, uint32_t OperatingCurrent,
                                           uint32_t MaxOperatingCurrent);
int32_t BSP_USBPD_PWR_VBUSSetVoltage_Variable(uint32_t PortNum, uint32_t VbusTargetMaxInmv,
                                              uint32_t VbusTargetMinInmv, uint32_t OperatingCurrent,
                                              uint32_t MaxOperatingCurrent);
int32_t BSP_USBPD_PWR_VBUSSetVoltage_Battery(uint32_t PortNum, uint32_t VbusTargetMin, uint32_t VbusTargetMax,
                                             uint32_t OperatingPower, uint32_t MaxOperatingPower);
int32_t BSP_USBPD_PWR_VBUSSetVoltage_APDO(uint32_t PortNum, uint32_t VbusTargetInmv, uint32_t OperatingCurrent,
                                          int32_t Delta);

int32_t BSP_USBPD_PWR_SetVBUSDisconnectionThreshold(uint32_t PortNum, uint32_t VoltageThreshold);

int32_t BSP_USBPD_PWR_RegisterVBUSDetectCallback(uint32_t PortNum,
                                                 USBPD_PWR_VBUSDetectCallbackFunc *pfnVBUSDetectCallback);

int32_t BSP_USBPD_PWR_VBUSGetVoltage(uint32_t PortNum, uint32_t *pVoltage);
int32_t BSP_USBPD_PWR_VBUSGetCurrent(uint32_t PortNum, int32_t *pCurrent);

int32_t BSP_USBPD_PWR_VBUSDischargeOn(uint32_t PortNum);
int32_t BSP_USBPD_PWR_VBUSDischargeOff(uint32_t PortNum);

int32_t BSP_USBPD_PWR_VCONNInit(uint32_t PortNum, uint32_t CCPinId);
int32_t BSP_USBPD_PWR_VCONNDeInit(uint32_t PortNum, uint32_t CCPinId);

int32_t BSP_USBPD_PWR_VCONNOn(uint32_t PortNum, uint32_t CCPinId);
int32_t BSP_USBPD_PWR_VCONNOff(uint32_t PortNum, uint32_t CCPinId);
int32_t BSP_USBPD_PWR_VCONNIsOn(uint32_t PortNum, uint32_t CCPinId, uint8_t *pState);

int32_t BSP_USBPD_PWR_VCONNDischargeOn(uint32_t PortNum);
int32_t BSP_USBPD_PWR_VCONNDischargeOff(uint32_t PortNum);

void    BSP_USBPD_PWR_EventCallback(uint32_t PortNum);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* USBPD_TCPP0203_USBPD_PWR_H */
