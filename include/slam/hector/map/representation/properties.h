/* Created slam/hector/map/representation/properties.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_REPRESENTATION_PROPERTIES_H_
#define _SLAM_HECTOR_MAP_REPRESENTATION_PROPERTIES_H_

#include <common/exception.h>

namespace sgbot {
namespace slam {
namespace hector {

  class MapProperties {
  public:
    float resolution;
    int width;
    int height;
    float left_offset;
    float top_offset;
  };  // MapProperties

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_REPRESENTATION_PROPERTIES_H_
