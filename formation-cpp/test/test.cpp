#include<iostream>
#include"linalg.h"
#include"def.h"
#include"robot.h"

using namespace alglib;
using namespace std;

int main()
{

    ae_int_t info;
    matinvreport rep;

    real_2d_array I_g("[[0.7,0,0],[0,0.9,0],[0,0,1.0]]");
    real_1d_array r_g("[0,0,0]");
    int Xuu=50,Yvv=25,Zww=25,Kpp=40,Mqq=15,Nrr=15;  //二次阻尼系数
    int Xu=40,Yv=25,Zw=25,Kp=40,Mq=15,Nr=5;         //一次阻尼系数
    int Xua=30,Yva=40,Zwa=30,Kpa=1,Mqa=1,Nra=1;     //附加质量
    real_2d_array addmassM("[[Xua,0,0,0,0,0],[0,Yva,0,0,0,0],[0,0,Zwa,0,0,0],[0,0,0,Kpa,0,0], [0,0,0,0,Mqa,0],[0,0,0,0,0,Nra]]");
    // 二次阻尼参数矩阵
    real_2d_array Dr_quad("[[Xu,0,0,0,0,0],[0,Yv,0,0,0,0],[0,0,Zw,0,0,0],[0,0,0,Kp,0,0], [0,0,0,0,Mq,0],[0,0,0,0,0,Nr]]");
    // 线性阻尼参数矩阵
    real_2d_array Dr_linear("[[Xuu,0,0,0,0,0],[0,Yvv,0,0,0,0],[0,0,Zww,0,0,0],[0,0,0,Kpp,0,0], [0,0,0,0,Mqq,0],[0,0,0,0,0,Nrr]]");
    real_2d_array MRB, M, inM, eyes_3, my_r_g;
    matrix_eye(3, eyes_3);
    cout << eyes_3.tostring(2).c_str() << endl; 
    cout << "eyes_3: " << endl;
    cout << eyes_3.tostring(2) << endl;

    // my_smtrx(my_r_g,r_g);

    // rmatrixgencopy(3, 3,  m, eyes_3, 0, 0, 0, MRB, 0, 0);
    // rmatrixgencopy(3, 3, -m, my_r_g, 0, 0, 0, MRB, 0, 3);
    // rmatrixgencopy(3, 3,  m, my_r_g, 0, 0, 0, MRB, 3, 0);
    // rmatrixgencopy(3, 3,  1,    I_g, 0, 0, 0, MRB, 3, 3);
    // cout << "MRB: " << endl;
    // cout << MRB.tostring(2).c_str() << endl;

    // rmatrixgencopy(6, 6, 1,      MRB, 0, 0, 0, M, 0, 0);
    // rmatrixgencopy(6, 6, 1, addmassM, 0, 0, 1, M, 0, 0);
    // inM=M;
    // rmatrixinverse(inM, 6, info, rep);

    // cout << "M: " << endl;
    // cout << M.tostring(2).c_str() << endl;
    // cout << "inM: " << endl;
    // cout << inM.tostring(2).c_str() << endl;
    
}