/*
 * IMU963_963.c
 *
 *  Created on: 2025年3月17日
 *      Author: ORRN
 */

#include "zf_common_headfile.h"
//#include "MahonyAHRS.h"

gyro963_param_t Gyro963_Offset;
IMU963_param_t  IMU963_Data;

float Yaw963_1 = 0;
float Roll963_1 = 0;
float Picth963_1 = 0;

//// 欧拉角输出,new
//float Yaw963_1 = 0;     // 偏航角
//float Roll963_1 = 0;    // 横滚角
//float Pitch963_1 = 0;   // 俯仰角

//// 时间相关变量,new
//static float dt = 0.001f;  // 采样周期（根据实际中断频率调整）
//static uint32_t last_time = 0;
//
//// Mahony算法参数配置,new
//#define SAMPLE_FREQ    500.0f   // 采样频率需与实际一致
//#define Kp             1.0f     // 比例增益
//#define Ki             0.05f    // 积分增益

int IMU963_1_Open_flag = 0;//开启IMU963标志位

void IMU963_init(void)//IMU963初始化
{
    imu963ra_init();   //IMU963惯导初始化
    pit_ms_init(CCU60_CH0, 1);                  //开启中断0初始化为1MS中断
    IMU963_gyro_Offset_Init();// 陀螺仪零漂初始化
//    //new
//    twoKp = 2.0f * Kp;
//    twoKi = 2.0f * Ki;
//    q0 = 1.0f; q1 = q2 = q3 = 0.0f;
}

void IMU963_gyro_Offset_Init(void)
{
    Gyro963_Offset.Xdata = 0;
    Gyro963_Offset.Ydata = 0;
    Gyro963_Offset.Zdata = 0;
    for (uint16_t i = 0; i < 1000; i++)
    {
        Gyro963_Offset.Xdata += imu963ra_gyro_x;
        Gyro963_Offset.Ydata += imu963ra_gyro_y;
        Gyro963_Offset.Zdata += imu963ra_gyro_z;
        system_delay_ms(5);   // 最大 1Khz
    }

    Gyro963_Offset.Xdata /= 1000;
    Gyro963_Offset.Ydata /= 1000;
    Gyro963_Offset.Zdata /= 1000;
}

/*
增加采样次数：从 1000 次提升到 2000 次，提高统计精度。
异常值过滤：丢弃瞬时噪声或硬件异常数据。
零漂范围校验：校准后检查零漂值是否在合理范围内。
*/
/*void IMU963_gyro_Offset_Init(void)
{
    #define SAMPLES 2000       // 增加采样次数

    // 初始化累加器
    double sum_x = 0, sum_y = 0, sum_z = 0;

    // 采集数据
    for (uint16_t i = 0; i < SAMPLES; i++)
    {
        sum_x += imu963ra_gyro_x;
        sum_y += imu963ra_gyro_y;
        sum_z += imu963ra_gyro_z;

        // 添加异常值过滤（示例）
        if (abs(imu963ra_gyro_x) > 100.0f ||
            abs(imu963ra_gyro_y) > 100.0f ||
            abs(imu963ra_gyro_z) > 100.0f)
        {
            i--;  // 丢弃异常采样
            continue;
        }

        system_delay_ms(5);
    }

    // 计算平均值
    Gyro963_Offset.Xdata = sum_x / SAMPLES;
    Gyro963_Offset.Ydata = sum_y / SAMPLES;
    Gyro963_Offset.Zdata = sum_z / SAMPLES;

    // 校验零漂范围（示例）
    if (abs(Gyro963_Offset.Xdata) > 1.0f ||
        abs(Gyro963_Offset.Ydata) > 1.0f ||
        abs(Gyro963_Offset.Zdata) > 1.0f)
    {
        // 零漂异常，触发告警或重新校准
        Buzzer_check(1000);  // 蜂鸣器报警
    }
}*/

void IMU963_GetValues(void)//将采集的数值转化为实际物理值, 并对陀螺仪进行去零漂处理
{
    IMU963_Data.gyro_x = ((float) imu963ra_gyro_x - Gyro963_Offset.Xdata)* PI / 180/ 14.3f;
    IMU963_Data.gyro_y = ((float) imu963ra_gyro_y - Gyro963_Offset.Ydata)* PI / 180/ 14.3f;
    IMU963_Data.gyro_z = ((float) imu963ra_gyro_z - Gyro963_Offset.Zdata)* PI / 180/ 14.3f;
    //new
//    IMU963_Data.acc_x = ((float) imu963ra_acc_x - Gyro963_Offset.Xdata)* PI / 180/ 4098.0f;  // 补充加速度计数据读取
//    IMU963_Data.acc_y = ...;
//    IMU963_Data.acc_z = ...;



    if(IMU963_Data.gyro_z<0.015&&IMU963_Data.gyro_z>-0.015)//滤波
    {
        Yaw963_1-=0;
    }
    else
    {
        IMU963_Handle_180();
     }

}

void IMU963_Handle_180(void)
{

    Yaw963_1-=RAD_TO_ANGLE(IMU963_Data.gyro_z*0.005);//(积分过程)本来是逆时针为正,现在改为顺时针为正

   if(Yaw963_1>180 && Yaw963_1<=360)
    {
        Yaw963_1-=360;
    }
    else if(Yaw963_1<(-180) && Yaw963_1>=(-360))
    {
        Yaw963_1+=360;
    }

}
////new
//void IMU963_AHRS_Update(void)
//{
//    // 调用Mahony算法（IMU版本，无磁力计）
//    MahonyAHRSupdateIMU(
//        IMU963_Data.gyro_x, IMU963_Data.gyro_y, IMU963_Data.gyro_z,
//        IMU963_Data.acc_x, IMU963_Data.acc_y, IMU963_Data.acc_z
//    );
//
//    // 四元数转欧拉角
//    Pitch963_1 = atan2f(2.0f*(q0*q1 + q2*q3), 1.0f - 2.0f*(q1*q1 + q2*q2));
//    Roll963_1  = asinf(2.0f*(q0*q2 - q3*q1));
//    Yaw963_1   = atan2f(2.0f*(q0*q3 + q1*q2), 1.0f - 2.0f*(q2*q2 + q3*q3));
//
//    // 弧度转角度
//    Yaw963_1   *= 180.0f / PI;
//    Roll963_1  *= 180.0f / PI;
//    Pitch963_1 *= 180.0f / PI;
//
//    // 角度规范化
//    if(Yaw963_1 < 0) Yaw963_1 += 360.0f;
//}

void IMU963_data_get(void)
{
    imu963ra_get_gyro();

    if(IMU963_1_Open_flag==1)
    {
        IMU963_GetValues();
    }
}

//void IMU963_data_get(void)
//{
//    imu963ra_get_gyro();
//
//    if(IMU963_1_Open_flag == 1)
//    {
//        // 计算时间间隔
//        uint32_t now = systick_get_value();
//        dt = (now - last_time) * 0.001f;  // 转换为秒
//        last_time = now;
//
//        IMU963_GetValues();
//        IMU963_AHRS_Update();  // 替换原有积分方法
//    }
//}

void IMU963_text(void)
{
    IMU963_1_Open_flag=1;
    while(1)
    {
        ips200_show_string( 0,16*4,"gyro_z,Gyro_Offset.Zdata:");
        ips200_show_float(  0, 16*7, imu963ra_gyro_z  , 4, 5);
        ips200_show_float(  0, 16*8, Gyro963_Offset.Zdata, 4, 5);
        ips_show_string(8*0, 16*0, "Yaw:");      ips_show_float(8*5,16*0,Yaw963_1,3,6);

    }
}


