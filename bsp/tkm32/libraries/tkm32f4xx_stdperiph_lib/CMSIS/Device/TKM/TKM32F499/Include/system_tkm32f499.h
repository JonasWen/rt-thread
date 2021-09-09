
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup tkm32f499_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_TKM32F499_H
#define __SYSTEM_TKM32F499_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup TKM32F499_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup TKM32F499_System_Exported_types
  * @{
  */
extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

extern const uint8_t  AHBPrescTable[16];    /*!< AHB prescalers table values */
extern const uint8_t  APBPrescTable[8];     /*!< APB prescalers table values */

/**
  * @}
  */

/** @addtogroup TKM32F499_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup TKM32F499_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup TKM32F499_System_Exported_Functions
  * @{
  */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_TKM32F499_H */

/**
  * @}
  */
  
/**
  * @}
  */
