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

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

