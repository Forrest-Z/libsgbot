/* Created slam/hector/slam/scanmatcher.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_SLAM_SCANMATCHER_H_
#define _SLAM_HECTOR_SLAM_SCANMATCHER_H_

#include <common/exception.h>
#include <type/pose2d.h>
#include <sensor/lidar2d.h>
#include <linear-algebra/matrix.h>
#include <slam/hector/map/occupancy-gridmap/map.h>
#include <slam/hector/map/occupancy-gridmap/optimizer.h>

namespace sgbot {
namespace slam {
namespace hector {

  class ScanMatcher {
  public:

    ScanMatcher() {}
    virtual ~ScanMatcher() {}

    sgbot::Pose2D scanMatch(OccupancyGridMapOptimizer& optimizer, const sgbot::Pose2D& estimation_world_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& covariance, const int max_iteration_times);
  
  protected:

    sgbot::la::Matrix<float, 3, 3> hessian_;

    bool estimateTransformation(OccupancyGridMapOptimizer& optimizer, sgbot::Pose2D& estimation, const sgbot::sensor::Lidar2D& scan);

    void updateEstimation(sgbot::Pose2D& estimation, float dx, float dy, float dth);

  };  // ScanMatcher

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_SLAM_SCANMATCHER_H_
