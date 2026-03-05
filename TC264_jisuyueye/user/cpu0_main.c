#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中




int core0_main(void)
{
    ALL_init();

//    Steer_text();                   //舵机测试程序(内部自带死循环,仅在测试时使用,正常使用的时候关掉)
//    MT9V03_text();                  //MT9V03总钻风测试程序(内部自带死循环,仅在测试时使用,正常使用的时候关掉)
//    BLDC_text();                    //无刷电机测试程序(内部自带死循环,仅在测试时使用,正常使用的时候关掉)
//    Motor_text();                   //DRV8701有刷电机测试程序(内部自带死循环,仅在测试时使用,正常使用的时候关掉)
//    Encoder_text();                 //编码器测试程序(内部自带死循环,仅在测试时使用,正常使用的时候关掉,使用时需要打开定时器 pit_ms_init(CCU60_CH0, 1);)
//    GPS_text();                     //GPS测试程序(内部自带死循环,仅在测试时使用,正常使用的时候关掉,使用时需要打开定时器 pit_ms_init(CCU60_CH0, 1);)
//    IMU_text();                     //IMU660测试程序(内部自带死循环,仅在测试时使用,正常使用的时候关掉,使用时需要打开定时器 pit_ms_init(CCU60_CH0, 1);)
//    IMU963_text();                  //IMU963测试程序(内部自带死循环,仅在测试时使用,正常使用的时候关掉,使用时需要打开定时器 pit_ms_init(CCU60_CH0, 1);)
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    while (TRUE)
    {
        GO_car();
    }
}

#pragma section all restore
