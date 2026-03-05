/*
 * Common_Peripherals.h
 *
 *  Created on: 2024年6月26日
 *      Author: ORRN
 */

#ifndef CODE_COMMON_PERIPHERALS_H_
#define CODE_COMMON_PERIPHERALS_H_


#define BUZZER_PIN  (P33_10)

#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)                           // 定义主板上舵机对应引脚
#define SERVO_MOTOR_FREQ            (50)                                        // 定义主板上舵机频率  请务必注意范围
#define SERVO_MOTOR_MID             (130)                                        //中值130//可以通过修改中值的方式弥补机械误差79
#define SERVO_MOTOR_LMAX            (153)                                        //左打死153
#define SERVO_MOTOR_RMAX            (105)                                       //右打死105
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))// ------------------ 舵机占空比计算方式 ------------------


#define LED1                    (P20_9)
#define LED2                    (P20_8)
#define LED3                    (P21_5)
#define LED4                    (P21_4)

#define KEY1                    (P20_6)
#define KEY2                    (P20_7)
#define KEY3                    (P11_2)
#define KEY4                    (P11_3)

#define SWITCH2                 (P33_12)
#define SWITCH1                 (P33_13)


#define X6F_CH1                     (P10_3)      //方向舵通道
#define X6F_CH2                     (P10_1)      //油门通道

#define X6F_CH3                     (P10_1)      //指示按钮通道
#define X6F_CH4                     (P02_6)      //拨动挡位通道
#define X6F_CH5                     (P21_5)      //旋钮通道1
#define X6F_CH6                     (P21_3)      //旋钮通道2

////IPS114宏定义
//#define ips_show_string                  ips114_show_string
//#define ips_show_int                     ips114_show_int
//#define ips_show_uint                    ips114_show_uint
//#define ips_show_float                   ips114_show_float
//#define ips_show_chinese                 ips114_show_chinese
//#define ips_clear                        ips114_clear
//#define ips_init                         ips114_init
//#define ips_show_rgb565_image            ips114_show_rgb565_image

//IPS200宏定义
#define ips_show_string                  ips200_show_string
#define ips_show_int                     ips200_show_int
#define ips_show_uint                    ips200_show_uint
#define ips_show_float                   ips200_show_float
#define ips_show_chinese                 ips200_show_chinese
#define ips_clear                        ips200_clear
#define ips_init                         ips200_init
#define ips_show_rgb565_image            ips200_show_rgb565_image

#define R_DIR P21_2
#define R_PWM ATOM0_CH1_P21_3
#define L_DIR P21_4
#define L_PWM ATOM1_CH3_P21_5

//#define L_PWM_1 ATOM1_CH5_P02_5
//#define L_PWM_2 ATOM1_CH4_P02_4
//
//#define R_PWM_1 ATOM1_CH6_P02_6
//#define R_PWM_2 ATOM1_CH7_P02_7

#define ENCODER_L                   (TIM2_ENCODER)
#define ENCODER_L_A                 (TIM2_ENCODER_CH1_P33_7)
#define ENCODER_L_B                 (TIM2_ENCODER_CH2_P33_6)

#define ENCODER_R                   (TIM5_ENCODER)
#define ENCODER_R_A                 (TIM5_ENCODER_CH1_P10_3)
#define ENCODER_R_B                 (TIM5_ENCODER_CH2_P10_1)

#define PWM_CH1             ATOM1_CH5_P02_5      //PWM输出端口
#define DIR_CH1             P02_4               //电机方向输出端口

#define ENCODER1_TIM        TIM2_ENCODER            //编码器定时器
#define ENCODER1_PLUS       TIM2_ENCODER_CH1_P33_7   //编码器计数端口
#define ENCODER1_DIR        TIM2_ENCODER_CH2_P33_6  //编码器方向采值端口


extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;
extern uint8 key4_flag;

extern int16 NOW_SPEED_L;
extern int16 NOW_SPEED_R;

void Buzzer_init(void);
void Buzzer_check(int time2);

void Key_init(void);
void key_scan(void);

void Steer_init(void);
void Steer_set(int angle);
void Steer_text(void);

void DRV8701_D_init(void);
void DRV8701_D_ctrl(float L_speed,float R_speed);
//void DRV8701_D_loop_ctrl(float EXT_L,float EXT_R);

//void HIP4082_Init_D(void);
//void HIP4082_MOTOR_DRIVER_D(int L_SPEED,int R_SPEED);
void Motor_text(void);

void Encoder_init(void);
void Encoder_get(void);
void Encoder_text(void);

void MT9V03_text(void);

void BLDC_init(void);
void BLDC_ctrl(int16 Motor_SPEED);
void BLDC_text(void);

void HALL_init(void);
void HALL_gather(void);

void Control_init();
void x6f_scan(void);
void Control_TEXT();
void YX_CTRL(void);
void YX_CTRL_2(void);
void new_ctrl(void);

void ALL_init(void);









#endif /* CODE_COMMON_PERIPHERALS_H_ */
