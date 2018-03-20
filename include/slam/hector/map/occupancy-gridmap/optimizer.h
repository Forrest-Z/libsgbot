/* Created slam/hector/map/occupancy-gridmap/optimizer.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_OPTIMIZER_H_
#define _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_OPTIMIZER_H_

#include <common/exception.h>
#include <slam/hector/map/occupancy-gridmap/map.h>
#include <slam/hector/map/gridmap/cache.h>
#include <sensor/lidar2d.h>

namespace sgbot {
namespace slam {
namespace hector {

  class OccupancyGridMapOptimizer
  {
  public:
    OccupancyGridMapOptimizer(OccupancyGridMap* gridmap)
      : gridmap_(gridmap)
    {
      cache_.setMapSize(gridmap->getWidth(), gridmap->getHeight());
    }

    virtual ~OccupancyGridMapOptimizer() {}

    void getCompleteHessianDerivs(const sgbot::Pose2D& estimate_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& hessian, sgbot::tf::Transform2D& delta_transformation);

  protected:
    OccupancyGridMap* gridmap_;
    GridMapCache cache_;
  };  // class OccupancyGridMapOptimizer

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_OPTIMIZER_H_
