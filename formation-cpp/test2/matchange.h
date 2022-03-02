#ifndef MATCHANGE_H_
#define MATCHANGE_H_
#include "ap.h"

using namespace alglib;

void my_smtrx(alglib::real_2d_array &out, const alglib::real_1d_array &in);
void vector2diag(const int n, alglib::real_2d_array &out, const alglib::real_1d_array &in);
void matrix_eyes(const int n, alglib::real_2d_array &out);
void matrix_zeros(const int n, alglib::real_2d_array &out);


#endif