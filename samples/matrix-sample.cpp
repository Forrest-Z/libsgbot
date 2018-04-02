//
// Created by root on 18-3-29.
//
#include <linear-algebra/matrixbase.h>
#include <linear-algebra/matrix.h>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

int main(int argc,char* argv[])
{
    sgbot::la::Matrix<double, 3, 3> a;
    a(0, 0) = 1.0f;
    a(0, 1) = 2.0f;
    a(0, 2) = 3.0f;
    a(1, 0) = 6.0f;
    a(1, 1) = 5.0f;
    a(1, 2) = 4.0f;
    a(2, 0) = 8.0f;
    a(2, 1) = 7.0f;
    a(2, 2) = 9.0f;
    
    std::cout << a;

    sgbot::la::Matrix<double, 3, 3> b = a;

    std::cout << b;

    std::cout << "det: " << a.determinant() << std::endl;

    sgbot::la::Matrix<double, 3, 3> c = a.inverse();
    std::cout << "inverse: " << c;

    std::cout << "transpose: " << a.transpose();

    std::cout << "+1: " << (a + 1);
    std::cout << "-1: " << (a - 1);
    std::cout << "x2: " << (a * 2);
    std::cout << "/2: " << (a / 2);

    std::cout << "multi: " << std::fixed << std::setprecision(1) << (a * c);
}
