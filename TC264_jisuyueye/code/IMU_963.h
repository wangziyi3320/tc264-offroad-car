/*
 * IMU_963.h
 *
 *  Created on: 2025年3月17日
 *      Author: ORRN
 */

#ifndef CODE_IMU_963_H_
#define CODE_IMU_963_H_


//结构体声明
typedef struct{
    float Xdata;   //零飘参数X
    float Ydata;   //零飘参数Y
    float Zdata;   //零飘参数Z
}gyro963_param_t ;

typedef struct{
    float acc_x;   //x轴加速度
    float acc_y;   //y轴加速度
    float acc_z;   //z轴加速度

    float gyro_x;  //x轴角速度
    float gyro_y;  //y轴角速度
    float gyro_z;  //z轴角速度
}IMU963_param_t ;

extern int IMU963_1_Open_flag;
extern float Yaw963_1;

void IMU963_init(void);
void IMU963_gyro_Offset_Init(void);
void IMU963_GetValues(void);
void IMU963_Handle_180(void);
void IMU963_data_get(void);
void IMU963_text(void);
//void IMU963_AHRS_Update(void);










#endif /* CODE_IMU_963_H_ */
