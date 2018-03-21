/* Created slam/hector/map/occupancy-gridmap/optimizer.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#include <slam/hector/map/occupancy-gridmap/optimizer.h>

namespace sgbot {
namespace slam {
namespace hector {

  void OccupancyGridMapOptimizer::getCompleteHessianDerivs(const sgbot::Pose2D& estimate_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& hessian, sgbot::tf::Transform2D& delta_transformation)
  {

  }

  sgbot::la::Matrix<float, 3, 3> OccupancyGridMapOptimizer::getPoseCovariance(const sgbot::Pose2D& map_pose, const sgbot::sensor::Lidar2D& scan)
  {

  }

  sgbot::la::Matrix<float, 3, 3> OccupancyGridMapOptimizer::getWorldCoordsCovariance(const sgbot::la::Matrix<float, 3, 3>& map_coords_cov)
  {

  }

  float OccupancyGridMapOptimizer::getStateResidual(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points)
  {

  }

  float OccupancyGridMapOptimizer::getResidualLikelihood(float residual, int scan_points_count)
  {

  }

  float OccupancyGridMapOptimizer::getStateLikelihood(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points)
  {

  }

  float OccupancyGridMapOptimizer::getInterpMapValue(const sgbot::Point2D& coords)
  {

  }

  bool OccupancyGridMapOptimizer::interpMapValueWithDerivatives(const sgbot::Point2D& coords, float& occupancy_value, float& derivative_x, float& derivative_y)
  {

  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

