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
#include <omp.h>

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

    void updateByScan(const sgbot::sensor::Lidar2D& scan, const sgbot::Pose2D& world_pose)
    {
      current_mark_free_index_ = current_updated_index_ + 1;
      current_mark_occupancy_index_ = current_updated_index_ + 2;

      sgbot::Pose2D map_pose = this->getMapPose(world_pose);

      // debug
      //std::cout << "world pose: " << world_pose << std::endl;
      //std::cout << "map pose: " << map_pose << std::endl;
    
      // TODO: check the following code is correct
      sgbot::tf::Transform2D pose_tf(map_pose.x(), map_pose.y(), map_pose.theta(), 1.0f);

      //std::cout << "pose tf:" << pose_tf.getMatrix() << std::endl;

      sgbot::Point2D scan_origin_in_map = pose_tf.transform(scan.getOrigin());

      // debug
      //std::cout << "origin: " << scan_origin_in_map.x() << ", " << scan_origin_in_map.y() << std::endl;

      int scan_origin_x = scan_origin_in_map.x() + 0.5f;
      int scan_origin_y = scan_origin_in_map.y() + 0.5f;

      // debug
      //std::cout << "scan end point in map" << std::endl;

      for(int i = 0; i < scan.getCount(); ++i)
      {
        sgbot::Point2D scan_endpoint_in_map = pose_tf.transform(scan.getPoint(i));

        scan_endpoint_in_map.x() = scan_endpoint_in_map.x() + 0.5f;
        scan_endpoint_in_map.y() = scan_endpoint_in_map.y() + 0.5f;

        // debug
        //std::cout << scan_endpoint_in_map << std::endl;
        //std::cout << "laser:" << scan.getPoint(i).x() << "," << scan.getPoint(i).y() << ",map:" << scan_endpoint_in_map.x() << "," << scan_endpoint_in_map.y() << std::endl;

        int scan_endpoint_x = static_cast<int>(scan_endpoint_in_map.x());
        int scan_endpoint_y = static_cast<int>(scan_endpoint_in_map.y());

        if(!((scan_origin_x == scan_endpoint_x) && (scan_origin_y == scan_endpoint_y)))
        {
          updateLine(scan_origin_x, scan_origin_y, scan_endpoint_x, scan_endpoint_y);
          // debug
          //std::cout << "b:" << scan_origin_x << "," << scan_origin_y << ",e:" << scan_endpoint_x << "," << scan_endpoint_y << std::endl;
        }
      }

      this->update();

      current_updated_index_ += 3;
    }

  private:

    inline void updateLine(const int x0, const int y0, const int x1, const int y1, unsigned int max_length = UINT_MAX)
    {
      if((x0 < 0) || (x0 >= this->getWidth()) || (y0 < 0) || (y0 >= this->getHeight()))
      {
        return;
      }

      if((x1 < 0) || (x1 >= this->getWidth()) || (y1 < 0) || (y1 >= this->getHeight()))
      {
        return;
      }

      int dx = x1 - x0;
      int dy = y1 - y0;

      unsigned int abs_dx = sgbot::math::abs(dx);
      unsigned int abs_dy = sgbot::math::abs(dy);

      int offset_dx = sgbot::math::sign(dx);
      int offset_dy = sgbot::math::sign(dy) * this->getWidth();

      unsigned int start_offset = y0 * this->getWidth() + x0;

      int error;
      unsigned int abs_a, abs_b;
      int offset_a, offset_b;
      unsigned int offset = start_offset;

      // if x is dominant
      if(abs_dx >= abs_dy)
      {
        // equals to [error = abs_dx / 2]
        error = abs_dx * 0.5f;

        abs_a = abs_dx;
        abs_b = abs_dy;
        offset_a = offset_dx;
        offset_b = offset_dy;
      }
      else
      {
        // equals to [error = abs_dy / 2]
        error = abs_dy * 0.5f;

        abs_a = abs_dy;
        abs_b = abs_dx;
        offset_a = offset_dy;
        offset_b = offset_dx;
      }

      // debug
      //std::cout << "da: " << abs_a << ",db: " << abs_b << ",error: " << error << ",offset_a: " << offset_a << ",offset_b: " << offset_b << ",offset:" << offset << std::endl;

      // bresenham draw line algorithm
      updateCellAsFree(offset);

      for(int i = 0; i < (abs_a - 1); ++i)
      {
        offset += offset_a;
        error += abs_b;
        if((unsigned int)error >= abs_a)
        {
          offset += offset_b;
          error -= abs_a;
        }
        updateCellAsFree(offset);
      }
    
    
      unsigned int end_offset = y1 * this->getWidth() + x1;
      updateCellAsOccupied(end_offset);
    }

    inline void updateCellAsFree(int index)
    {
      CellType& cell(this->getCell(index));

      if(cell.index < current_mark_free_index_)
      {
        cell_factor_.setFree(cell);
        cell.index = current_mark_free_index_;
      }

      // debug
      //std::cout << "index: " << cell.index << ",value:" << cell.value << ",current_mark_free_index_: " << current_mark_free_index_ << std::endl;
    }

    inline void updateCellAsOccupied(int index)
    {
      CellType& cell(this->getCell(index));

      if(cell.index < current_mark_occupancy_index_)
      {
        if(cell.index == current_mark_free_index_)
        {
          cell_factor_.unsetFree(cell);
        }

        cell_factor_.setOccupied(cell);

        cell.index = current_mark_occupancy_index_;
      }
      
      // debug
      //std::cout << "index: " << cell.index << ",value:" << cell.value << ",current_mark_occupancy_index_: " << current_mark_occupancy_index_ << ",current_mark_free_index_: " << current_mark_free_index_ << std::endl;
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
