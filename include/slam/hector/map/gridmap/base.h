/* Created slam/hector/map/gridmap/base.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_GRIDMAP_BASE_H_
#define _SLAM_HECTOR_MAP_GRIDMAP_BASE_H_

#include <common/exception.h>
#include <linear-algebra/vector.h>
#include <slam/hector/map/gridmap/dimension.h>
#include <type/point2d.h>
#include <transform/transform2d.h>

namespace sgbot {
namespace slam {
namespace hector {

  template<typename CellType>
  class GridMapBase {
  public:
    GridMapBase(float resolution, const int width, const int height, const float left_offset, float top_offset)
      : cells_(NULL), updated_times_(0)
    {
      setDimensions(width, height);
      width_ = width;
      height_ = height;
      setMapTransformation(width, height, left_offset, top_offset, resolution);
      clear();
    }

    virtual ~GridMapBase()
    {
      freeMapSpace();
    }

    GridMapBase(const GridMapBase& other)
    {
      allocateMapSpace(other.getWidth(), other.getHeight());
      *this = other;
    }

    GridMapBase& operator=(const GridMapBase& other)
    {
      if(!(dimension_ == other.dimension_))
      {
        setDimensions(other.getWidth(), other.getHeight());
      }
      
      dimension_ = other.dimension_;
      world_to_map_tf_ = other.world_to_map_tf_;
      map_to_world_tf_ = other.map_to_world_tf_;
      map_scaling_factor_ = other.map_scaling_factor_;

      int map_data_size = getWidth() * getHeight() * sizeof(CellType);

      memcpy(this->cells_, other.cells_, map_data_size);

      return *this;
    }

    bool hasGridCell(int x, int y) const
    {
      return (x >= 0) && (y >= 0) && (x < getWidth()) && (y < getHeight());
    }

    void allocateMapSpace(const int width, const int height)
    {
      int count = width * height;

      cells_ = new CellType[count];

      dimension_.setMapDimensions(width, height);
    }

    void freeMapSpace()
    {
      if(cells_)
      {
        delete[] cells_;
        cells_ = 0;

        dimension_.setMapDimensions(-1, -1);
      }
    }

    void getDimensions(int& width, int& height) const
    {
      dimension_.getMapDimensions(width, height);
    }

    void setDimensions(const int width, const int height)
    {
      if(!(width == getWidth() && height == getHeight()))
      {
        freeMapSpace();
        allocateMapSpace(width, height);
        reset();
      }
    }

    int getWidth() const
    {
      return dimension_.getMapWidth();
    }

    int getHeight() const
    {
      return dimension_.getMapHeight();
    }

    bool isPointOutOfMap(const sgbot::Point2D& point) const
    {
      return dimension_.isPointOutOfMap(point);
    }

    virtual void reset()
    {
      clear();
    }

    void clear()
    {
      if(cells_)
      {
        int count = getWidth() * getHeight();

        for(int i = 0; i < count; ++i)
        {
          cells_[i].reset();
        }
      }
    }

    CellType& getCell(int x, int y) const
    {
      return cells_[(y * width_) + x];
    }

    CellType& getCell(int index) const
    {
      return cells_[index];
    }

    const sgbot::tf::Transform2D& getWorldToMapTransform() const
    {
      return world_to_map_tf_;
    }

    const sgbot::tf::Transform2D& getMapToWorldTransform() const
    {
      return map_to_world_tf_;
    }

    // TODO:  to confirm this transform is correct.
    sgbot::Point2D getWorldCoords(const sgbot::Point2D map_coords)
    {
      return world_to_map_tf_.transform(map_coords);
    }

    // TODO:  to confirm this transform is correct.
    sgbot::Point2D getMapCoords(const sgbot::Point2D world_coords)
    {
      return map_to_world_tf_.transform(world_coords);
    }

    // TODO:  to confirm this transform is correct.
    sgbot::Pose2D getWorldPose(const sgbot::Pose2D map_pose)
    {
      return world_to_map_tf_.transform(map_pose);
    }

    // TODO:  to confirm this transform is correct.
    sgbot::Pose2D getMapPose(const sgbot::Pose2D world_pose)
    {
      return map_to_world_tf_.transform(world_pose);
    }

    float getScalingFactor() const
    {
      return map_scaling_factor_;
    }

    float getCellLength() const
    {
      return dimension_.getCellLength();
    }

    void update()
    {
      updated_times_++;
    }

    int getUpdateTimes() const
    {
      return updated_times_;
    }

    void setMapTransformation(const int width, const int height, const float left_offset, const float top_offset, float cell_length)
    {
      dimension_.setCellLength(cell_length);
      dimension_.setTopLeftOffset(top_offset, left_offset);
      dimension_.setMapDimensions(width, height);

      map_scaling_factor_ = 1.0f / cell_length;

      // debug
      std::cout << "set tf:" << top_offset << "," << left_offset << "," << cell_length <<std::endl;
    
      // TODO: set map to world affine transfomation, maybe problem here
      map_to_world_tf_.setValue((map_scaling_factor_ * left_offset), (map_scaling_factor_ * top_offset), 0.0f, map_scaling_factor_);

      // debug
      std::cout << "map to world: " << map_to_world_tf_.getMatrix() << std::endl;

      world_to_map_tf_ = map_to_world_tf_.inverse();

      // debug
      std::cout << "world to map: " << world_to_map_tf_.getMatrix() << std::endl;
    }

    bool getMapExtends(int& start_x, int& start_y, int& end_x, int& end_y)
    {
      int min_val = -1;
      int max_val = 10000;

      int start_x_temp = max_val;
      int start_y_temp = max_val;
      int end_x_temp = min_val;
      int end_y_temp = min_val;

      for(int i = 0; i < getWidth(); ++i)
      {
        for(int j = 0; j < getHeight(); ++j)
        {
          if(getCell(i, j) != 0.0f)
          {
            if(i > end_x_temp)
            {
              end_x_temp = i;
            }
          
            if(i < start_x_temp)
            {
              start_x_temp = i;
            }

            if(j > end_y_temp)
            {
              end_y_temp = j;
            }

            if(j < start_y_temp)
            {
              start_y_temp = j;
            }
          }
        }
      }

      if((start_x_temp != max_val) && (start_y_temp != max_val) && (end_x_temp != min_val) && (end_y_temp = min_val))
      {
        start_x = start_x_temp;
        start_y = start_y_temp;
        end_x = end_x_temp;
        end_y = end_y_temp;

        return true;
      }
      else
      {
        return false;
      }
    }

  protected:
    GridMapDimension dimension_;
    CellType* cells_;
    int width_, height_;
    sgbot::tf::Transform2D world_to_map_tf_;
    sgbot::tf::Transform2D map_to_world_tf_;
    float map_scaling_factor_;
  private:
    int updated_times_;
  };  // class GridMapBase

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_GRIDMAP_BASE_H_
