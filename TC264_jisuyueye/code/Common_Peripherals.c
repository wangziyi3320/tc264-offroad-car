/*
 * Common_Peripherals.c
 *
 *  Created on: 2024年6月26日
 *      Author: ORRN
 */



#include "zf_common_headfile.h"

//===================================================蜂鸣器===================================================
void Buzzer_init(void)//蜂鸣器初始化
{
    gpio_init(BUZZER_PIN, GPO, 0, GPO_PUSH_PULL);
}

void Buzzer_check(int time2)//蜂鸣器的自检函数
{
    gpio_set_level(BUZZER_PIN,1);
    system_delay_ms(time2);
    gpio_set_level(BUZZER_PIN,0);
}

//===================================================按键与LED===================================================
uint8 key1_state = 1;                                                               // 按键动作状态
uint8 key2_state = 1;                                                               // 按键动作状态
uint8 key3_state = 1;                                                               // 按键动作状态
uint8 key4_state = 1;                                                               // 按键动作状态

uint8 switch1_state = 0;                                                            // 拨码开关动作状态
uint8 switch2_state = 0;                                                            // 拨码开关动作状态

uint8 key1_state_last = 0;                                                          // 上一次按键动作状态
uint8 key2_state_last = 0;                                                          // 上一次按键动作状态
uint8 key3_state_last = 0;                                                          // 上一次按键动作状态
uint8 key4_state_last = 0;                                                          // 上一次按键动作状态

uint8 switch1_state_last = 0;                                                       // 上一次拨码开关动作状态
uint8 switch2_state_last = 0;                                                       // 上一次拨码开关动作状态

uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

uint8 key_val;


uint8 switch1_flag;
uint8 switch2_flag;

uint16 key1_count=-1;
uint16 key2_count=-1;
uint16 key3_count=-1;
uint16 key4_count=-1;

uint16 switch1_count=-1;
uint16 switch2_count=-1;

void Key_init(void)//按键与LED初始化
{

       gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED1 输出 默认高电平 推挽输出模式
       gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED2 输出 默认高电平 推挽输出模式
       gpio_init(LED3, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED3 输出 默认高电平 推挽输出模式
       gpio_init(LED4, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED4 输出 默认高电平 推挽输出模式

       gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY1 输入 默认高电平 上拉输入
       gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY2 输入 默认高电平 上拉输入
       gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY3 输入 默认高电平 上拉输入
       gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY4 输入 默认高电平 上拉输入

       gpio_init(SWITCH1, GPI, GPIO_HIGH, GPI_FLOATING_IN);    // 初始化 SWITCH1 输入 默认高电平 浮空输入
       gpio_init(SWITCH2, GPI, GPIO_HIGH, GPI_FLOATING_IN);    // 初始化 SWITCH2 输入 默认高电平 浮空输入

}

void key_scan(void)//按键扫描
    {


        //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费

        //保存按键状态
        key1_state_last = key1_state;
        key2_state_last = key2_state;
        key3_state_last = key3_state;
        key4_state_last = key4_state;

        //读取当前按键状态
        key1_state = gpio_get_level(KEY1);
        key2_state = gpio_get_level(KEY2);
        key3_state = gpio_get_level(KEY3);
        key4_state = gpio_get_level(KEY4);


        //检测到按键按下之后  并放开置位标志位
        if(key1_state && !key1_state_last)   {key1_flag = 1;}
        if(key2_state && !key2_state_last)   {key2_flag = 1;}
        if(key3_state && !key3_state_last)   {key3_flag = 1;}
        if(key4_state && !key4_state_last)   {key4_flag = 1;}

        //标志位置位之后，可以使用标志位执行自己想要做的事件

//        system_delay_ms(10);//延时，按键程序应该保证调用时间不小于10ms

    }


//===================================================舵机类===================================================
void Steer_init(void)//舵机初始化
{
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, (uint32)SERVO_MOTOR_DUTY(SERVO_MOTOR_MID));
}

void Steer_set(int angle)//舵机驱动
{
    if(angle>SERVO_MOTOR_LMAX){angle=SERVO_MOTOR_LMAX;}
    if(angle<SERVO_MOTOR_RMAX){angle=SERVO_MOTOR_RMAX;}
    pwm_set_duty(SERVO_MOTOR_PWM, (uint32)SERVO_MOTOR_DUTY(angle));

}

void Steer_text(void)//舵机测试
{
    static int32 angle=SERVO_MOTOR_MID;
    while(1)
    {
        //if(1 == uart_receiver.finsh_flag)                            // 帧完成标志判断
        //{
            //if(1 == uart_receiver.state)                             // 遥控器失控状态判断
            //{
               //static int32 angle=SERVO_MOTOR_MID;

                  key_scan();
                  if(key1_flag)
                     {
                         key1_flag=0;
                         angle+=10;
                         Steer_set(angle);

                     }
                  if(key2_flag)
                     {
                         key2_flag=0;
                         angle-=10;
                         Steer_set(angle);

                     }
                  if(key3_flag)
                     {
                         key3_flag=0;
                         angle+=1;
                         Steer_set(angle);

                     }
                  if(key4_flag)
                     {
                         key4_flag=0;
                        angle-=1;
                        Steer_set(angle);

                     }
                  ips_show_string(0,100, "Steer_text");
                  ips_show_int(100,  16*3,angle, 5);
//                  Steer_set(angle);

            }
            /*if( uart_receiver.channel[5] == 1792){
                static int32 angle = 130;
                Steer_set(angle);
                ips200_show_string(0, 16*0, "Stop");
                system_delay_ms(1000);

            }
            uart_receiver.finsh_flag = 0;
        }
    }*/

}

//===================================================电机类===================================================

int16 SPEED_ERROR_L=0;
int16 SPEED_ERROR_R=0;
float OUT_L=0;
float OUT_R=0;

void DRV8701_D_init(void)//DRV8701驱动初始化
 {
    gpio_init(R_DIR, GPO, 1, GPO_PUSH_PULL);
    pwm_init(R_PWM, 17000, 0);
    gpio_init(L_DIR, GPO, 1, GPO_PUSH_PULL);
    pwm_init(L_PWM, 17000, 0);
 }

void DRV8701_D_ctrl(float L_speed,float R_speed)//驱动面向前方,输出电机红线在前
{


    if(L_speed>=0)
      {
        gpio_set_level(L_DIR, 0);
        pwm_set_duty(L_PWM, L_speed);
       }
         else
        {
        gpio_set_level(L_DIR, 1);
        pwm_set_duty(L_PWM, -L_speed);
        }

    if(R_speed>=0)
       {
           gpio_set_level(R_DIR, 1);
           pwm_set_duty(R_PWM, R_speed);
       }
    else
       {
           gpio_set_level(R_DIR, 0);
           pwm_set_duty(R_PWM, -R_speed);
       }

}

//void DRV8701_D_loop_ctrl(float EXT_L,float EXT_R)//期望速度
//{
//    SPEED_ERROR_L=EXT_L-NOW_SPEED_L;
//    SPEED_ERROR_R=EXT_R-NOW_SPEED_R;
//
//    OUT_L=PidIncCtrl_L(&DJ_PID,SPEED_ERROR_L);
//    OUT_R=PidIncCtrl_R(&DJ_PID,SPEED_ERROR_R);
//
//    if(OUT_L>8000){OUT_L=8000;}
//    if(OUT_L<(-8000)){OUT_L=(-8000);}
//
//    if(OUT_R>8000){OUT_R=8000;}
//    if(OUT_R<(-8000)){OUT_R=(-8000);}
//
//    DRV8701_D_ctrl(OUT_L,OUT_R);
//}

//void HIP4082_Init_D(void)//HIP4082驱动初始化
//{
//    pwm_init(L_PWM_1, 17000, 50);
//    pwm_init(L_PWM_2, 17000, 50);
//
//    pwm_init(R_PWM_1, 17000, 50);
//    pwm_init(R_PWM_1, 17000, 50);
//}
//
//void HIP4082_MOTOR_DRIVER_D(int L_SPEED,int R_SPEED)//HIP4082驱动
//{
//    if(L_SPEED>=0)
//    {
//        pwm_set_duty(L_PWM_1, L_SPEED);
//        pwm_set_duty(L_PWM_2, 0);
//    }
//    else
//    {
//        pwm_set_duty(R_PWM_1, 0);
//        pwm_set_duty(R_PWM_2, (-L_SPEED));
//    }
//
//    if(R_SPEED>=0)
//    {
//        pwm_set_duty(R_PWM_1, R_SPEED);
//        pwm_set_duty(R_PWM_2, 0);
//    }
//    else
//    {
//        pwm_set_duty(R_PWM_1, 0);
//        pwm_set_duty(R_PWM_2, (-R_SPEED));
//    }
//

//}

void Motor_text(void)//电机测试
{
    while(1)
    {
   static int16 MOTOR=0;


          key_scan();
          if(key1_flag)
             {
                 key1_flag=0;
                 MOTOR+=100;
             }
          if(key2_flag)
             {
                 key2_flag=0;
                 MOTOR-=100;

             }
          if(key3_flag)
             {
                 key3_flag=0;
                 MOTOR+=1000;
//                 MOTOR=100;
             }
          if(key4_flag)
             {
                 key4_flag=0;
                 MOTOR-=1000;
//                 MOTOR=190;


             }

          ips_show_string(0, 100, "Motor_text");
          ips_show_int(100,  16*3,MOTOR, 5);
          DRV8701_D_ctrl(MOTOR,MOTOR);

    }


}


//===================================================编码器===================================================
int16 NOW_SPEED_L=0;
int16 NOW_SPEED_R=0;
void Encoder_init(void)
{
    //L
    encoder_dir_init (ENCODER_L,ENCODER_L_A,ENCODER_L_B);
    //R
    encoder_dir_init (ENCODER_R,ENCODER_R_A,ENCODER_R_B);
}

void Encoder_get(void)
{

    NOW_SPEED_L = (encoder_get_count(ENCODER_L));                              // 获取编码器计数
    encoder_clear_count(ENCODER_L);                                             // 清空编码器计数

    NOW_SPEED_R = -encoder_get_count(ENCODER_R);                              // 获取编码器计数
    encoder_clear_count(ENCODER_R);
}

void Encoder_text(void)
{
    while(1)
    {
        ips_show_string(0, 130, "Encoder_text");
        ips_show_string(8*0, 16*0, "NOW_SPEED_L");  ips200_show_int(8*12, 16*0, NOW_SPEED_L, 3);
        ips_show_string(8*0, 16*1, "NOW_SPEED_R");  ips200_show_int(8*12, 16*1, NOW_SPEED_R, 3);
    }
}
//===================================================编码器===================================================


//===================================================摄像头===================================================
void MT9V03_text(void)
{
    while(1)
    {
        if(mt9v03x_finish_flag)
        {
            ips_show_string(0, 130, "MT9V03_text");
            ips200_displayimage03x((const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H);                       // 显示原始图像
    //            ips200_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 240, 180, 64);     // 显示二值化图像
            mt9v03x_finish_flag = 0;
        }
    }
}





//===================================================摄像头===================================================

//===================================================无刷电机===================================================
void BLDC_init(void)//无刷电机初始化
{

    pwm_init(PWM_CH1, 1000, 0);                 //PWM引脚初始化
    gpio_init(DIR_CH1, GPO, 1, GPO_PUSH_PULL);  //方向引脚

}

void BLDC_ctrl(int16 Motor_SPEED)//BLDC驱动
{

    if(Motor_SPEED>=0)//正转
    {
        pwm_set_duty(PWM_CH1, (Motor_SPEED));
        gpio_set_level(DIR_CH1,1);
    }
    else             //反转
    {
        pwm_set_duty(PWM_CH1, -Motor_SPEED);
        gpio_set_level(DIR_CH1,0);
    }

 //    ips_show_uint(100,  16*1,Motor_SPEED, 5);
}

void BLDC_text(void)//舵机测试
{
    while(1)
    {
        if(1 == uart_receiver.finsh_flag)                            // 帧完成标志判断
        {
            if(1 == uart_receiver.state)                             // 遥控器失控状态判断
            {
               static int16 Motor_SPEED=0;

                  key_scan();
                  if(key1_flag)
                     {
                         key1_flag=0;
                         Motor_SPEED+=100;
                     }
                  if(key2_flag)
                     {
                         key2_flag=0;
                         Motor_SPEED-=100;
                     }
                  if(key3_flag)
                     {
                         key3_flag=0;
                         Motor_SPEED+=10;
                     }
                  if(key4_flag)
                     {
                         key4_flag=0;
                         Motor_SPEED-=10;
                     }
                  ips_show_string(0,100, "BLDC_text");
                  ips_show_int(100,  16*3,Motor_SPEED, 5);
                  BLDC_ctrl(Motor_SPEED);
            }
            if( uart_receiver.channel[5] == 1792){
                BLDC_ctrl(0);
                ips200_show_string(0, 16*0, "Stop");
                system_delay_ms(1000);

            }
            uart_receiver.finsh_flag = 0;
        }
    }

}


//===================================================无刷电机===================================================

//===================================================霍尔编码器===================================================
int16 encoder=0;  //转速
int16 stand=0;

void HALL_init(void)//霍尔编码器初始化
{
    encoder_dir_init(ENCODER1_TIM,ENCODER1_PLUS,ENCODER1_DIR);
}

void HALL_gather(void)//霍尔编码器获取值
{
    encoder= (encoder_get_count(ENCODER1_TIM));
    encoder_clear_count(ENCODER1_TIM);                                // 采集对应编码器数据
//    printf("encoder counter: %d\n", encoder);                // 串口输出采集的数据
//    system_delay_ms(100);
}


//===================================================霍尔编码器===================================================

//===================================================逐飞遥控===================================================

//各通道引脚
int16 x6f_pin_map[6] = {X6F_CH1, X6F_CH2, X6F_CH3, X6F_CH4, X6F_CH5, X6F_CH6};
//各通道高电平计数变量
int16 x6f_count[6];
//各通道高电平计数输出
int16 x6f_out[6];



void Control_init()//遥控器引脚初始化
{

    //初始化接收机引脚
       gpio_init(X6F_CH1, GPI, GPIO_LOW, GPI_PULL_UP);
       gpio_init(X6F_CH2, GPI, GPIO_LOW, GPI_PULL_UP);
//       gpio_init(X6F_CH3, GPI, GPIO_LOW, GPI_PULL_UP);
//       gpio_init(X6F_CH4, GPI, GPIO_LOW, GPI_PULL_UP);
//       gpio_init(X6F_CH5, GPI, GPIO_LOW, GPI_PULL_UP);
//       gpio_init(X6F_CH6, GPI, GPIO_LOW, GPI_PULL_UP);
}

void x6f_scan(void)//遥控器通道扫描
{
    for(int i = 0; i < 6; i ++)
    {
        if(gpio_get_level(x6f_pin_map[i]))
        {
            x6f_count[i]++;
        }
        else if(x6f_count[i] > 0)
        {
            x6f_out[i] = x6f_count[i];
            x6f_count[i] = 0;
        }
    }
}

void Control_TEXT()//遥控器测试
{
    //打印各通道高电平时长计数值
    printf("CH1 = %d\tCH2 = %d\tCH3 = %d\tCH4= %d\tCH5 = %d\tCH6 = %d\r\n",
            x6f_out[0], x6f_out[1], x6f_out[2], x6f_out[3], x6f_out[4], x6f_out[5]);
    gpio_toggle_level(LED1);
    system_delay_ms(50);
}


void YX_CTRL(void)
{


       if(x6f_out[0]<145)
              {Steer_set(SERVO_MOTOR_LMAX);}
       else if(x6f_out[0]>155)
              {Steer_set(SERVO_MOTOR_RMAX);}
       else
              {Steer_set(SERVO_MOTOR_MID);}


       if(x6f_out[1]>170)
              {DRV8701_D_ctrl(3000,3000);}
       else if (x6f_out[1]<140)
              {DRV8701_D_ctrl(-2000,-2000);}
       else
              {DRV8701_D_ctrl(0,0);}

}

void YX_CTRL_2(void)
{


    /* uart_receiver.channel[0]方向1
     * uart_receiver.channel[1]油门2
     * uart_receiver.channel[2]通道3
     *
    */
    if(1 == uart_receiver.finsh_flag)                            // 帧完成标志判断
    {
        if(uart_receiver.channel[0]<500)//这个if-else if结构控制舵机，舵机的值按照你实际的来改
               {Steer_set(SERVO_MOTOR_RMAX);}//YOU打死
        else if(uart_receiver.channel[0]<992)
               {Steer_set(SERVO_MOTOR_RMAX);}//右打死
        else if(uart_receiver.channel[0]>992&&uart_receiver.channel[0]<1300)
               {Steer_set(SERVO_MOTOR_LMAX);}//ZUO打死
        else if(uart_receiver.channel[0]>1300)
               {Steer_set(SERVO_MOTOR_LMAX);}//ZUO打死

        else  if(uart_receiver.channel[0]==992)
                {Steer_set(SERVO_MOTOR_MID);}//中值


       if(uart_receiver.channel[1]<300)//这个if-else if结构控制电机，电机的值按照你实际的来改
       {DRV8701_D_ctrl(3000,3000);}
       else if (uart_receiver.channel[1]<600&&uart_receiver.channel[1]>400)
       {DRV8701_D_ctrl(2500,2500);}
       else if (uart_receiver.channel[1]<968&&uart_receiver.channel[1]>600)
       {DRV8701_D_ctrl(2000,2000);}
       else if (uart_receiver.channel[1]>968)
       {DRV8701_D_ctrl(-2000,-2000);}
       else if(uart_receiver.channel[1]==968)
       {DRV8701_D_ctrl(0,0);}


        uart_receiver.finsh_flag = 0;                            // 帧完成标志复位
    }

}

void new_ctrl(void)
{
    if(1 == uart_receiver.finsh_flag)                            // 帧完成标志判断
           {
               if(1 == uart_receiver.state)                             // 遥控器失控状态判断
               {
                   //舵机控制
                          if(uart_receiver.channel[0]>=1500&&uart_receiver.channel[0]<=1792)
                          {
                              Steer_set(SERVO_MOTOR_LMAX);
                          }

                           else if(uart_receiver.channel[0]>=192&&uart_receiver.channel[0]<=700)
                           {
                               Steer_set(SERVO_MOTOR_RMAX);

                           }
                           else
                           {
                               Steer_set(SERVO_MOTOR_MID);
                           }


                          //电机控制
                          if(uart_receiver.channel[1]>=1500&&uart_receiver.channel[1]<=1792)
                          {
                              BLDC_ctrl(2000);
                          }

                           else if(uart_receiver.channel[1]>=192&&uart_receiver.channel[1]<=700)
                           {
                               BLDC_ctrl(-2000);

                           }
                           else
                           {
                               BLDC_ctrl(0);
                           }
               }
               else
               {
                   printf("Remote control has been disconnected.\r\n"); // 串口输出失控提示
               }
               uart_receiver.finsh_flag = 0;                            // 帧完成标志复位
           }

}


void ALL_init(void)//总初始化
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等

    GPS_init();                                 //GPS初始化
    Buzzer_init();                              //蜂鸣器
    Key_init();
    mt9v03x_init();                           //摄像头初始化
    Steer_init();                               //舵机初始化
//    DRV8701_D_init();                         //电机驱动初始化
    ips200_init(IPS200_TYPE_SPI);               //IPS200(SPI)初始化

//    Encoder_init();                           //带方向编码器初始化
//    IMU_init();                               //IMU初始化
    IMU963_init();
    BLDC_init();
    uart_receiver_init();                       //sbus接收机初始化


    Buzzer_check(50);


}
