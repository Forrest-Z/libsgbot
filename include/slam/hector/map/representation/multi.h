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
#include <std-math/math.h>

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

      multi_level_scans_ = new sgbot::sensor::Lidar2D[levels - 1];
    }

    virtual ~RepresentationMultiMap()
    {
      delete[] multi_level_scans_;
    }

    virtual void reset()
    {
      for(int i = 0; i < maps_.size(); ++i)
      {
        maps_[i]->getMap().reset();
        maps_[i]->getOptimizer().resetCache();
      }
    }

    virtual float getScalingFactor() const
    {
      return maps_[0]->getMap().getScalingFactor();
    }

    virtual int getLevels() const
    {
      return levels_;
    }

    virtual const OccupancyGridMap& getMap(int level) const
    {
      if(level < levels_)
        return maps_[level]->getMap();
      else
        return maps_[0]->getMap();
    }
    
    virtual void onMapUpdated()
    {
      for(int i = 0; i < maps_.size(); ++i)
      {
        maps_[i]->getOptimizer().resetCache();
      }
    }

    virtual sgbot::Pose2D scanMatch(const sgbot::Pose2D& estimate_world_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& covariance)
    {
      sgbot::Pose2D pose = estimate_world_pose;
      
      for(int i = (levels_ - 1); i >= 0; --i)
      {
        if(i == 0)
        {
          pose = maps_[i]->getScanMatcher().scanMatch(pose, getMap(i), scan, covariance, 5);
        }
        else
        {
          float adjust_factor = 1.0f / sgbot::math::pow(2.0f, (float)i);

          sgbot::sensor::Lidar2D scan_temp;

          sgbot::Point2D origin = scan.getOrigin();
          origin.x *= adjust_factor;
          origin.y *= adjust_factor;
          scan_temp.setOrigin(origin);

          scan_temp.clear();
          for(int j = 0; j < scan.getCount(); ++j)
          {
            sgbot::Point2D point = scan.getPoint(j);
            scan_temp.addPoint(point.x * adjust_factor, point.y * adjust_factor);
          }

          multi_level_scans_[i - 1] = scan_temp;

          pose = maps_[i]->getScanMatcher().scanMatch(pose, getMap(i), scan_temp, covariance, 3);
        }
      }
      return pose;
    }

    virtual void updateByScan(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& world_pose)
    {
      for(int i = 0; i < maps_.size(); ++i)
      {
        maps_[i]->lockMap();

        if(i == 0)
        {
          maps_[i]->getMap().updateByScan(scan, world_pose);
        }
        else
        {
          maps_[i]->getMap().updateByScan(multi_level_scans_[i - 1], world_pose);
        }

        maps_[i]->unlockMap();
      }
    }

    virtual void setCellFreeFactor(float factor)
    {
      for(int i = 0; i < maps_.size(); ++i)
      {
        maps_[i]->getMap().setCellFreeFactor(factor);
      }
    }

    virtual void setCellOccupiedFactor(float factor)
    {
      for(int i = 0; i < maps_.size(); ++i)
      {
        maps_[i]->getMap().setCellOccupiedFactor(factor);
      }
    }
  
  private:
    int levels_;
    sgbot::sensor::Lidar2D* multi_level_scans_;

  };  // RepresentationMultiMap

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_REPRESENTATION_MULTI_H_
