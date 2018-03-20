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

  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

