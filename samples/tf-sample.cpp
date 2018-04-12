//
// Created by root on 18-3-29.
//
#include <transform/transform2d.h>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <cmath>

int main(int argc,char* argv[])
{
    sgbot::tf::Transform2D tf1(1.0f, 2.0f, M_PI / 4, 1.0f);
    sgbot::tf::Transform2D tf2(0.5f, 0.5f, 0.0f, 1.0f);

    sgbot::Pose2D p1(0.5f, 0.5f, M_PI / 8);

    std::cout << "P1:" << p1;

    std::cout << "P1 in TF2" << tf2.transform(p1);

    sgbot::Pose2D p2 = (tf1 * tf2).transform(p1);

    std::cout << p2;

    std::cout << (tf1 * tf1.inverse()).transform(p1);
}

