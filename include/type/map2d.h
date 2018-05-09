/* Created type/map2d.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _TYPE_MAP2D_H_
#define _TYPE_MAP2D_H_

#include <common/exception.h>
#include <type/point2d.h>

namespace sgbot {

  typedef enum {
    UNKNOWN_MAP_POINT = 0,
    KNOWN_MAP_POINT,
    OBSTACLE_MAP_POINT,
  } MapPointType;

  class Map2D {
  public:
    Map2D()
      : width_(0), height_(0), resolution_(0.0f)
    {}

    Map2D(int width, int height, Point2D origin, float resolution)
      : width_(width), height_(height), origin_(origin), resolution_(resolution)
    {
      resize(width, height);
    }
    
    virtual ~Map2D() {}

    void updateAsKnown(int x, int y)
    {
      points_[x][y] = KNOWN_MAP_POINT;
    }

    void updateAsUnknown(int x, int y)
    {
      points_[x][y] = UNKNOWN_MAP_POINT;
    }

    void updateAsEdge(int x, int y)
    {
      points_[x][y] = OBSTACLE_MAP_POINT;
    }

    void resize(int width, int height)
    {
      points_.resize(width);
      for(int i = 0; i < points_.size(); i++)
      {
        points_[i].resize(height);
      }

      for(int i = 0; i < points_.size(); i++)
      {
        for(int j = 0; j < points_[i].size(); j++)
        {
          points_[i][j] = UNKNOWN_MAP_POINT;
        }
      }
    }

    MapPointType getPoint(int x, int y) const
    {
      return points_[x][y];
    }

    const int getWidth() const
    {
      return width_;
    }

    const int getHeight() const
    {
      return height_;
    }

    const float getResolution() const
    {
      return resolution_;
    }

    const Point2D getOrigin() const
    {
      return origin_;
    }

    bool isKnown(int x, int y) const
    {
      return (points_[x][y] == KNOWN_MAP_POINT);
    }

    bool isUnknown(int x, int y) const
    {
      return (points_[x][y] == UNKNOWN_MAP_POINT);
    }

    bool isEdge(int x, int y) const
    {
      return (points_[x][y] == OBSTACLE_MAP_POINT);
    }
    
  public:
    int width_, height_;
    float resolution_;
    std::vector<std::vector<MapPointType> > points_;
    Point2D origin_;
    
  };  // class Map2D

}  // namespace sgbot

#endif  // _TYPE_GRIDMAP_H_
