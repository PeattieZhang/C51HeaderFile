/************************************************************************************/
/*																PZ_UART.h	Ver1.0																	*/
/*					------------------------------------------------------------------			*/
/*									适用于51单片机的UART头函数																			*/
/*									用于通过UART发送、接收数据																			*/
/*									内置32字节FIFO，FIFO字节数可通过FIFO_SIZE改变										*/
/*									波特率默认9600kbps，可通过BAUD_RATE改变													*/
/*					------------------------------------------------------------------			*/
/*							默认情况下FIFO_SIZE上限较小，若过大则会报错"SEGMENT TOO LARGE"。		*/
/*					解决办法：进入"Options for Target/Target"，通过改变"Memory Model"可			*/
/*					以改变FIFO_SIZE上限。																										*/
/*																														————Peattie Zhang			*/
/*																																	 2020/03/03			*/
/************************************************************************************/

#ifndef __PZUART_H__
#define __PZUART_H__
#include<reg52.h>

/**********************************************/
/*									参数设定									*/
/**********************************************/
#define BAUD_RATE 9600																										//波特率
#define FIFO_SIZE 32																											//FIFO大小

/**********************************************/
/*								FIFO状态表示								*/
/**********************************************/
typedef enum{
	FIFO_AVAILABLE = 0u,
	FIFO_INAVAILABLE
}FIFO_STATUS;

/**********************************************/
/*									函数声明									*/
/**********************************************/
/*	UART初始化	*/
void PZ_UART_Init(void);

/*	UART发送/接收数据，Data为数据指针，DataLength为数据字节数	*/
char PZ_UART_Send(unsigned char *Data, unsigned char DataLength);					//UART发送数据，返回数为1代表FIFO空间不足，待发送数据过多；返回数为0代表数据存入FIFO成功
char PZ_UART_GetReceived(unsigned char *Data, unsigned char DataLength);	//UART获取数据，返回数为1代表FIFO数据不足，已接收数据过少；返回数为0代表数据获取成功

#endif