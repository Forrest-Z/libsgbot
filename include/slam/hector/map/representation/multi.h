/* Created slam/hector/map/representation/multi.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_REPRESENTATION_MULTI_H_
#define _SLAM_HECTOR_MAP_REPRESENTATION_MULTI_H_

#include <common/exception.h>
#include <slam/hector/map/representation/base.h>

namespace sgbot {
namespace slam {
namespace hector {

  class RepresentationMultiMap : public MapRepresentationBase {
  public:

    RepresentationMultiMap(const MapProperties& properties, int levels)
    {
      int width = properties.width;
      int height = properties.height;
      float left_offset = properties.resolution * (float)properties.width * properties.left_offset;
      float top_offset = properties.resolution * (float)properties.height * properties.top_offset;
      float map_resolution = properties.resolution;

      levels_ = levels;

      for(int i = 0; i < levels; i++)
      {
        MapProperties single_map;

        single_map.resolution = map_resolution;
        single_map.width = width;
        single_map.height = height;
        single_map.left_offset = left_offset;
        single_map.top_offset = top_offset;

        MapManager* map = new MapManager(properties);
        maps_.push_back(map);

        map_resolution *= 2;
        width /= 2;
        height /= 2;
      }
    }

    virtual ~RepresentationMultiMap() {}

    virtual void reset()
    {
    }

    virtual float getScalingFactor() const
    {

    }

    virtual int getLevels() const
    {

    }

    virtual const OccupancyGridMap& getMap(int level) const
    {

    }
    
    virtual void onMapUpdated()
    {

    }

    virtual sgbot::Pose2D scanMatch(const sgbot::Pose2D& estimate_world_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& covariance)
    {

    }

    virtual void updateByScan(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& world_pose)
    {

    }

    virtual void setCellFreeFactor(float factor)
    {

    }

    virtual void setCellOccupiedFactor(float factor)
    {

    }
  
  private:
    int levels_;

  };  // RepresentationMultiMap

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_REPRESENTATION_MULTI_H_
