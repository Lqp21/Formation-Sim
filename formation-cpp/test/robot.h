#ifndef ROBOT_H_
#define ROBOT_H_
#include "def.h"
#include "linalg.h"
#include "matchange.h"

using namespace std;

typedef struct robot_state{
    real_1d_array input;
    real_1d_array acc;
    real_1d_array vel;
    real_1d_array pos;
}robot_state;

class robot_wrapper
{
public:
    robot_wrapper();
    static void Robot_Init();
    static void Show_Robot_Info();

private:
    robot_state *ptr; //状态信息


    // // 数据更新频率设置，单位为hz
    // static const int SBL_update_rate=  1; 
    // static const int VO_update_rate=   5; 
    // static const int IMU_update_rate=  200; 
    // static const int MAG_update_rate=  50; 
    // static const int SLAM_update_rate= 2; 
    // static const int press_update_rate=20; 


    // 机器人刚体参数，根据机器人参数确定
    static double m;
    static double rgb;
    static double Gravity;   // 重力
    static double Buoyancy;  // 浮力等于重力，或者略大于重力也行
    static real_1d_array r_g;
    static real_2d_array I_g;
    static real_2d_array addmassM; //附加质量
    static real_2d_array Dr_linear; // 线性阻尼参数矩阵
    static real_2d_array Dr_quad; // 二次阻尼参数矩阵
    static real_2d_array M, inM;
    static real_2d_array M11, M12, M21, M22;
    static real_2d_array zeros_33;
};


#endif