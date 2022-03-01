#include"robot.h"

void my_smtrx(alglib::real_2d_array &out, const alglib::real_1d_array &in)
{
    out[0][0] = 0; 
    out[0][1] = -in[3];
    out[0][2] = in[2];

    out[1][0] = in[3]; 
    out[1][1] = 0;
    out[1][2] = -in[1];

    out[2][0] = -in[2]; 
    out[2][1] = in[1];
    out[2][2] = 0; 
}

void vector2diag(const int n, alglib::real_2d_array &out, const alglib::real_1d_array &in)
{
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j) out[i][j]=in[i];
            else out[i][j]=0;
        }
    }
}
void matrix_eye(const int n, alglib::real_2d_array &out)
{
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j) out[i][j]=1;
            else out[i][j]=0;
        }
    }
}
