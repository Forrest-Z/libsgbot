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
#include <sensor/gyro.h>
#include <type/map2d.h>
#include <slam/hector/slam/processor.h>
#include <slam/hector/config.h>

namespace sgbot {
namespace slam {
namespace hector {

  class HectorMapping {
  public:
    HectorMapping()
    {
      config_.map_properties.resolution = 0.1f;
      config_.map_properties.width = 1024;
      config_.map_properties.height = 1024;
      config_.map_properties.left_offset = 0.5f;
      config_.map_properties.top_offset = 0.5f;
      config_.use_multi_level_maps = true;
      config_.update_free_factor = 0.4f;
      config_.update_occupied_factor = 0.9f;
      config_.min_update_theta = 0.9f;
      config_.min_update_distance = 0.4f;

      processor_ = new SlamProcessor(config_.map_properties, config_.use_multi_level_maps, config_.update_free_factor, config_.update_occupied_factor, config_.min_update_distance, config_.min_update_theta);
      
      maps_last_update_times_.resize(processor_->getMapLevels());
    }

    HectorMapping(const HectorMappingConfig& config)
    {
      config_ = config;
      processor_ = new SlamProcessor(config.map_properties, config.use_multi_level_maps, config.update_free_factor, config.update_occupied_factor, config.min_update_distance, config.min_update_theta);

      maps_last_update_times_.resize(processor_->getMapLevels());
    }

    ~HectorMapping()
    {
      delete processor_;
    }

    void updateByScan(const sgbot::sensor::Lidar2D& scan);

    void updateByScanWithGyro(const sgbot::sensor::Lidar2D& scan, const sgbot::sensor::Gyro& gyro);

    sgbot::Map2D getMap(const int level)
    {
      const OccupancyGridMap& gridmap = processor_->getMap(level);

      sgbot::Map2D map(gridmap.getWidth(), gridmap.getHeight(), gridmap.getCellLength());

      processor_->lockMap(level);

      for(int i = 0; i < gridmap.getWidth(); i++)
      {
        for(int j = 0; j < gridmap.getHeight(); j++)
        {
          if(gridmap.isCellOccupied(i, j))
          {
            map.updateAsEdge(i, j);
          }
          else if(gridmap.isCellFree(i, j))
          {
            map.updateAsKnown(i, j);
          }
        }
      }

      processor_->unlockMap(level);

      maps_last_update_times_[level] = gridmap.getUpdateTimes();

      return map;
    }

    const HectorMappingConfig& getConfig() const
    {
      return config_;
    }

    const sgbot::Pose2D& getPose() const
    {
      return processor_->getLastScanMatchPose();
    }

    const sgbot::la::Matrix<float, 3, 3>& getPoseCovariance() const
    {
      return processor_->getLastScanMatchCovariance();
    }

    bool hasUpdatedMap(int level) const
    {
      const OccupancyGridMap& gridmap = processor_->getMap(level);

      return maps_last_update_times_[level] != gridmap.getUpdateTimes();
    }

  private:
    SlamProcessor* processor_;
    HectorMappingConfig config_;
    std::vector<int> maps_last_update_times_;

  };  // HectorMapping

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAPPING_H_
