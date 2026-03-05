/*
 * GPS.c
 *
 *  Created on: 2025年1月18日
 *      Author: ORRN
 */
#include "zf_common_headfile.h"
#include "images.h"

void GPS_init(void)
{
    gnss_init(GN42A);               // GN42A 为GPS模块 GN43RFA 为RTK模块
}

void GPS_parse(void)//GPS数据解析
{
    if(gnss_flag)
    {
        gnss_flag = 0;
        gnss_data_parse();           //开始解析数据
    }
}

void GPS_text(void)
{
    while(1)
    {
    ips200_show_uint(   0, 16*0, gnss.time.year, 4);
    ips200_show_uint(  80, 16*0, gnss.time.month, 2);
    ips200_show_uint( 160, 16*0, gnss.time.day, 2);
    ips200_show_uint(   0, 16*1, gnss.time.hour, 2);
    ips200_show_uint(  80, 16*1, gnss.time.minute, 2);
    ips200_show_uint( 160, 16*1, gnss.time.second, 2);

    ips200_show_uint(   0, 16*2, gnss.state, 5);
    ips200_show_float(120, 16*2, gnss.latitude, 4, 6);
    ips200_show_float(  0, 16*3, gnss.longitude, 4, 6);
    ips200_show_float(120, 16*3, gnss.speed, 4, 6);
    ips200_show_float(  0, 16*4, gnss.direction, 4, 6);
    ips200_show_uint( 120, 16*4, gnss.satellite_used, 5);
    ips200_show_float(  0, 16*5, gnss.height, 4, 6);
    }
}

int    i =0;                   //数组索引
int    Point_num=0;            //当前点位
double LAT_data[Point_MAX]={0};//纬度存储数组
double LOG_data[Point_MAX]={0};//经度存储数组

//===================================================GPS数组存点===================================================

//void GPS_array_get_point(void)
//{
//    //在页面上展示实时经纬度
//    ips200_show_string(8*0,16*0,"LAT:");    ips200_show_float(8*5, 16*0, gnss.latitude, 4, 6);
//    ips200_show_string(8*0,16*1,"LOG:");    ips200_show_float(8*5, 16*1, gnss.longitude, 4, 6);
//
//    if(key1_flag==1)
//    {
//        key1_flag=0;
//        if(i<=Point_MAX)
//        {
//            LAT_data[i]=gnss.latitude;//把实时维度赋值给存储纬度
//            LOG_data[i]=gnss.latitude;//把实时经度赋值给存储经度
//
//            ips200_show_string(8*0,16*3,"R_LAT:");   ips200_show_float(8*7, 16*3, LAT_data[i], 4, 6);
//            ips200_show_string(8*0,16*4,"R_LOG:");   ips200_show_float(8*7, 16*4, LOG_data[i], 4, 6);
//
//            ips200_show_string(8*0,16*6,"Num:");     ips200_show_uint(8*5, 16*6, i+1, 5);//数组是从0开始的,第一个点实际上是数组0,为了方便辨认+1
//            ips200_show_string(8*0,16*7,"MAX:20");
//            i++;
//            Point_num=i;
//        }
//        gpio_set_level(P20_9, 1);
//        system_delay_ms(100);
//        gpio_set_level(P20_9, 0);
//
//    }
//
//    if(key2_flag==1)
//    {
//        key2_flag=0;
//        ips200_clear();
//        for(int i=0;i<Point_num;i++)
//        {
//            ips200_show_float(8*2 ,16*(i+3),LAT_data[i],4,6);
//            ips200_show_float(8*15,16*(i+3),LAT_data[i],4,6);
//            ips200_show_uint( 8*0 ,16*(i+3),i+1,2);
//
//        }
//        gpio_set_level(P20_8, 1);
//        system_delay_ms(100);
//        gpio_set_level(P20_8, 0);
//    }
//
//    if(key3_flag==1)
//    {
//
//        key3_flag=0;
//        ips200_clear();
//        gpio_set_level(BUZZER_PIN,1);
//        system_delay_ms(3000);//延时3S
//        gpio_set_level(BUZZER_PIN,0);
//        IMU963_1_Open_flag=1;
//        gpio_set_level(P21_5, 1);
//        system_delay_ms(100);
//        gpio_set_level(P21_5, 0);
//    }
//
//}

void GPS_array_get_point(void)
{
    //在页面上展示实时经纬度
    ips200_show_string(8*0,16*0,"LAT:");    ips200_show_float(8*5, 16*0, gnss.latitude, 4, 6);
    ips200_show_string(8*0,16*1,"LOG:");    ips200_show_float(8*5, 16*1, gnss.longitude, 4, 6);
    while(key3_flag==0)
    {
        if(key1_flag==1)
        {
            key1_flag=0;
            if(i<=Point_MAX)
            {
                LAT_data[i]=gnss.latitude;//把实时维度赋值给存储纬度
                LOG_data[i]=gnss.longitude;//把实时经度赋值给存储经度

                ips200_show_string(8*0,16*3,"R_LAT:");   ips200_show_float(8*7, 16*3, LAT_data[i], 4, 6);
                ips200_show_string(8*0,16*4,"R_LOG:");   ips200_show_float(8*7, 16*4, LOG_data[i], 4, 6);

                ips200_show_string(8*0,16*6,"Num:");     ips200_show_uint(8*5, 16*6, i+1, 5);//数组是从0开始的,第一个点实际上是数组0,为了方便辨认+1
                ips200_show_string(8*0,16*7,"MAX:20");
                i++;
                Point_num=i;
            }
            gpio_set_level(P20_9, 1);
            system_delay_ms(1000);
            gpio_set_level(P20_9, 0);

        }

        if(key2_flag==1)
        {
            key2_flag=0;
            ips200_clear();
            for(int i=0;i<Point_num;i++)
            {
                ips200_show_float(8*2 ,16*(i+3),LAT_data[i],4,6);
                ips200_show_float(8*15,16*(i+3),LAT_data[i],4,6);
                ips200_show_uint( 8*0 ,16*(i+3),i+1,2);

            }
            gpio_set_level(P20_8, 1);
            system_delay_ms(1000);
            gpio_set_level(P20_8, 0);
        }
    }

    key3_flag=0;
    //ips200_clear();
    gpio_set_level(BUZZER_PIN,1);
    system_delay_ms(3000);//延时3S
    gpio_set_level(BUZZER_PIN,0);
    IMU963_1_Open_flag=1;

}
//===================================================GPS数组存点===================================================


//===================================================核心循迹===================================================
double Azimuth = 0;//方位角
double Distance = 0;//距离
double Nomal_Error = 0;//最终输出的角度偏差

int N = 0;//索引变量

void Follow_track(void)
{
    Azimuth=get_two_points_azimuth(gnss.latitude,gnss.longitude,LAT_data[N],LOG_data[N]);  //计算Azimuth
    Distance=get_two_points_distance(gnss.latitude,gnss.longitude,LAT_data[N],LOG_data[N]);//计算Distance

    if(Azimuth>=180)//对正北发车
    {
        Azimuth-=360;//为了使GPS分成+-半轴
    }

   if(Azimuth-Yaw963_1>180)
   {
       Nomal_Error=Azimuth-Yaw963_1-360;
   }
   else if(Azimuth-Yaw963_1<-180)
   {
       Nomal_Error=Azimuth-Yaw963_1+360;
   }
   else
   {
       Nomal_Error=Azimuth-Yaw963_1;
   }

}
//===================================================核心循迹===================================================

int OUT_value = 0;//正常GPS与IMU做差循迹
//===================================================姿态控制===================================================
void BD_ctrl(double Angle_error)
{
    OUT_value=PidLocCtrl(&Nomal_PID,(float)Angle_error);
    Steer_set(SERVO_MOTOR_MID+OUT_value);//具体是+还是-涉及到舵机安装,试一下
}
//===================================================姿态控制===================================================

//===================================================图像角度计算===================================================
extern float Angle_Error;  // 桥洞模式标志
#define BRIDGE_START_POINT 5  // 桥洞起始点位
#define BRIDGE_END_POINT   6   // 桥洞结束点位
void image_control(int current_point)
{
    if(current_point >= BRIDGE_END_POINT || bridge_mode == 0)
    {
            bridge_mode = 0;
            return;
    }
    uint8 BandW_threshold= 0;
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    while (bridge_mode && current_point < BRIDGE_END_POINT)
    {
        if(mt9v03x_finish_flag)
        {
            // 图像处理
            image_preprocess();
            //BandW_threshold = otsuThreshold_fast(mt9v03x_image[0]);
            BandW_threshold = adaptive_otsuThreshold(mt9v03x_image[0]);
            Set_image_towvalues(BandW_threshold);
            Find_Mid_Line(mt9v03x_image_BandW);

            // 计算角度偏差
            Calculate_Track_Error();
            BD_ctrl(-Angle_Error);
            ips200_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 240, 180, BandW_threshold);
            Find_Mid_Line_Draw_Line();

            // 显示角度信息（白色文字）
            char angle_str[30];
            sprintf(angle_str, "Angle: %.1f deg", Angle_Error);
            ips200_show_string(8*0, 16*11, angle_str);

            // 显示中线位置（调试用）
            sprintf(angle_str, "Mid: %d", mid_line_list[MT9V03X_H-5]);
            ips200_show_string(8*0, 16*12, angle_str);
            if(current_point >= BRIDGE_END_POINT)
            {
                bridge_mode = 0;
                break;
            }
            mt9v03x_finish_flag = 0;
        }
    }
}
//===================================================图像角度计算===================================================

void GO_car(void)
{
    uint8 bridge_mode = 0;  // 0-正常模式 1-桥洞模式
    GPS_array_get_point();
    if(IMU963_1_Open_flag==1)
    {
        for(int current_point = 0; current_point < Point_num; current_point++)
        {

            N = current_point;
            if(current_point == BRIDGE_START_POINT)
            {
                bridge_mode = 1;  // 进入桥洞模式
                BLDC_ctrl(800);   // 进入前减速
                system_delay_ms(500);
            }
            while(1)
            {
                if(bridge_mode)
                {
                    // 桥洞内使用视觉导航
                    image_control(current_point);

                    // 检查是否到达结束点
                    if(current_point >= BRIDGE_END_POINT || !bridge_mode)
                    {
                        break;
                    }
                }
                else
                {
                    Follow_track();
                    // 转向控制（增加方向输出限制）
                    BD_ctrl(Nomal_Error);
                    // 动态速度控制
                    if(Distance > 5.0)BLDC_ctrl(1500);  // 高速模式
                    else if(Distance > 2.0)BLDC_ctrl(1000);   // 中速模式
                    else BLDC_ctrl(800);   // 低速精调
                }
                // 到达判定（增加角度容差）
                if(!bridge_mode && Distance < 2.0 && fabs(Nomal_Error) < 5.0)
                {
                     BLDC_ctrl(0);
                     Steer_set(SERVO_MOTOR_MID);
                     system_delay_ms(30);
                     break;
                }
                //system_delay_ms(20);
             }
            //桥动处理结束
            if( current_point==BRIDGE_END_POINT)
            {
                bridge_mode = 0;
                BLDC_ctrl(1000);
            }
         }
         // 完成所有点后停车
         BLDC_ctrl(0);
         Steer_set(SERVO_MOTOR_MID);
         Buzzer_check(1000);  // 提示音

    }
}
