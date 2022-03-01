#ifndef ROBOT_H_
#define ROBOT_H_

#include"ap.h"
#include"linalg.h"



void my_smtrx(alglib::real_2d_array &out, const alglib::real_1d_array &in);
void vector2diag(const int n, alglib::real_2d_array &out, const alglib::real_1d_array &in);
void matrix_eye(const int n, alglib::real_2d_array &out);

#endif