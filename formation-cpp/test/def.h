#ifndef DEF_H_
#define DEF_H_
// 仿真参数
#define data_num 10000   // 数据数量
#define step     0.02    // 计算间隔时间，50hz

// 数据更新频率设置，单位为hz
#define SBL_update_rate    1 
#define VO_update_rate     5 
#define IMU_update_rate    200 
#define MAG_update_rate    50 
#define SLAM_update_rate   2 
#define press_update_rate  20 

#define g 9.81

// 机器人刚体参数，根据机器人参数确定
#define m   30
#define rgb 0.025;
#define Gravity m*g;   // weight
#define Buoyancy Gravity;  // 浮力等于重力，或者略大于重力也行

#endif