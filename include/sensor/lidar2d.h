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
#include <std-math/math.h>

namespace sgbot {
namespace sensor {

  class Lidar2D {
  public:
    // Define constructor
    Lidar2D() {};

    // Define destructor
    virtual ~Lidar2D() {};

    // Copy constructor
    Lidar2D(const Lidar2D& other)
    {
      origin_ = other.getOrigin();
      
      points_.resize(other.getCount());

      for(int i = 0; i < points_.size(); ++i)
      {
        points_[i] = other.getPoint(i);
      }
    }

    // Member functions
    void addBeam(float angle, float distance)
    {
      float x = sgbot::math::cos(angle) * distance;
      float y = sgbot::math::sin(angle) * distance;

      addPoint(x, y);
    }

    void addPoint(sgbot::Point2D point)
    {
      points_.push_back(point);
    }

    void addPoint(float x, float y)
    {
      sgbot::Point2D point;
      point.x() = x;
      point.y() = y;

      addPoint(point);
    }

    int getCount() const
    {
      return points_.size();
    }

    const sgbot::Point2D& getPoint(int index) const
    {
      return points_[index];
    }

    void clear()
    {
      points_.clear();
    }

    const sgbot::Point2D& getOrigin() const
    {
      return origin_;
    }

    void setOrigin(const sgbot::Point2D& origin)
    {
      origin_ = origin;
    }

  private:
    std::vector<sgbot::Point2D> points_;
    sgbot::Point2D origin_;
  };
}  // namespace sgbot
}  // namespace sensor

#endif  // _SENSOR_LIDAR2D_H_
