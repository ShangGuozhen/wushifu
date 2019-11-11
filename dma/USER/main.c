#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "dma.h"
#include "gyro.h"
u8 judge=0;
float ax,ay,az;
float gx,gy,gz;
float pitch,yaw,roll;

int ax1,ay1,az1;
int gx1,gy1,gz1;
int pitch1,yaw1,roll1;
int main()
{
	delay_init(168);
	usart3_init();
	while(1)
	{
		if(CheckData())
		{
			GetAcc(&ax,&ay,&az);
			GetGyro(&gx,& gy,&gz);
			GetAngle(&pitch,&roll,&yaw);
		}
		pitch1=pitch*100;
		yaw1=yaw*100;
		roll1=roll*100;
		
	}
}