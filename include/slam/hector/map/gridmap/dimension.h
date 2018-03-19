/* Created slam/hector/map/gridmap/dimension.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_GRIDMAP_DIMENSION_H_
#define _SLAM_HECTOR_MAP_GRIDMAP_DIMENSION_H_

#include <common/exception.h>
#include <linear-algebra/vector.h>
#include <type/point2d.h>

namespace sgbot {
namespace slam {
namespace hector {
  
  class GridMapDimension {
  public:
    GridMapDimension()
      : top_offset_(-1.0f), left_offset_(-1.0f), width_(-1), height_(-1), cell_length_(-1.0f)
    {}

    GridMapDimension(float top_offset, float left_offset, int width, int height, float cell_length)
      : top_offset_(top_offset), left_offset_(left_offset), width_(width), height_(height), cell_length_(cell_length)
    {
      x_limit_ = (float)(width - 1);
      y_limit_ = (float)(height - 1);
    }

    virtual ~GridMapDimension()
    {}

    void setTopLeftOffset(const float top_offset, const float left_offset)
    {
      top_offset_ = top_offset;
      left_offset_ = left_offset;
    }

    void getTopLeftOffset(float& top_offset, float& left_offset) const
    {
      top_offset = top_offset_;
      left_offset = left_offset_;
    }

    void setMapDimensions(const int width, const int height)
    {
      width_ = width;
      height_ = height;
      x_limit_ = (float)(width - 2);
      y_limit_ = (float)(height - 2);
    }

    void getMapDimensions(int& width, int& height) const
    {
      width = width_;
      height = height_;
    }

    void setCellLength(const float cell_length)
    {
      cell_length_ = cell_length;
    }

    float getCellLength() const
    {
      return cell_length_;
    }

    void setMapWidth(const int width)
    {
      width_ = width;
    }

    int getMapWidth() const
    {
      return width_;
    }

    void setMapHeight(const int height)
    {
      height_ = height;
    }

    int getMapHeight() const
    {
      return height_;
    }

    bool operator==(const GridMapDimension& other) const
    {
      return (top_offset_ == other.top_offset_) && (left_offset_ == other.left_offset_) && (width_ == other.width_) && (height_ == other.height_) && (cell_length_ == other.cell_length_);
    }

    bool isDimensionEqual(const GridMapDimension& other) const
    {
      return (width_ == other.width_) && (height_ == other.height_);
    }
    
    bool isTransformationEqual(const GridMapDimension& other) const
    {
      return (top_offset_ == other.top_offset_) && (left_offset_ == other.left_offset_) && (cell_length_ == other.cell_length_);
    }

    bool isPointOutOfMap(const sgbot::Point2D& point) const
    {
      return ((point.x < 0.0f) || (point.x > x_limit_) || (point.y < 0.0f) || (point.y > y_limit_));
    }

  protected:
    float top_offset_, left_offset_;
    int width_, height_;
    float x_limit_, y_limit_;
    float cell_length_;
  };  // class GridMapDimension

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_GRIDMAP_DIMENSION_H_
