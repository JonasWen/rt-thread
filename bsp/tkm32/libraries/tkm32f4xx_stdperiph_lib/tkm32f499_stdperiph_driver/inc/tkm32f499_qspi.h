
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TKM32F499_QSPI_H
#define __TKM32F499_QSPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tkm32f499.h"

/** @addtogroup TKM32F499_StdPeriph_Driver
* @{
*/

/** @addtogroup QSPI
* @{
*/

/** @defgroup QSPI_Exported_Types
* @{
*/

/**
  * @brief  QSPI Communication Configuration Init structure definition
  */

typedef struct
{

    uint32_t QSPI_ComConfig_FMode;        /* Specifies the Functional Mode
                                          This parameter can be a value of @ref QSPI_ComConfig_Functional_Mode*/
    uint32_t QSPI_ComConfig_DDRMode;      /* Specifies the Double Data Rate Mode
                                          This parameter can be a value of @ref QSPI_ComConfig_DoubleDataRateMode*/
    uint32_t QSPI_ComConfig_DHHC;         /* Specifies the Delay Half Hclk Cycle
                                          This parameter can be a value of @ref QSPI_ComConfig_DelayHalfHclkCycle*/
    uint32_t QSPI_ComConfig_SIOOMode;     /* Specifies the Send Instruction Only Once Mode
                                          This parameter can be a value of @ref QSPI_ComConfig_SendInstructionOnlyOnceMode*/
    uint32_t QSPI_ComConfig_DMode;        /* Specifies the Data Mode
                                          This parameter can be a value of @ref QSPI_ComConfig_DataMode*/
    uint32_t QSPI_ComConfig_DummyCycles;  /* Specifies the Number of Dummy Cycles.
                                           This parameter can be a number between 0x00 and 0x1F */
    uint32_t QSPI_ComConfig_ABSize;       /* Specifies the Alternate Bytes Size
                                          This parameter can be a value of @ref QSPI_ComConfig_AlternateBytesSize*/
    uint32_t QSPI_ComConfig_ABMode;       /* Specifies the Alternate Bytes Mode
                                          This parameter can be a value of @ref QSPI_ComConfig_AlternateBytesMode*/
    uint32_t QSPI_ComConfig_ADSize;       /* Specifies the Address Size
                                          This parameter can be a value of @ref QSPI_ComConfig_AddressSize*/
    uint32_t QSPI_ComConfig_ADMode;       /* Specifies the Address Mode
                                          This parameter can be a value of @ref QSPI_ComConfig_AddressMode*/
    uint32_t QSPI_ComConfig_IMode;        /* Specifies the Instruction Mode
                                          This parameter can be a value of @ref QSPI_ComConfig_InstructionMode*/
    uint32_t QSPI_ComConfig_Ins;          /* Specifies the Instruction Mode
                                          This parameter can be a value of @ref QSPI_ComConfig_Instruction*/
} QSPI_ComConfig_InitTypeDef;
/**
  * @brief  QSPI Init structure definition
  */
typedef struct
{
    uint32_t QSPI_SShift;    /* Specifies the Sample Shift
                              This parameter can be a value of @ref QSPI_Sample_Shift*/
    uint32_t QSPI_Prescaler; /* Specifies the prescaler value used to divide the QSPI clock.
                              This parameter can be a number between 0x00 and 0xFF */
    uint32_t QSPI_CKMode;    /* Specifies the Clock Mode
                              This parameter can be a value of @ref QSPI_Clock_Mode*/
    uint32_t QSPI_CSHTime;   /* Specifies the Chip Select High Time
                              This parameter can be a value of @ref QSPI_ChipSelectHighTime*/
    uint32_t QSPI_FSize;     /* Specifies the Flash Size.
                               QSPI_FSize+1 is effectively the number of address bits required to address the flash memory.
                               The flash capacity can be up to 4GB (addressed using 32 bits) in indirect mode, but the
                               addressable space in memory-mapped mode is limited to 512MB
                               This parameter can be a number between 0x00 and 0x1F */
    uint32_t QSPI_FSelect;   /* Specifies the Flash which will be used,
                                 This parameter can be a value of @ref QSPI_Fash_Select*/
    uint32_t QSPI_DFlash;    /* Specifies the Dual Flash Mode State
                                 This parameter can be a value of @ref QSPI_Dual_Flash*/
} QSPI_InitTypeDef;



#ifdef __cplusplus
}
#endif

#endif /* __TKM32F499_QSPI_H */
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2016 HOLOCENE ----------------------*/
