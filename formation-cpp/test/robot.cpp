#include<iostream>
#include"linalg.h"
#include"def.h"

using namespace std;

int main()
{
    int Xuu=50,Yvv=25,Zww=25,Kpp=40,Mqq=15,Nrr=15;  //二次阻尼系数
    int Xu=40,Yv=25,Zw=25,Kp=40,Mq=15,Nr=5;         //一次阻尼系数
    int Xua=30,Yva=40,Zwa=30,Kpa=1,Mqa=1,Nra=1;     //附加质量
    alglib::real_2d_array addmassM("[[Xua,0,0,0,0,0],[0,Yva,0,0,0,0],[0,0,Zwa,0,0,0],[0,0,0,Kpa,0,0], [0,0,0,0,Mqa,0],[0,0,0,0,0,Nra]]");
    // 二次阻尼参数矩阵
    alglib::real_2d_array Dr_quad("[[Xu,0,0,0,0,0],[0,Yv,0,0,0,0],[0,0,Zw,0,0,0],[0,0,0,Kp,0,0], [0,0,0,0,Mq,0],[0,0,0,0,0,Nr]]");
    // 线性阻尼参数矩阵
    alglib::real_2d_array Dr_linear("[[Xuu,0,0,0,0,0],[0,Yvv,0,0,0,0],[0,0,Zww,0,0,0],[0,0,0,Kpp,0,0], [0,0,0,0,Mqq,0],[0,0,0,0,0,Nrr]]");
                            
}

void diag(alglib::real_2d_array* )