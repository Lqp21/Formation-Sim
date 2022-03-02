#ifndef DEF_H_
#define DEF_H_
// 仿真参数
const int data_num=10000;   // 数据数量
const double step=0.02;   // 计算间隔时间，50hz

// 数据更新频率设置，单位为hz
const int SBL_update_rate=  1; 
const int VO_update_rate=   5; 
const int IMU_update_rate=  200; 
const int MAG_update_rate=  50; 
const int SLAM_update_rate= 2; 
const int press_update_rate=20; 

const double g=9.81;

// 机器人刚体参数，根据机器人参数确定
const double AUV_m=30;
const double AUV_rgb=0.025;
const int Xua=30,Yva=40,Zwa=30,Kpa=1,Mqa=1,Nra=1;     //附加质量
const int Xu=40,Yv=25,Zw=25,Kp=40,Mq=15,Nr=5;         //一次阻尼系数
const int Xuu=50,Yvv=25,Zww=25,Kpp=40,Mqq=15,Nrr=15;  //二次阻尼系数

#endif