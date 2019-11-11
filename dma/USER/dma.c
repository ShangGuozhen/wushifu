#include "dma.h"
#include "gyro.h"
u8 trans[10]={6,5,3,2,2,2,3,4,4,5};
u8 receive[100]={0};


void dma_init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
//	while (DMA_GetCmdStatus(DMA1_Stream3) != DISABLE){;}//等待 DMA 可配置 
//		
//	DMA_InitStructure.DMA_Channel=DMA_Channel_4;
//	DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)&USART3->DR;
//	DMA_InitStructure.DMA_Memory0BaseAddr=(u32)trans;
//	DMA_InitStructure.DMA_DIR=DMA_DIR_MemoryToPeripheral;
//	DMA_InitStructure.DMA_BufferSize=10;
//	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 使用普通模式
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;//FIFO 模式禁止
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;//FIFO 阈值
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
//	DMA_Init(DMA1_Stream3, &DMA_InitStructure);//
//	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE); 
		
	while (DMA_GetCmdStatus(DMA1_Stream1) != DISABLE){;}
	DMA_InitStructure.DMA_Channel=DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)&USART3->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr=(u32)Get_Address();
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize=34;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 使用普通模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;//FIFO 模式禁止
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;//FIFO 阈值
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
	DMA_Init(DMA1_Stream1, &DMA_InitStructure);//
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); 
	DMA_Cmd(DMA1_Stream1, ENABLE); 
}



void usart3_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_USART3); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式 
	USART_Init(USART3, &USART_InitStructure); //初始化串口 
	
	
	
	//USART3->RESERVED4|=1;

//	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//开启中断 
//	
//	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure); 
	
	
	
	
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//开启中断 
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	
  USART_Cmd(USART3, ENABLE); 

	
	dma_init();
}

void DMASend(void)
{
	
	if(DMA_GetFlagStatus(DMA1_Stream3,DMA_FLAG_TCIF3)!=RESET) //等待 DMA2_Steam7 传输完成     
	{       
			DMA_ClearFlag(DMA1_Stream3,DMA_FLAG_TCIF3);//清传输完成标志                
	}
	
	
	
	DMA_Cmd(DMA1_Stream3, DISABLE); //关闭 DMA 传输  
	while (DMA_GetCmdStatus(DMA1_Stream3) != DISABLE){}//确保 DMA 可以被设置   
	//DMA_SetCurrDataCounter(DMA1_Stream3,10);//这一步好像有没有都能发，但寄存器那里的确改变了
	DMA_Cmd(DMA1_Stream3, ENABLE); 
}

void USART3_IRQHandler(void)
{
	
	if(USART_GetFlagStatus(USART3,USART_IT_IDLE)!=RESET )
	{
		DMA_Cmd(DMA1_Stream1, DISABLE); 
		USART3->DR;//清除寄存器
		DMA_Cmd(DMA1_Stream1, ENABLE); 
	}
	
	
}
//void DMA1_Stream1_IRQHandler(void)
//{
//	if(DMA_GetFlagStatus(DMA1_Stream1,DMA_FLAG_TCIF0)!=RESET )
//	{

//	}
//	CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);  
//	
//}







