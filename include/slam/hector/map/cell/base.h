/* Created slam/hector/map/cell/base.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_CELL_BASE_H_
#define _SLAM_HECTOR_MAP_CELL_BASE_H_

#include <common/exception.h>

namespace sgbot {
namespace slam {
namespace hector {

  class CellBase {
  public:
    
    virtual ~CellBase() {}

    virtual bool isOccupied() const = 0;

    virtual bool isFree() const = 0;

    virtual void reset() = 0;

  public:
    float value;
    int index;
  };  // class CellBase

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_CELL_BASE_H_
