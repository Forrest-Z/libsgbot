/* Created slam/hector/slam/scanmatcher.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#include <slam/hector/slam/scanmatcher.h>

namespace sgbot {
namespace slam {
namespace hector {

  sgbot::Pose2D ScanMatcher::scanMatch(const sgbot::Pose2D& estimation_world_pose, const OccupancyGridMap& gridmap, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& covariance, const int max_iteration_times)
  {

  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

