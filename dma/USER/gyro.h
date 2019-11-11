#ifndef _GYRO_
#define _GYRO_
#include "stm32f4xx.h"

#define Offset_Acc    6//���ٶ�
#define Offset_Gyro  13//���ٶ�
#define Offset_Geo   20//�ش�
#define Offset_Angle 27
#define Offset_Last  33

#define First_Check 0xA5
#define Last_Check  0x5A

u32 Get_Address(void);
u8 CheckData(void);

u8 GetAcc(float* ax,float* ay,float* az);
u8 GetGyro(float* gx,float* gy,float* gz);
u8 GetAngle(float* pitch,float* roll,float* yaw);
#endif
