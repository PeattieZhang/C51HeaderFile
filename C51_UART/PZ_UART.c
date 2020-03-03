#include "PZ_UART.h"
/*	����FIFO���	*/
unsigned char TRANSMIT_FIFO[FIFO_SIZE];
unsigned char TRANSMIT_FIFO_POS;
unsigned char TRANSMIT_FIFO_CNT;

/* ����FIFO���	*/
unsigned char RECEIVE_FIFO[FIFO_SIZE];
unsigned char RECEIVE_FIFO_POS;
unsigned char RECEIVE_FIFO_CNT;

/*	UART��ʼ��*/
void PZ_UART_Init(void){
	/*	FIFO��ʼ��	*/
	TRANSMIT_FIFO_POS = 0;
	TRANSMIT_FIFO_CNT = 0;
	RECEIVE_FIFO_POS = 0;
	RECEIVE_FIFO_CNT = 0;
	
	/*	UART��TIMER1�趨	*/
	SCON = 0x50;
	TMOD &= 0x0F;
	TMOD |= 0x20;
	switch(BAUD_RATE){				//���������ã����������
		case 9600:
		default:
			TH1 = TL1 = 0xFD;
			break;
		case 4800:
			TH1 = TL1 = 0xFA;
			break;
		case 2400:
			TH1 = TL1 = 0xF4;
			break;
		case 1200:
			TH1 = TL1 = 0xE8;
			break;
		case 600:
			TH1 = TL1 = 0xD0;
			break;
		case 300:
			TH1 = TL1 = 0xA0;
			break;
		case 150:
			TH1 = TL1 = 0x40;
			break;
	}
	TR1 = 1;
	ES = 1;
	EA = 1;
}

/*	��������(����FIFO��)	*/
void PZ_UART_Send(unsigned char *Data, unsigned char DataLength){
	unsigned char i;
	
	for(i = 0; i < DataLength; i++){
		while(TRANSMIT_FIFO_CNT >= FIFO_SIZE);																					//��FIFO��ʱ�ȴ�
		TRANSMIT_FIFO[(TRANSMIT_FIFO_POS+TRANSMIT_FIFO_CNT)%FIFO_SIZE] = *(Data+i);
		TRANSMIT_FIFO_CNT ++;
		if(TRANSMIT_FIFO_CNT <= 1){
			SBUF = TRANSMIT_FIFO[TRANSMIT_FIFO_POS];
		}
	}
}

/*	��������(��FIFO��ȡ)	*/
char PZ_UART_GetReceived(unsigned char *Data, unsigned char DataLength){
	unsigned char i;
	
	for(i = 0; (i <= DataLength || DataLength == 0) && RECEIVE_FIFO_CNT > 0; i++){		//����ȡ�ַ�������DataLength��FIFO�����պ��˳�ѭ��
		if(RECEIVE_FIFO_CNT){
			*(Data+i) = RECEIVE_FIFO[RECEIVE_FIFO_POS];
			RECEIVE_FIFO_POS = (RECEIVE_FIFO_POS+1)%FIFO_SIZE;
			RECEIVE_FIFO_CNT --;
		}
	}
	
	return i;
}

/*	�жϺ���	*/
void PZ_UART_SendInterrupt(void) interrupt 4{
	if(TI == 1){
		TRANSMIT_FIFO_POS = (TRANSMIT_FIFO_POS+1)%FIFO_SIZE;
		TRANSMIT_FIFO_CNT --;
		TI = 0;
		if(TRANSMIT_FIFO_CNT){
			SBUF = TRANSMIT_FIFO[TRANSMIT_FIFO_POS];
		}
	}
	
	if(RI == 1){
		if(RECEIVE_FIFO_CNT >= FIFO_SIZE) return;
		RECEIVE_FIFO[(RECEIVE_FIFO_POS+RECEIVE_FIFO_CNT)%FIFO_SIZE] = SBUF;
		RECEIVE_FIFO_CNT ++;
		RI = 0;
	}
}
