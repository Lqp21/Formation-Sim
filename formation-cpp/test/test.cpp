#include "robot.h"


int main()
{
    robot_wrapper::Robot_Init();
    robot_wrapper::Show_Robot_Info();
    // real_2d_array b = "[[1,-1],[1,1]]";
    // matrix_eyes(2,b);
    // std::cout << b.tostring(2) << std::endl;

    
    return 0;
}


// int main()
// { 
   
//     ae_int_t info;
//     matinvreport rep;

//     real_2d_array I_g = "[[0.7,0,0],[0,0.9,0],[0,0,1.0]]";
//     real_1d_array r_g = "[0,0,0]";
//     int Xua=30,Yva=40,Zwa=30,Kpa=1,Mqa=1,Nra=1;     //附加质量
//     int Xu=40,Yv=25,Zw=25,Kp=40,Mq=15,Nr=5;         //一次阻尼系数
//     int Xuu=50,Yvv=25,Zww=25,Kpp=40,Mqq=15,Nrr=15;  //二次阻尼系数
    
//     real_2d_array addmassM="[[30,0,0,0,0,0],[0,40,0,0,0,0],[0,0,30,0,0,0],[0,0,0,1,0,0], [0,0,0,0,1,0],[0,0,0,0,0,1]]";
//     // 线性阻尼参数矩阵
//     real_2d_array Dr_linear="[[40,0,0,0,0,0],[0,25,0,0,0,0],[0,0,25,0,0,0],[0,0,0,40,0,0], [0,0,0,0,15,0],[0,0,0,0,0,5]]";
//     // 二次阻尼参数矩阵
//     real_2d_array Dr_quad="[[50,0,0,0,0,0],[0,25,0,0,0,0],[0,0,25,0,0,0],[0,0,0,40,0,0], [0,0,0,0,15,0],[0,0,0,0,0,15]]"; 
    
//     real_2d_array MRB, M, inM, eyes_3, my_r_g;
//     matrix_eyes(3, eyes_3);
//     cout << "eyes_3: " << endl << eyes_3.tostring(2) << endl;

//     my_smtrx(my_r_g,r_g);
//     cout << "my_r_g: " << endl << my_r_g.tostring(2) << endl;

//     MRB.setlength(6,6);
//     rmatrixgencopy(3, 3,  m, eyes_3, 0, 0, 0, MRB, 0, 0);
//     rmatrixgencopy(3, 3, -m, my_r_g, 0, 0, 0, MRB, 0, 3);
//     rmatrixgencopy(3, 3,  m, my_r_g, 0, 0, 0, MRB, 3, 0);
//     rmatrixgencopy(3, 3,  1,    I_g, 0, 0, 0, MRB, 3, 3);
//     cout << "MRB: " << endl << MRB.tostring(2) << endl;

//     M.setlength(6,6);
//     rmatrixgencopy(6, 6, 1,      MRB, 0, 0, 0, M, 0, 0);
//     rmatrixgencopy(6, 6, 1, addmassM, 0, 0, 1, M, 0, 0);
//     cout << "M: " << endl << M.tostring(2) << endl;

//     inM.setlength(6,6);
//     inM=M;
//     rmatrixinverse(inM, 6, info, rep);
//     cout << "inM: " << endl << inM.tostring(2) << endl;

    
// }