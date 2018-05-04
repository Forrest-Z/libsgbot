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

    Lidar2D operator =(const Lidar2D& other) const
    {
      Lidar2D result;
      
      result.origin_ = other.getOrigin();
      
      result.points_.resize(other.getCount());

      for(int i = 0; i < result.points_.size(); ++i)
      {
        result.points_[i] = other.getPoint(i);
      }

      return result;
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

    Lidar2D& operator *=(float factor)
    {
      origin_ *= factor;
      for(int i = 0; i < points_.size(); i++)
      {
        points_[i] *= factor;
      }
      return *this;
    }

    Lidar2D& operator /=(float factor)
    {
      origin_ /= factor;
      for(int i = 0; i < points_.size(); i++)
      {
        points_[i] /= factor;
      }
      return *this;
    }

    Lidar2D operator *(float factor) const
    {
      Lidar2D result = *this;
      result.origin_ *= factor;
      for(int i = 0; i < result.points_.size(); i++)
      {
        result.points_[i] *= factor;
      }
      return result;
    }

    Lidar2D operator /(float factor) const
    {
      Lidar2D result = *this;
      result.origin_ /= factor;
      for(int i = 0; i < result.points_.size(); i++)
      {
        result.points_[i] /= factor;
      }
      return result;
    }

    const sgbot::Point2D& getOrigin() const
    {
      return origin_;
    }

    void setOrigin(const sgbot::Point2D& origin)
    {
      origin_ = origin;
    }

  protected:
    std::vector<sgbot::Point2D> points_;
    sgbot::Point2D origin_;
  };

  inline std::ostream& operator <<(std::ostream& output, const Lidar2D& scan)
  {
    output << "[" << std::endl;
    output << "  point cout: " << scan.getCount() << std::endl;
    output << "  origin    : " << scan.getOrigin().x() << " , " << scan.getOrigin().y() << std::endl;

    for(int i = 0; i < scan.getCount(); i++)
    {
      output << "(" << scan.getPoint(i).x() << "," << scan.getPoint(i).y() << ") , ";
    }

    output << std::endl;
    
    output << "]" << std::endl;
    return output;
  }

}  // namespace sgbot
}  // namespace sensor

#endif  // _SENSOR_LIDAR2D_H_
