/**
  ******************************************************************************
  * @file       main.c
  * @date       2026
  * @brief      DWT应用与DHT11温湿度传感器
  ******************************************************************************
	*/

#include "main.h"
#include "led/bsp_led.h"
#include "dwt/bsp_dwt.h"
#include "usart/bsp_usart.h"
#include "dht11/bsp_dht11.h"
#include "i2c/bsp_i2c.h"
#include "oled/bsp_i2c_oled.h"
#include "dht11_oled/app_dht11_oled.h"


void SystemClock_Config(void);


int main(void)
{

	HAL_Init();  			// 初始化 HAL 库 

	SystemClock_Config();   // 配置系统时钟，设置为 72MHz
	
	MX_USART1_UART_Init();	// 初始化串口，用于打印调试信息
	
	DWT_Init();				// 启动 DWT 计数器，用于精确测量程序运行时间

    MX_I2C1_Init();    	    // 初始化 I2C1 总线，配置时钟、引脚等硬件资源

    OLED_Init();      		// 初始化 OLED 显示屏，发送初始化命令配置显示参数以及清屏、显示
	
	DHT11_GPIO_Config();	// 初始化DHT11引脚部分
	
	while (1)
	{
               
		//读取 DHT11 传感器数据并显示到 OLED 屏上，也可以用串口进行打印
		DHT11_UpdateAndShow();

	}
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 1
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  oscinitstruct.HSEState        = RCC_HSE_ON;
  oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}

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
