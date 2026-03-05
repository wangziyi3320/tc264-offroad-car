/*
 * images.h
 *
 *  Created on: 2025年4月16日
 *      Author: 27322
 */
#ifndef __IMAGES_H__
#define __IMAGES_H__
extern float Angle_Error;  // 声明全局变量
#include "zf_common_headfile.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif


// 颜色定义
#define BLUE            0x0000FF
#define RED             0xFF0000
// 颜色定义（补充）
#define WHITE  0xFFFF
#define BLACK  0x0000

// 全局变量声明
extern uint8 mt9v03x_image_BandW[MT9V03X_H][MT9V03X_W];
extern uint8 left_line_list[MT9V03X_H];
extern uint8 right_line_list[MT9V03X_H];
extern uint8 mid_line_list[MT9V03X_H];
extern uint8 bridge_mode;
/* 图像处理函数声明 */
// 大津法阈值计算
uint8 otsuThreshold_fast(uint8 *image);
uint8 otsuThreshold(uint8 *image, uint16 width, uint16 height);
void Calculate_Track_Error(void);
// 图像二值化
void Set_image_towvalues(uint8 value);

// 赛道边界识别
void Find_Mid_Line(uint8 index[MT9V03X_H][MT9V03X_W]);
void Find_Mid_Line_Draw_Line(void);
void image_preprocess(void);
// 辅助绘图函数
void draw_points(uint8 x, uint8 y, uint16 color);
uint8 adaptive_otsuThreshold(uint8 *image);
uint8 otsuThreshold_dark(uint8 *image, uint16 width, uint16 height);
/* 新增的舵机控制声明 */
#define SERVO_MOTOR_PWM         (ATOM1_CH1_P33_9)   // 舵机PWM引脚
#define STEER_CENTER            129                 // 舵机中值
#define STEER_MAX_LEFT          153                 // 最大左转
#define STEER_MAX_RIGHT         105                 // 最大右转
// 添加在 images.h 中
#ifdef __cplusplus
extern "C" {
#endif

float constrain(float value, float min_val, float max_val);
int constrain_int(int value, int min_val, int max_val);

#ifdef __cplusplus
}
#endif
void servo_control(int angle);

/* 新增的电机控制声明 */
#define MAX_DUTY               30    // 电机最大占空比
#define MOTOR_BASE_SPEED       15    // 基础速度
void motor_control(int speed_left, int speed_right);

#endif /* __IMAGES_H__ */
