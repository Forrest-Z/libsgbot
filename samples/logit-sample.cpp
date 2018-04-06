//
// Created by root on 18-3-29.
//
#include <distribution/functions.h>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

int main(int argc,char* argv[])
{
    float d = 0.4f;
    std::cout << "logit: " << sgbot::distr::logit(d) << std::endl;
    std::cout << "logistic: " << sgbot::distr::logistic(sgbot::distr::logit(d)) << std::endl;
}
