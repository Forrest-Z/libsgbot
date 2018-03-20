/* Created slam/hector/map/occupancy-gridmap/map.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_MAP_H_
#define _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_MAP_H_

#include <common/exception.h>
#include <slam/hector/map/cell/logodds.h>
#include <slam/hector/map/occupancy-gridmap/base.h>

namespace sgbot {
namespace slam {
namespace hector {

  typedef OccupancyGridMapBase<LogOddsCell, LogOddsCellFactor> OccupancyGridMap;

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_MAP_H_
