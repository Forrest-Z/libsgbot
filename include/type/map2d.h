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

namespace sgbot {

  typedef enum {
    UNKNOWN_MAP_POINT = 0,
    KNOWN_MAP_POINT,
    OBSTACLE_MAP_POINT,
  } MapPointType;

  class Map2D {
  public:
    Map2D()
      : width_(0), height_(0)
    {}

    Map2D(int width, int height)
      : width_(width), height_(height)
    {}
    
    virtual ~Map2D() {}

    void updateAsKnown(int x, int y)
    {

    }

    void updateAsUnknown(int x, int y)
    {

    }

    void updateAsEdge(int x, int y)
    {

    }

    MapPointType getPoint(int x, int y) const
    {

    }
    
  public:
    int width_, height_;
    char** points_;
  };  // class Map2D

}  // namespace sgbot

#endif  // _TYPE_GRIDMAP_H_
