/* Created slam/hector/map/occupancy-gridmap/base.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_BASE_H_
#define _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_BASE_H_

#include <climits>

#include <common/exception.h>
#include <slam/hector/map/gridmap/base.h>
#include <sensor/lidar2d.h>
#include <slam/hector/map/cell/logodds.h>

namespace sgbot {
namespace slam {
namespace hector {

  template <typename CellType, typename CellFactor>
  class OccupancyGridMapBase : public GridMapBase<CellType>
  {
  public:
    OccupancyGridMapBase(float resolution, const int width, const int height, const float left_offset, float top_offset)
      : GridMapBase<CellType>(resolution, width, height, left_offset, top_offset),
        current_updated_index_(0), current_mark_occupancy_index_(-1), current_mark_free_index_(-1)
    {}

    virtual ~OccupancyGridMapBase() {}

    void setCellOccupied(int index)
    {
      cell_factor_.setOccupied(this->getCell(index));
    }

    void setCellFree(int index)
    {
      cell_factor_.setFree(this->getCell(index));
    }

    void unsetCellFree(int index)
    {
      cell_factor_.unsetCellFree(this->getCell(index));
    }

    float getCellProbability(int index)
    {
      return cell_factor_.getProbability(this->getCell(index));
    }

    bool isCellOccupied(int x, int y) const
    {
      return this->getCell(x, y).isOccupied();
    }

    bool isCellOccupied(int index) const
    {
      return this->getCell(index).isOccupied();
    }

    bool isCellFree(int x, int y) const
    {
      return this->getCell(x, y).isFree();
    }

    bool isCellFree(int index) const
    {
      return this->getCell(index).isFree();
    }

    float getObstacleThreshold() const
    {
      CellType cell;
      cell.reset();
      return cell_factor_.getProbability(cell);
    }

    void setCellFreeFactor(float factor)
    {
      cell_factor_.setFreeFactor(factor);
    }

    void setCellOccupiedFactor(float factor)
    {
      cell_factor_.setOccupiedFactor(factor);
    }

    void updateByScan(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& world_pose);

  private:

    inline void updateLine(const int x0, const int y0, const int x1, const int y1, unsigned int max_length = UINT_MAX);

    inline void updateCellAsFree(int index)
    {
      CellType& cell(this->getCell(index));

      if(cell.getIndex() < current_mark_occupancy_index_)
      {
        cell_factor_.setFree(cell);
        cell.setIndex(current_mark_free_index_);
      }
    }

    inline void updateCellAsOccupied(int index)
    {
      CellType& cell(this->getCell(index));
      
      if(cell.getIndex() == current_mark_free_index_)
      {
        cell_factor_.unsetFree(cell);
      }

      cell_factor_.setOccupied(cell);

      cell.setIndex(current_mark_occupancy_index_);
    }

  protected:
    CellFactor cell_factor_;
    int current_updated_index_;
    int current_mark_occupancy_index_;
    int current_mark_free_index_;
  };  // class OccupancyGridMapBase

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_OCCUPANCY_GRIDMAP_BASE_H_
