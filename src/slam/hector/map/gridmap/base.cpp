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
  void GridMapBase<CellType>::setMapTransformation(const float left_offset, const float top_offset, float cell_length)
  {
    dimension_.setCellLength(cell_length);
    dimension_.setTopLeftOffset(top_offset, left_offset);

    world_to_map_scaling_factor_ = 1.0f / cell_length;
  }

  template <typename CellType>
  bool GridMapBase<CellType>::getMapExtends(int& start_x, int& start_y, int& end_x, int& end_y)
  {

  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

