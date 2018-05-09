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
      surround_point_intensities[0] = 0.0f;
      surround_point_intensities[1] = 0.0f;
      surround_point_intensities[2] = 0.0f;
      surround_point_intensities[3] = 0.0f;
    }

    virtual ~OccupancyGridMapOptimizer() {}

    void getCompleteHessianDerivs(const sgbot::Pose2D& estimate_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& hessian, sgbot::la::Vector<float, 3>& delta_tf);
    
    sgbot::la::Matrix<float, 3, 3> getPoseCovariance(const sgbot::Pose2D& map_pose, const sgbot::sensor::Lidar2D& scan);

    sgbot::la::Matrix<float, 3, 3> getWorldCoordsCovariance(const sgbot::la::Matrix<float, 3, 3>& map_coords_cov);

    float getStateResidual(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points);

    float getResidualLikelihood(float residual, int scan_points_count);

    float getStateLikelihood(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points);

    float getInterpMapValue(const sgbot::Point2D& coords);

    bool interpMapValueWithDerivatives(const sgbot::Point2D& coords, float& occupancy_value, float& derivative_x, float& derivative_y);

    inline sgbot::Point2D getWorldCoords(const sgbot::Point2D& map_coords) const
    {
      return gridmap_->getWorldCoords(map_coords);
    }

    inline sgbot::Point2D getMapCoords(const sgbot::Point2D& world_coords) const
    {
      return gridmap_->getMapCoords(world_coords);
    }

    inline sgbot::Pose2D getWorldPose(const sgbot::Pose2D& map_pose) const
    {
      return gridmap_->getWorldPose(map_pose);
    }

    inline sgbot::Pose2D getMapPose(const sgbot::Pose2D& world_pose) const
    {
      return gridmap_->getMapPose(world_pose);
    }

    inline sgbot::tf::Transform2D getStateTransform(const sgbot::Pose2D& pose) const
    {
      return sgbot::tf::Transform2D(pose.x(), pose.y(), pose.theta(), 1.0f);
    }

    float getCellProbability(const int index) const
    {
      return gridmap_->getCellProbability(index);
    }

    void resetCache()
    {
      cache_.resetCache();
    }

  protected:
    OccupancyGridMap* gridmap_;
    GridMapCache cache_;
    
    float surround_point_intensities[4];
  };  // class OccupancyGridMapOptimizer

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_OPTIMIZER_H_
