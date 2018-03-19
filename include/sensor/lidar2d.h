/* Created sensor/lidar2d.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SENSOR_LIDAR2D_H_
#define _SENSOR_LIDAR2D_H_

#include <vector>
#include <type/point2d.h>

namespace sgbot {
namespace sensor {

  class Lidar2D {
  public:
    // Define constructor
    Lidar2D() {};

    // Define destructor
    virtual ~Lidar2D() {};

    // Member functions
    void addBeam(double angle, double distance)
    {

    }

    void addPoint(Point2D point)
    {

    }

    void addPoint(double x, double y)
    {

    }

    size_t count()
    {
      return points_.size();
    }

    Point2D getPoint(int index)
    {

    }

    void clear()
    {
      points_.clear();
    }
  private:
    std::vector<Point2D> points_;
  };
}  // namespace sgbot
}  // namespace sensor

#endif  // _SENSOR_LIDAR2D_H_
