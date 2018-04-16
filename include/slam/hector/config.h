/* Created slam/hector/config.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_CONFIG_H_
#define _SLAM_HECTOR_CONFIG_H_

#include <string>
#include <common/exception.h>
#include <slam/hector/map/representation/properties.h>

namespace sgbot {
namespace slam {
namespace hector {

  class HectorMappingConfig {
  public:
    HectorMappingConfig() {}
    virtual ~HectorMappingConfig() {}

    void loadConfig(const std::string& ini_file);

  public:
    MapProperties map_properties;
    bool use_multi_level_maps;
    float update_free_factor;
    float update_occupied_factor;
    float min_update_theta;
    float min_update_distance;

  };  // HectorMappingConfig

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_CONFIG_H_
