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

  sgbot::Pose2D ScanMatcher::scanMatch(OccupancyGridMapOptimizer& optimizer, const sgbot::Pose2D& estimation_world_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& covariance, const int max_iteration_times)
  {
    if(scan.getCount() > 0)
    {
      sgbot::Pose2D estimate_map_pose = optimizer.getMapPose(estimation_world_pose);

      estimateTransformation(optimizer, estimate_map_pose, scan);
    }
  }

  bool ScanMatcher::estimateTransformation(OccupancyGridMapOptimizer& optimizer, sgbot::Pose2D& estimation, const sgbot::sensor::Lidar2D& scan)
  {
    optimizer.getCompleteHessianDerivs(estimation, scan, hessian_, delta_tf_);

    if((hessian_(0, 0) != 0.0f) && (hessian_(1, 1) != 0.0f))
    {
      float dummy;
      sgbot::la::Vector<float, 3> d_tf_vec;
      delta_tf_.getValue(d_tf_vec(0), d_tf_vec(1), d_tf_vec(2), dummy);

      sgbot::la::Vector<float, 3> search_dir = (hessian_.inverse() * d_tf_vec);

      // TODO: there must be some better idea here, use other estimate method?
      if(search_dir(2) > 0.2f)
      {
        search_dir(2) = 0.2f;
      }
      else if(search_dir(2) < -0.2f)
      {
        search_dir(2) = -0.2f;
      }

      updateEstimation(estimation, search_dir(0), search_dir(1), search_dir(2));
      return true;
    }
    return false;
  }

  void ScanMatcher::updateEstimation(sgbot::Pose2D& estimation, float dx, float dy, float dth)
  {
    estimation.x() += dx;
    estimation.y() += dy;
    estimation.theta() += dth;
  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

