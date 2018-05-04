/* Created slam/hector/slam/processor.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_SLAM_PROCESSOR_H_
#define _SLAM_HECTOR_SLAM_PROCESSOR_H_

#include <common/exception.h>
#include <slam/hector/map/representation/properties.h>
#include <slam/hector/map/representation/base.h>
#include <slam/hector/map/representation/single.h>
#include <slam/hector/map/representation/multi.h>
#include <sensor/lidar2d.h>
#include <type/pose2d.h>
#include <float.h>

namespace sgbot {
namespace slam {
namespace hector {

  class SlamProcessor {
  public:
    SlamProcessor(const MapProperties& properties, bool use_multi_level_maps, float free_factor, float occupied_factor, float distance_threshold, float theta_threshold)
    {
      if(use_multi_level_maps)
      {
        map_representation_ = new RepresentationMultiMap(properties, 3);
      }
      else
      {
        map_representation_ = new RepresentationSingleMap(properties);
      }

      reset();

      map_representation_->setCellFreeFactor(free_factor);
      map_representation_->setCellOccupiedFactor(occupied_factor);

      update_distance_threshold_ = distance_threshold;
      update_theta_threshold_ = theta_threshold;
    }

    virtual ~SlamProcessor()
    {
      delete map_representation_;
    }

    void update(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& pose_hint_world, bool need_matching = true);

    void reset()
    {
      last_scanmatch_pose_.x() = 0.0f;
      last_scanmatch_pose_.y() = 0.0f;
      last_scanmatch_pose_.theta() = 0.0f;

      last_update_pose_.x() = FLT_MAX;
      last_update_pose_.y() = FLT_MAX;
      last_update_pose_.theta() = FLT_MAX;

      map_representation_->reset();
    }

    const sgbot::la::Matrix<float, 3, 3>& getLastScanMatchCovariance() const
    {
      return last_scanmatch_covariance_;
    }

    const sgbot::Pose2D& getLastScanMatchPose() const
    {
      return last_scanmatch_pose_;
    }

    float getMapScaleFactor() const
    {
      return map_representation_->getScalingFactor();
    }

    int getMapLevels() const
    {
      return map_representation_->getLevels();
    }

    OccupancyGridMap& getMap(int level) const
    {
      return map_representation_->getMap(level);
    }

    void lockMap(int level)
    {
      map_representation_->lockMap(level);
    }

    void unlockMap(int level)
    {
      map_representation_->unlockMap(level);
    }

  private:
    MapRepresentationBase* map_representation_;

    sgbot::la::Matrix<float, 3, 3> last_scanmatch_covariance_;
    sgbot::Pose2D last_scanmatch_pose_;

    sgbot::Pose2D last_update_pose_;

    float update_distance_threshold_;
    float update_theta_threshold_;

  };  //class SlamProcessor

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_SLAM_PROCESSOR_H_
