#include "gyro.h"
u8 GyroData[100];
u32 Get_Address(void)
{
	return (u32)GyroData;
}

u16 DataChange(u8 low,u8 high)
{
	return low|(high<<8);
}
u8 CheckData(void)
{
	if(GyroData[0]!=First_Check||GyroData[Offset_Last]!=Last_Check)
		return 0;
	return 1;
}

u8 GetAcc(float* ax,float* ay,float* az)
{
	*ax=(float)(int16_t)DataChange(GyroData[Offset_Acc],GyroData[Offset_Acc+1]);
	*ay=(float)(int16_t)DataChange(GyroData[Offset_Acc+2],GyroData[Offset_Acc+3]);
	*az=(float)(int16_t)DataChange(GyroData[Offset_Acc+3],GyroData[Offset_Acc+5]);
}
u8 GetGyro(float* gx,float* gy,float* gz)
{
	*gx=(float)(int16_t)DataChange(GyroData[Offset_Gyro],GyroData[Offset_Gyro+1]);
	*gy=(float)(int16_t)DataChange(GyroData[Offset_Gyro+2],GyroData[Offset_Gyro+3]);
	*gz=(float)(int16_t)DataChange(GyroData[Offset_Gyro+3],GyroData[Offset_Gyro+5]);
}
u8 GetAngle(float* pitch,float* roll,float* yaw)
{
	*pitch=(float)(int16_t)DataChange(GyroData[Offset_Angle],GyroData[Offset_Angle+1])/100;
	*roll=(float)(int16_t)DataChange(GyroData[Offset_Angle+2],GyroData[Offset_Angle+3])/100;
	*yaw=(float)(int16_t)DataChange(GyroData[Offset_Angle+3],GyroData[Offset_Angle+5])/10;
}