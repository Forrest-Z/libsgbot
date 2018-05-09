/* Created slam/hector/slam/processor.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#include <slam/hector/slam/processor.h>
#include <std-math/gadgets.h>
#include <common/draw.h>

namespace sgbot {
namespace slam {
namespace hector {

  void SlamProcessor::update(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& pose_hint_world, bool need_matching)
  {
    sgbot::Pose2D new_world_pose;

    // debug
    //std::cout << "pose hit world: " << pose_hint_world << std::endl;

    if(!need_matching)
    {
      new_world_pose = pose_hint_world;
    }
    else
    {
      new_world_pose = map_representation_->scanMatch(pose_hint_world, scan, last_scanmatch_covariance_);
    }

    // debug
    //std::cout << "new world pose: " << new_world_pose << std::endl;

    last_scanmatch_pose_ = new_world_pose;

    // TODO : confirm need_matching logic is correct
    if(sgbot::math::farAwayBetweenPoses(new_world_pose, last_update_pose_, update_distance_threshold_, update_theta_threshold_) || !need_matching)
    {
      // debug
      //std::cout << "far enough..." << std::endl;

      map_representation_->updateByScan(scan, new_world_pose);
      map_representation_->onMapUpdated();
      last_update_pose_ = new_world_pose;
    }
  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

