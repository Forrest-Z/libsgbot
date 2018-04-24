/* Created slam/hector/map/representation/single.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_REPRESENTATION_SINGLE_H_
#define _SLAM_HECTOR_MAP_REPRESENTATION_SINGLE_H_

#include <common/exception.h>
#include <slam/hector/map/representation/base.h>

namespace sgbot {
namespace slam {
namespace hector {

  class RepresentationSingleMap : public MapRepresentationBase {
  public:

    RepresentationSingleMap(const MapProperties& properties)
    {
      MapManager* map = new MapManager(properties);
      maps_.push_back(map);
    }

    virtual ~RepresentationSingleMap() {}

    virtual void reset()
    {
      maps_[0]->getMap().reset();
      maps_[0]->getOptimizer().resetCache();
    }

    virtual float getScalingFactor() const 
    {
      return maps_[0]->getMap().getScalingFactor();
    }

    virtual int getLevels() const
    {
      return 1;
    }

    virtual OccupancyGridMap& getMap(int level)
    {
      return maps_[0]->getMap();
    }

    virtual OccupancyGridMapOptimizer& getOptimizer(int level)
    {
      return maps_[0]->getOptimizer();
    }
    
    virtual void onMapUpdated()
    {
      maps_[0]->getOptimizer().resetCache();
    }

    virtual sgbot::Pose2D scanMatch(const sgbot::Pose2D& estimate_world_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& covariance)
    {
      maps_[0]->getScanMatcher().scanMatch(getOptimizer(0), estimate_world_pose, scan, covariance, 20);
    }

    virtual void updateByScan(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& world_pose)
    {
      maps_[0]->lockMap();
      maps_[0]->getMap().updateByScan(scan, world_pose);
      maps_[0]->unlockMap();
    }

    virtual void setCellFreeFactor(float factor)
    {
      maps_[0]->getMap().setCellFreeFactor(factor);
    }

    virtual void setCellOccupiedFactor(float factor)
    {
      maps_[0]->getMap().setCellOccupiedFactor(factor);
    }

    virtual void lockMap(int level)
    {
      return maps_[0]->lockMap();
    }

    virtual void unlockMap(int level)
    {
      return maps_[0]->unlockMap();
    }

  };  // RepresentationSingleMap

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_REPRESENTATION_SINGLE_H_
