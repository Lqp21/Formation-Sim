// // // #include<iostream>
// // // #include "linalg.h"

// // // using namespace std;

// // // int main()
// // // {
// // //     alglib::real_2d_array a("[[1]]");
// // //     alglib::spdmatrixcholesky(a, 1, true);
// // //     cout << "OK" << endl;
// // //     return 0;
// // // }

// // #include <stdio.h>
// // #include <windows.h>
// // #include "LinAlg.h"

// // double counter()
// // {
// //     return 0.001*GetTickCount();
// // }

// // int main()
// // {
// //     alglib::real_2d_array a, b, c;
// //     int n = 2000;
// //     int i, j;
// //     double timeneeded, flops;
    
// //     // Initialize arrays
// //     a.setlength(n, n);
// //     b.setlength(n, n);
// //     c.setlength(n, n);
// //     for(i=0; i<n; i++)
// //         for(j=0; j<n; j++)
// //         {
// //             a[i][j] = alglib::randomreal()-0.5;
// //             b[i][j] = alglib::randomreal()-0.5;
// //             c[i][j] = 0.0;
// //         }
    
// //     // Set global threading settings (applied to all ALGLIB functions);
// //     // default is to perform serial computations, unless parallel execution
// //     // is activated. Parallel execution tries to utilize all cores; this
// //     // behavior can be changed with alglib::setnworkers() call.
// //     alglib::setglobalthreading(alglib::parallel);
    
// //     // Perform matrix-matrix product.
// //     flops = 2*pow((double)n, (double)3);
// //     timeneeded = counter();
// //     alglib::rmatrixgemm(
// //         n, n, n,
// //         1.0,
// //         a, 0, 0, 0,
// //         b, 0, 0, 1,
// //         0.0,
// //         c, 0, 0);
// //     timeneeded = counter()-timeneeded;
    
// //     // Evaluate performance
// //     printf("Performance is %.1f GFLOPS\n", (double)(1.0E-9*flops/timeneeded));
    
// //     return 0;
// // }

// #include "stdafx.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <math.h>
// #include "linalg.h"

// using namespace alglib;


// int main(int argc, char **argv)
// {
//     real_2d_array a = "[[1,-1],[1,1]]";
//     ae_int_t info;
//     matinvreport rep;
//     rmatrixinverse(a, info, rep);
//     printf("%d\n", int(info)); // EXPECTED: 1
//     printf("%s\n", a.tostring(2).c_str()); // EXPECTED: [[0.5,0.5],[-0.5,0.5]]
//     printf("%.4f\n", double(rep.r1)); // EXPECTED: 0.5
//     printf("%.4f\n", double(rep.rinf)); // EXPECTED: 0.5

//     std::cout << a.tostring(2).c_str() << std::endl;
//     std::cout << "a.tostring(2)" << std::endl;
//     std::cout << a.tostring(2) << std::endl;
//     return 0;
    
// }