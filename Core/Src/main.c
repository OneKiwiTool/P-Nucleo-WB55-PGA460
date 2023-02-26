#include "main.h"
#include "board.h"
#include "pga460.h"
#include <stdio.h>

int main(void)
{

    uint8_t temp = 0;
    
    /* System interrupt init*/
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    /* SysTick_IRQn interrupt configuration */
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));

    board_init();
    printf("start program!\n\r");

    temp = pga460_read_register(0x01);
    printf("1. 0x%02x\n", temp);

    pga460_write_register(0x01, 0x45);
    temp = pga460_read_register(0x01);
    printf("2. 0x%02x\n", temp);

    pga460_write_register(0x01, 0x25);
    temp = pga460_read_register(0x01);
    printf("3. 0x%02x\n", temp);

    pga460_write_register(0x01, 0x15);
    temp = pga460_read_register(0x01);
    printf("4. 0x%02x\n", temp);

    //pga460_init_thresholds(1);
    //pga460_default(1);
    //pga460_init_tvg(2, 1);
    pga460_threshold_bulk_read();
    printf("4. 0x%02x\n", temp);

    while (1)
    {

    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
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
