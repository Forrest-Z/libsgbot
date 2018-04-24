/* Created slam/hector/map/representation/base.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_REPRESENTATION_BASE_H_
#define _SLAM_HECTOR_MAP_REPRESENTATION_BASE_H_

#include <common/exception.h>
#include <slam/hector/map/util/manager.h>
#include <slam/hector/map/representation/properties.h>
#include <vector>

namespace sgbot {
namespace slam {
namespace hector {

  class MapRepresentationBase {
  public:
    MapRepresentationBase() {}

    virtual ~MapRepresentationBase()
    {
      for(int i = 0; i < maps_.size(); ++i)
      {
        delete maps_[i];
      }
    }

    virtual void reset() = 0;

    virtual float getScalingFactor() const = 0;

    virtual int getLevels() const = 0;

    virtual OccupancyGridMap& getMap(int level) = 0;

    virtual OccupancyGridMapOptimizer& getOptimizer(int level) = 0;
    
    virtual void onMapUpdated() = 0;

    virtual sgbot::Pose2D scanMatch(const sgbot::Pose2D& estimate_world_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& covariance) = 0;

    virtual void updateByScan(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& world_pose) = 0;

    virtual void setCellFreeFactor(float factor) = 0;

    virtual void setCellOccupiedFactor(float factor) = 0;

    virtual void lockMap(int level) = 0;

    virtual void unlockMap(int level) = 0;

  protected:
    MapProperties properties_;
    std::vector<MapManager*> maps_;
  };  // MapRepresentationBase

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_REPRESENTATION_BASE_H_
