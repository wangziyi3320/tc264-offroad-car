/*
 * IMU.c
 *
 *  Created on: 2025年1月21日
 *      Author: ORRN
 */
#include "zf_common_headfile.h"

gyro_param_t Gyro_Offset;
IMU_param_t  IMU_Data;

float Yaw_1 = 0;
float Roll_1 = 0;
float Picth_1 = 0;

int IMU_1_Open_flag = 0;//开启IMU标志位

void IMU_init(void)//IMU初始化
{
    imu660ra_init();   //IMU660惯导初始化
    IMU_gyro_Offset_Init();// 陀螺仪零漂初始化
}

void IMU_gyro_Offset_Init(void)
{
    Gyro_Offset.Xdata = 0;
    Gyro_Offset.Ydata = 0;
    Gyro_Offset.Zdata = 0;
    for (uint16_t i = 0; i < 1000; i++)
    {
        Gyro_Offset.Xdata += imu660ra_gyro_x;
        Gyro_Offset.Ydata += imu660ra_gyro_y;
        Gyro_Offset.Zdata += imu660ra_gyro_z;
        system_delay_ms(5);   // 最大 1Khz
    }

    Gyro_Offset.Xdata /= 1000;
    Gyro_Offset.Ydata /= 1000;
    Gyro_Offset.Zdata /= 1000;
}

void IMU_GetValues(void)//将采集的数值转化为实际物理值, 并对陀螺仪进行去零漂处理
{

    IMU_Data.gyro_x = ((float) imu660ra_gyro_x - Gyro_Offset.Xdata)* PI / 180/ 16.384f;
    IMU_Data.gyro_y = ((float) imu660ra_gyro_y - Gyro_Offset.Ydata)* PI / 180/ 16.384f;
    IMU_Data.gyro_z = ((float) imu660ra_gyro_z - Gyro_Offset.Zdata)* PI / 180/ 16.384f;

    if(IMU_Data.gyro_z<0.015&&IMU_Data.gyro_z>-0.015)//滤波
    {
        Yaw_1-=0;
    }
    else
    {
        IMU_Handle_180();
     }

}

void IMU_Handle_180(void)
{

    Yaw_1-=RAD_TO_ANGLE(IMU_Data.gyro_z*0.005);//(积分过程)本来是逆时针为正,现在改为顺时针为正

   if(Yaw_1>180 && Yaw_1<=360)
    {
        Yaw_1-=360;
    }
    else if(Yaw_1<(-180) && Yaw_1>=(-360))
    {
        Yaw_1+=360;
    }

}

void IMU_data_get(void)
{
    imu660ra_get_gyro();

    if(IMU_1_Open_flag==1)
    {
        IMU_GetValues();
    }
}

void IMU_text(void)
{
    IMU_1_Open_flag=1;
    while(1)
    {

        ips200_show_string( 0,16*4,"gyro_z,Gyro_Offset.Zdata:");
        ips200_show_float(  0, 16*7, imu963ra_gyro_z  , 4, 5);
        ips200_show_float(  0, 16*8, Gyro_Offset.Zdata, 4, 5);

        ips_show_string(8*0, 16*12, "Yaw:");      ips_show_float(8*5,16*12,Yaw_1,3,6);
    }
}
