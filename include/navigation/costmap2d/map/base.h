/* Created navigation/costmap2d/map/base.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _NAVIGATION_COSTMAP2D_MAP_BASE_H_
#define _NAVIGATION_COSTMAP2D_MAP_BASE_H_

#include <vector>
#include <common/exception.h>
#include <navigation/costmap2d/def.h>
#include <type/point2d.h>

#include <boost/thread.hpp>

namespace sgbot {
namespace nav {

  class Costmap2D {
  public:

    /*
     * Constractors
     */
    Costmap2D(int width, int height, float resolution, sgbot::Point2D origin)
      : width_(width), height_(height), resolution_(resolution), origin_(origin), cells_(NULL)
    {
      lock_ = new boost::recursive_mutex();
      createMap();
      reset();
    }

    Costmap2D(const Costmap2D& other)
      : cells_(NULL)
    {
      lock_ = new boost::recursive_mutex();
      *this = other;
    }

    Costmap2D()
      : width_(0), height_(0), resolution_(0.0f), cells_(NULL)
    {
      lock_ = new boost::recursive_mutex();
      origin_.x() = 0.0f;
      origin_.y() = 0.0f;
    }

    /*
     * Copy operator
     */
    Costmap2D& operator =(const Costmap& other)
    {
      if(this == &other)
        return *this;

      deleteMap();
      
      width_ = other.width_;
      height_ = other.height_;
      resolution_ = other.resolution_;
      origin_ = other.origin_;

      createMap();

      int index = 0;
      for(int x = 0; x < other.width_; x++)
      {
        for(int y = 0; y < other.height_; y++)
        {
          cells_[index] = other.cells_[index];
          index++;
        }
      }

      return *this;
    }

    /*
     * Destractor
     */
    virtual ~Costmap2D()
    {
      deleteMap();
      delete lock_;
    }

    /*
     * Member functions
     */
    virtual createMap()
    {
      boost::unique_lock<boost::recursive_mutex> lock(*lock_);
      if(cells_)
      {
        delete[] cells_;
      }
      cells_ = new CostValue[width_ * height_];
    }

    virtual deleteMap()
    {
      boost::unique_lock<boost::recursive_mutex> lock(*lock_);
      if(cells_)
      {
        delete[] cells_;
        cells_ = NULL;
      }
    }

    virtual reset()
    {
      boost::unique_lock<boost::recursive_mutex> lock(*lock_);
      int index = 0;
      for(int x = 0; x < width_; x++)
      {
        for(int y = 0; y < height_; y++)
        {
          cells_[index++] = UNKNOWN_SPACE;
        }
      }
    }

    virtual resize(int width, int height, float resolution, sgbot::Point2D origin)
    {
      width_ = width;
      height_ = height;
      resolution_ = resolution;
      origin_ = origin;

      createMap();
      reset();
    }

    /*
     * map access methods
     */
    CostValue getValue(int x, int y) const
    {
      return cells_[getCellIndex(x, y)];
    }

    void setValue(int x, int y, CostValue value)
    {
      cells_[getCellIndex(x, y)] = value;
    }

    CostValue getValue(int index) const
    {
      return cells_[index];
    }

    void setValue(int index, CostValue value)
    {
      cells_[index] = value;
    }

    /*
     * world coord and map cell exchange functions
     */
    sgbot::la::Vector<int, 2> worldToMap(const sgbot::Point2D& world_point) const
    {
      sgbot::la::Vector<int, 2> map_point;
      
      map_point(0) = static_cast<int>((world_point.x() - origin_.x()) / resolution_);
      map_point(1) = static_cast<int>((world_point.y() - origin_.y()) / resolution_);

      return map_point;
    }

    sgbot::Point2D mapToWorld(const sgbot::la::Vector<int, 2>& map_point) const
    {
      sgbot::Point2D world_point;
      
      world_point.x() = static_cast<float>(origin_.x() + (map_point(0) + 0.5f) * resolution_);
      world_point.y() = static_cast<float>(origin_.y() + (map_point(1) + 0.5f) * resolution_);

      return world_point;
    }

    int getWidth() const
    {
      return width_;
    }

    int getHeight() const
    {
      return height_;
    }

    sgbot::Point2D getOrigin() const
    {
      return origin_;
    }

    float getResolution() const
    {
      return resolution_;
    }

    int cellDistance(float world_distance)
    {
      float cells_dist = max(0.0f, sgbot::math::ceil(world_distance / resolution_));
      return static_cast<int>(cells_dist);
    }

    inline int getCellIndex(int x, int y) const
    {
      return (x * width_ + y);
    }

    inline void getCellCoords(const int index, int& x, int& y)
    {
      y = index / width_;
      x = index - (y * width_);
    }

  protected:
    int width_, height_;
    float resolution_;
    sgbot::Point2D origin_;
    CostValue* cells_;

    boost::recursive_mutex* lock_;
  };  // class Costmap2D

}  // namespace nav
}  // namespace sgbot

#endif  // _NAVIGATION_COSTMAP2D_MAP_BASE_H_
