/* Created slam/hector/mapping.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAPPING_H_
#define _SLAM_HECTOR_MAPPING_H_

#include <string>
#include <common/exception.h>
#include <sensor/lidar2d.h>
#include <type/map2d.h>
#include <slam/hector/config.h>
#include <slam/hector/slam/processor.h>

namespace sgbot {
namespace slam {
namespace hector {

  class HectorMapping {
  public:
    HectorMapping()
    {
      config_.map_properties.resolution = 0.025f;
      config_.map_properties.width = 1024;
      config_.map_properties.height = 1024;
      config_.map_properties.left_offset = 0.5f;
      config_.map_properties.top_offset = 0.5f;
      config_.use_multi_level_maps = true;
      config_.update_free_factor = 0.4f;
      config_.update_occupied_factor = 0.9f;
      config_.min_update_angle = 0.9f;
      config_.min_update_distance = 0.4f;

      processor_ = new SlamProcessor(config_.map_properties, config_.use_multi_level_maps);
    }

    HectorMapping(const HectorMappingConfig& config)
    {
      config_ = config;
      processor_ = new SlamProcessor(config.map_properties, config.use_multi_level_maps);
    }

    ~HectorMapping()
    {
      delete processor_;
    }

    void updateByScan(const sgbot::sensor::Lidar2D& scan);

    bool getMapAndPose(sgbot::Map2D& map, sgbot::Pose2D& pose)
    {

    }

  private:
    SlamProcessor* processor_;
    HectorMappingConfig config_;

  };  // HectorMapping

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAPPING_H_
