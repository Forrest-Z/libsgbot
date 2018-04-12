/* Created slam/hector/map/gridmap/base.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#include <slam/hector/map/gridmap/base.h>

namespace sgbot {
namespace slam {
namespace hector {

  template <typename CellType>
  void GridMapBase<CellType>::setMapTransformation(const int width, const int height, const float left_offset, const float top_offset, float cell_length)
  {
    dimension_.setCellLength(cell_length);
    dimension_.setTopLeftOffset(top_offset, left_offset);
    dimension_.setMapDimensions(width, height);

    map_scaling_factor_ = 1.0f / cell_length;
    
    // TODO: set map to world affine transfomation, maybe problem here
    map_to_world_tf_.setValue((width * left_offset), (height * top_offset), 0.0f, map_scaling_factor_);
    world_to_map_tf_ = map_to_world_tf_.inverse();
  }

  template <typename CellType>
  bool GridMapBase<CellType>::getMapExtends(int& start_x, int& start_y, int& end_x, int& end_y)
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

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

