/* Created slam/hector/map/util/manager.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_UTIL_MANAGER_H_
#define _SLAM_HECTOR_MAP_UTIL_MANAGER_H_

#include <common/exception.h>
#include <slam/hector/map/occupancy-gridmap/map.h>
#include <slam/hector/map/occupancy-gridmap/optimizer.h>
#include <slam/hector/slam/scanmatcher.h>
#include <slam/hector/map/util/locker.h>
#include <slam/hector/map/representation/properties.h>
#include <vector>

namespace sgbot {
namespace slam {
namespace hector {

  class MapManager {
  public:

    MapManager(const MapProperties& properties)
    {
      // debug
      std::cout << "properties: " << properties.resolution << ", " <<  properties.width << ", " << properties.height << ", " << properties.left_offset << ", " << properties.top_offset << std::endl;

      properties_ = properties;
      gridmap_ = new OccupancyGridMap(properties.resolution, properties.width, properties.height, properties.left_offset, properties.top_offset);
      optimizer_ = new OccupancyGridMapOptimizer(gridmap_);
    }

    virtual ~MapManager()
    {
      if(optimizer_)
        delete optimizer_;
      if(gridmap_)
        delete gridmap_;
    }

    OccupancyGridMap& getMap()
    {
      return *gridmap_;
    }

    OccupancyGridMapOptimizer& getOptimizer()
    {
      return *optimizer_;
    }

    ScanMatcher& getScanMatcher()
    {
      return scanmatcher_;
    }

    void lockMap()
    {
      locker_.lock();
    }

    void unlockMap()
    {
      locker_.unlock();
    }
  
  private:
    MapProperties properties_;
    OccupancyGridMap* gridmap_;
    OccupancyGridMapOptimizer* optimizer_;
    ScanMatcher scanmatcher_;
    MapLocker locker_;
  };  // MapManager

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_UTIL_MANAGER_H_
