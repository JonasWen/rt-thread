/* Includes ------------------------------------------------------------------*/
#include "tkm32f499_qspi.h"

/**
  * @brief  Deinitializes the QSPI peripheral registers to their default
  *         reset values.
  * @param  None
  * @retval None
  */
void QSPI_DeInit(void)
{
    /* Enable QSPI reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_QSPI, ENABLE);
    /* Release QSPI from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_QSPI, DISABLE);
}

/**
  * @brief  Fills each QSPI_InitStruct member with its default value.
  * @param  QSPI_InitStruct: pointer to a QSPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void QSPI_StructInit(QSPI_InitTypeDef* QSPI_InitStruct)
{
/*--------- Reset QSPI init structure parameters default values ------------*/
  /* Initialize the QSPI_SShift member */
  QSPI_InitStruct->QSPI_SShift = QSPI_SShift_NoShift ;
  /* Initialize the QSPI_Prescaler member */  
  QSPI_InitStruct->QSPI_Prescaler = 0 ;
  /* Initialize the QSPI_CKMode member */
  QSPI_InitStruct->QSPI_CKMode = QSPI_CKMode_Mode0 ;
  /* Initialize the QSPI_CSHTime member */
  QSPI_InitStruct->QSPI_CSHTime = QSPI_CSHTime_1Cycle ;
  /* Initialize the QSPI_FSize member */
  QSPI_InitStruct->QSPI_FSize = 0 ;
  /* Initialize the QSPI_FSelect member */
  QSPI_InitStruct->QSPI_FSelect = QSPI_FSelect_1 ;
  /* Initialize the QSPI_DFlash member */
  QSPI_InitStruct->QSPI_DFlash = QSPI_DFlash_Disable ;
}
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
