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

namespace sgbot {
namespace slam {
namespace hector {

  class SlamProcessor {
  public:
    SlamProcessor(const MapProperties& properties, bool use_multi_level_maps)
    {
      if(use_multi_level_maps)
      {
        map_representation_ = new RepresentationMultiMap(properties, 3);
      }
      else
      {
        map_representation_ = new RepresentationSingleMap(properties);
      }
    }

    virtual ~SlamProcessor()
    {
      delete map_representation_;
    }

    void update(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& pose_hint_world, bool need_matching = false);

  private:
    MapRepresentationBase* map_representation_;
  };  //class SlamProcessor

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_SLAM_PROCESSOR_H_
