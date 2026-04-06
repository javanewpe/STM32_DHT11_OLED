/**
  ******************************************************************************
  * @file       app_dht11_oled.c
  * @date       2026
  * @brief      读取DHT11温湿度传感器并显示在OLED实验应用层函数接口
  ******************************************************************************
  */
  
#include "dht11_oled/app_dht11_oled.h"
#include "dht11/bsp_dht11.h" 
#include "dwt/bsp_dwt.h"
#include "oled/bsp_i2c_oled.h"


static DHT11_DATA_TYPEDEF dht11_data = {0};

/**
* @brief  读取DHT11传感器数据并显示在OLED上面
  * @param  无
  * @retval 读取成功返回1，失败返回0
  */
void DHT11_UpdateAndShow(void)
{
    /* -----------------只读取一次 DHT11 ---------------------------- */
    uint8_t result = DHT11_ReadData(&dht11_data);
	/* -------------- 清屏 ---------------------------- */
    OLED_CLS();
    /* ------------ 第一行：显示固定 LOGO（显示“温湿度采集”） ------------ */
    OLED_ShowChinese_F16X16(0, 1, 0);  // 第0行 第2列：显示“温”
    OLED_ShowChinese_F16X16(0, 2, 1);  // 第0行 第3列：显示“湿”
    OLED_ShowChinese_F16X16(0, 3, 2);  // 第0行 第4列：显示“度”
    OLED_ShowChinese_F16X16(0, 4, 3);  // 第0行 第5列：显示“采”
    OLED_ShowChinese_F16X16(0, 5, 4);  // 第0行 第6列：显示“集”
	
    if(result == HAL_OK)
    {
        /* ---------- 第二行：显示温度 ---------- */
        OLED_ShowChinese_F16X16(1, 0, 5);  // 第1行 第0列：显示“温”
        OLED_ShowChinese_F16X16(1, 1, 6);  // 第1行 第1列：显示“度”
        OLED_ShowString_F8X16(1, 4, (uint8_t *)":");  // 显示冒号“:”
	
        char temp_str[8];
        sprintf(temp_str, "%2d.%1dC", dht11_data.temp_int, dht11_data.temp_deci);  // 格式化温度字符串，如“27.0C”
        OLED_ShowString_F8X16(1, 6, (uint8_t *)temp_str);  // 显示温度数值
			
        /* ---------- 第三行：显示湿度 ---------- */
        OLED_ShowChinese_F16X16(2, 0, 7);  // 第2行 第0列：显示“湿”
        OLED_ShowChinese_F16X16(2, 1, 8);  // 第2行 第1列：显示“度”
        OLED_ShowString_F8X16(2, 4, (uint8_t *)":");  // 显示冒号“:”

        char humi_str[8];
        sprintf(humi_str, "%2d.%1d%%", dht11_data.humi_int, dht11_data.humi_deci);  // 格式化湿度字符串，如“66.2%”
        OLED_ShowString_F8X16(2, 6, (uint8_t *)humi_str);  // 显示湿度数值
       
        /* ---------- 串口打印 ---------- */       
        printf("==========================\r\n");
        printf("温度：%d.%d ℃\r\n", dht11_data.temp_int, dht11_data.temp_deci);
        printf("湿度：%d.%d %%RH\r\n", dht11_data.humi_int, dht11_data.humi_deci);
        printf("==========================\r\n");
		}
		else
		{
        /* ---------- 错误提示（传感器读取失败） ---------- */
        OLED_ShowString_F8X16(1, 5, (uint8_t *)"DHT11");     // 第1行 显示“DHT11”
        OLED_ShowString_F8X16(2, 4, (uint8_t *)"ERROR!!");   // 第2行 显示“ERROR!!”
        printf("DHT11 读取失败！\r\n");
		}
    /* ------------ 延时控制（确保采样周期大于2秒） ------------ */
    DWT_DelayS(2);  // 延时 2 秒
}

/*****************************END OF FILE***************************************/



