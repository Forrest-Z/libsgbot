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
    
    sgbot::la::Matrix<float, 3, 3> getPoseCovariance(const sgbot::Pose2D& map_pose, const sgbot::sensor::Lidar2D& scan);

    sgbot::la::Matrix<float, 3, 3> getWorldCoordsCovariance(const sgbot::la::Matrix<float, 3, 3>& map_coords_cov);

    float getStateResidual(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points);

    float getResidualLikelihood(float residual, int scan_points_count);

    float getStateLikelihood(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points);

    float getInterpMapValue(const sgbot::Point2D& coords);

    bool interpMapValueWithDerivatives(const sgbot::Point2D& coords, float& occupancy_value, float& derivative_x, float& derivative_y);

  protected:
    OccupancyGridMap* gridmap_;
    GridMapCache cache_;
  };  // class OccupancyGridMapOptimizer

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_OPTIMIZER_H_
