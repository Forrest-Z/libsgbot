//
// Created by root on 18-3-29.
//
#include <linear-algebra/vector.h>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

int main(int argc,char* argv[])
{
    sgbot::la::Vector<float, 3> a;
    a(0) = 3.0f;
    a(1) = 4.0f;

    std::cout << a;

    std::cout << "length: " << a.length();
    
}
