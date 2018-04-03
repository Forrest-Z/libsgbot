//
// Created by root on 18-3-29.
//
#include <transform/transform2d.h>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

int main(int argc,char* argv[])
{
    sgbot::tf::Transform2D tf1(1.0f, 2.0f, 30.0f);
    sgbot::tf::Transform2D tf2(0.5f, 0.5f, 0.0f);

    sgbot::Pose2D p1(0.5f, 0.5f, 15.0f);

    sgbot::Pose2D p2 = (tf1 * tf2).transform(p1);

    std::cout << p2;
}
