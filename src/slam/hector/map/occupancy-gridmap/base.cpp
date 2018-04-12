/* Created slam/hector/map/occupancy-gridmap/base.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#include <slam/hector/map/occupancy-gridmap/base.h>

namespace sgbot {
namespace slam {
namespace hector {

  template <typename CellType, typename CellFactor>
  void OccupancyGridMapBase<CellType, CellFactor>::updateByScan(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& world_pose)
  {

  }

  template <typename CellType, typename CellFactor>
  void OccupancyGridMapBase<CellType, CellFactor>::updateLine(const int x0, const int y0, const int x1, const int y1, unsigned int max_length)
  {
    if((x0 < 0) || (x0 >= this->getWidth()) || (y0 < 0) || (y0 >= this->getHeight()))
    {
      return;
    }

    if((x1 < 0) || (x1 >= this->getWidth()) || (y1 < 0) || (y1 >= this->getHeight()))
    {
      return;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    unsigned int abs_dx = sgbot::math::abs(dx);
    unsigned int abs_dy = sgbot::math::abs(dy);

    int offset_dx = sgbot::math::sign(dx);
    int offset_dy = sgbot::math::sign(dy) * this->getWidth();

    unsigned int start_offset = y0 * this->getWidth() + x0;

    int error;
    unsigned int abs_a, abs_b;
    int offset_a, offset_b;
    unsigned int offset = start_offset;

    // if x is dominant
    if(abs_dx >= abs_dy)
    {
      // equals to [error = abs_dx / 2]
      error = abs_dx * 0.5f;

      abs_a = abs_dx;
      abs_b = abs_dy;
      offset_a = offset_dx;
      offset_b = offset_dy;
    }
    else
    {
      // equals to [error = abs_dy / 2]
      error = abs_dy * 0.5f;

      abs_a = abs_dy;
      abs_b = abs_dx;
      offset_a = offset_dy;
      offset_b = offset_dx;
    }

    // bresenham draw line algorithm
    updateCellAsFree(offset);
    for(int i = 0; i < (abs_a - 1); ++i)
    {
      offset += offset_a;
      error += abs_b;
      if((unsigned int)error >= abs_a)
      {
        offset += offset_b;
        error -= abs_a;
      }
      updateCellAsFree(offset);
    }
    
    
    unsigned int end_offset = y1 * this->getWidth() + x1;
    updateCellAsOccupied(end_offset);
  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

