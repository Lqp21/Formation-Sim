#include "robot.h"

double robot_wrapper::m = AUV_m;
double robot_wrapper::rgb=AUV_rgb;
double robot_wrapper::Gravity=m*g;   // 重力
double robot_wrapper::Buoyancy=Gravity;  // 浮力等于重力，或者略大于重力也行

real_2d_array robot_wrapper::addmassM;
// 线性阻尼参数矩阵
real_2d_array robot_wrapper::Dr_linear;
// 二次阻尼参数矩阵
real_2d_array robot_wrapper::Dr_quad;

real_1d_array robot_wrapper::r_g;
real_2d_array robot_wrapper::I_g;

real_2d_array robot_wrapper::M;
real_2d_array robot_wrapper::inM;
real_2d_array robot_wrapper::M11;
real_2d_array robot_wrapper::M12;
real_2d_array robot_wrapper::M21;
real_2d_array robot_wrapper::M22;
real_2d_array robot_wrapper::zeros_33;

robot_wrapper::robot_wrapper(){}

void robot_wrapper::Robot_Init()
{
    real_2d_array my_r_g, MRB, eyes_33;
    ae_int_t info;
    matinvreport rep;

    addmassM="[[30,0,0,0,0,0],[0,40,0,0,0,0],[0,0,30,0,0,0],[0,0,0,1,0,0], [0,0,0,0,1,0],[0,0,0,0,0,1]]";
    // 线性阻尼参数矩阵
    Dr_linear="[[40,0,0,0,0,0],[0,25,0,0,0,0],[0,0,25,0,0,0],[0,0,0,40,0,0], [0,0,0,0,15,0],[0,0,0,0,0,5]]";
    // 二次阻尼参数矩阵
    Dr_quad="[[50,0,0,0,0,0],[0,25,0,0,0,0],[0,0,25,0,0,0],[0,0,0,40,0,0], [0,0,0,0,15,0],[0,0,0,0,0,15]]"; 

    r_g = "[0,0,0]";
    I_g = "[[0.7,0,0],[0,0.9,0],[0,0,1.0]]";

    // 初始化eyes_33
    matrix_eyes(3, eyes_33);
    
    // 初始化M
    my_smtrx(my_r_g,r_g);
    MRB.setlength(6,6);
    rmatrixgencopy(3, 3,  m, eyes_33, 0, 0, 0, MRB, 0, 0);
    rmatrixgencopy(3, 3, -m,  my_r_g, 0, 0, 0, MRB, 0, 3);
    rmatrixgencopy(3, 3,  m,  my_r_g, 0, 0, 0, MRB, 3, 0);
    rmatrixgencopy(3, 3,  1,     I_g, 0, 0, 0, MRB, 3, 3);
    M.setlength(6,6);
    rmatrixgencopy(6, 6, 1,      MRB, 0, 0, 0, M, 0, 0);
    rmatrixgencopy(6, 6, 1, addmassM, 0, 0, 1, M, 0, 0);
    
    // 初始化inM
    inM.setlength(6,6);
    inM=M;
    rmatrixinverse(inM, 6, info, rep);

    // 初始化M11,M12,M21,M22
    M11.setlength(3,3);
    rmatrixcopy(1, 3, M, 0, 0, M11, 0, 0);
    rmatrixcopy(1, 3, M, 0, 0, M11, 1, 0);
    rmatrixcopy(1, 3, M, 0, 0, M11, 2, 0);
    M12.setlength(3,3);
    rmatrixcopy(3, 3, M, 0, 3, M12, 0, 0);
    M21.setlength(3,3);
    rmatrixcopy(3, 3, M, 3, 0, M21, 0, 0);
    M22.setlength(3,3);
    rmatrixcopy(3, 3, M, 3, 3, M22, 0, 0);

    // 初始化3*3的0矩阵
    zeros_33.setlength(3,3);
    matrix_zeros(3,zeros_33);
}


// void robot_wrapper::Robot_Init()
// {
//     real_2d_array my_r_g, MRB, eyes_33;
//     ae_int_t info;
//     matinvreport rep;

//     addmassM="[[30,0,0,0,0,0],[0,40,0,0,0,0],[0,0,30,0,0,0],[0,0,0,1,0,0], [0,0,0,0,1,0],[0,0,0,0,0,1]]";
//     // 线性阻尼参数矩阵
//     Dr_linear="[[40,0,0,0,0,0],[0,25,0,0,0,0],[0,0,25,0,0,0],[0,0,0,40,0,0], [0,0,0,0,15,0],[0,0,0,0,0,5]]";
//     // 二次阻尼参数矩阵
//     Dr_quad="[[50,0,0,0,0,0],[0,25,0,0,0,0],[0,0,25,0,0,0],[0,0,0,40,0,0], [0,0,0,0,15,0],[0,0,0,0,0,15]]"; 
    
//     // 初始化eyes_33
//     matrix_eyes(3, eyes_33);
    
//     // 初始化M
//     my_smtrx(my_r_g,r_g);
//     MRB.setlength(6,6);
//     rmatrixgencopy(3, 3,  m, eyes_33, 0, 0, 0, MRB, 0, 0);
//     rmatrixgencopy(3, 3, -m,  my_r_g, 0, 0, 0, MRB, 0, 3);
//     rmatrixgencopy(3, 3,  m,  my_r_g, 0, 0, 0, MRB, 3, 0);
//     rmatrixgencopy(3, 3,  1,     I_g, 0, 0, 0, MRB, 3, 3);
//     M.setlength(6,6);
//     rmatrixgencopy(6, 6, 1,      MRB, 0, 0, 0, M, 0, 0);
//     rmatrixgencopy(6, 6, 1, addmassM, 0, 0, 1, M, 0, 0);
    
//     // 初始化inM
//     inM.setlength(6,6);
//     inM=M;
//     rmatrixinverse(inM, 6, info, rep);

//     // 初始化M11,M12,M21,M22
//     M11.setlength(3,3);
//     rmatrixcopy(1, 3, M, 0, 0, M11, 0, 0);
//     rmatrixcopy(1, 3, M, 0, 0, M11, 1, 0);
//     rmatrixcopy(1, 3, M, 0, 0, M11, 2, 0);
//     M12.setlength(3,3);
//     rmatrixcopy(3, 3, M, 0, 3, M12, 0, 0);
//     M21.setlength(3,3);
//     rmatrixcopy(3, 3, M, 3, 0, M21, 0, 0);
//     M22.setlength(3,3);
//     rmatrixcopy(3, 3, M, 3, 3, M22, 0, 0);

//     // 初始化3*3的0矩阵
//     zeros_33.setlength(3,3);
//     matrix_zeros(3,zeros_33);
// }

void robot_wrapper::Show_Robot_Info()
{
    
    cout << "AUV_m: "  << m << endl;
    cout << "AUV_rbg: "  << rgb << endl;
    cout << "AUV_Gravity: "  << Gravity << endl;
    cout << "AUV_Buoyancy: " << Buoyancy<< endl;

    cout << "M: " << endl << M.tostring(2) << endl;
    cout << "inM: " << endl << inM.tostring(2) << endl;
    cout << "M11: " << endl << M11.tostring(2) << endl;
    cout << "M12: " << endl << M12.tostring(2) << endl;
    cout << "M21: " << endl << M21.tostring(2) << endl;
    cout << "M22: " << endl << M22.tostring(2) << endl;
    cout << "zeros_33: " << endl << zeros_33.tostring(2) << endl;
}


// void Dynamic(real_1d_array &acc_b,
//             const real_1d_array &T,
//             const real_1d_array &V_b,
//             const double &pitch,
//             const double &roll)
// {



// }

