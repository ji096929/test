/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   SPI配置C文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */



#include "drv_spi.h"


/** 硬件SPI */
#define SPI_WAIT_TIMEOUT			((uint16_t)0xFFFF)


/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:接收到的字节
  */
uint8_t drv_spi_read_write_byte( SPI_HandleTypeDef *hspi,uint8_t TxByte )
{
	uint8_t l_Data = 0;
	
	HAL_SPI_TransmitReceive(hspi, &TxByte, &l_Data, 1, SPI_WAIT_TIMEOUT);  //一个字节
	
	return l_Data;		//返回
}

/**
  * @brief :SPI收发字符串
  * @param :
  *			@ReadBuffer: 接收数据缓冲区地址
  *			@WriteBuffer:发送字节缓冲区地址
  *			@Length:字节长度
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:无
  */
void drv_spi_read_write_string(SPI_HandleTypeDef *hspi, uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
{
	spi_set_nss_low();			//拉低片选
	while( Length-- )
	{
		*ReadBuffer = drv_spi_read_write_byte( hspi, *WriteBuffer );		//收发数据
		ReadBuffer++;
		WriteBuffer++;				//读写地址加1
	}
	spi_set_nss_high();				//拉高片选
}
/** 硬件SPI */
