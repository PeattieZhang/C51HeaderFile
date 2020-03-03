/************************************************************************************/
/*																PZ_UART.h	Ver1.1																	*/
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
/*					------------------------------------------------------------------			*/
/*					Ver1.1更新(2020/03/04)：																								*/
/*							1.PZ_UART_GetReceived()中当DataLength = 0时读取所有数据；						*/
/*							2.取消原PZ_UART_Send()中若FIFO满则不将数据写入的逻辑，改为若FIFO		*/
/*							满则等待FIFO有空位后继续写入，直到待传数据全部写入FIFO；						*/
/*							3.更改原PZ_UART_GetReceived()读取逻辑，当DataLength大于FIFO中缓存		*/
/*							字符数时，会将FIFO中所有缓存字符读取后再退出。											*/
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
/*									函数声明									*/
/**********************************************/
/*	UART初始化	*/
void PZ_UART_Init(void);

/*	UART发送/接收数据	*/
void PZ_UART_Send(unsigned char *Data, unsigned char DataLength);					//UART发送数据,Data为数据指针，DataLength为数据字节数
char PZ_UART_GetReceived(unsigned char *Data, unsigned char DataLength);	//UART获取数据，返回数为成功读取到的字符数;Data为数据指针，DataLength为最大接收数据字节数，DataLength = 0时读取所有数。

#endif