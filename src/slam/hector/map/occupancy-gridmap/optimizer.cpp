/* Created slam/hector/map/occupancy-gridmap/optimizer.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#include <slam/hector/map/occupancy-gridmap/optimizer.h>

namespace sgbot {
namespace slam {
namespace hector {

  void OccupancyGridMapOptimizer::getCompleteHessianDerivs(const sgbot::Pose2D& estimate_pose, const sgbot::sensor::Lidar2D& scan, sgbot::la::Matrix<float, 3, 3>& hessian, sgbot::tf::Transform2D& delta_transformation)
  {
    
  }

  sgbot::la::Matrix<float, 3, 3> OccupancyGridMapOptimizer::getPoseCovariance(const sgbot::Pose2D& map_pose, const sgbot::sensor::Lidar2D& scan)
  {

  }

  sgbot::la::Matrix<float, 3, 3> OccupancyGridMapOptimizer::getWorldCoordsCovariance(const sgbot::la::Matrix<float, 3, 3>& map_coords_cov)
  {

  }

  float OccupancyGridMapOptimizer::getStateResidual(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points)
  {

  }

  float OccupancyGridMapOptimizer::getResidualLikelihood(float residual, int scan_points_count)
  {

  }

  float OccupancyGridMapOptimizer::getStateLikelihood(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points)
  {

  }

  float OccupancyGridMapOptimizer::getInterpMapValue(const sgbot::Point2D& coords)
  {

  }

  bool OccupancyGridMapOptimizer::interpMapValueWithDerivatives(const sgbot::Point2D& coords, float& occupancy_value, float& derivative_x, float& derivative_y)
  {
    if(gridmap_->isPointOutOfMap(coords))
    {
      return false;
    }

    int x_floor = static_cast<int>(coords.x());
    int y_floor = static_cast<int>(coords.y());

    float x_factor = coords.x() - static_cast<float>(x_floor);
    float y_factor = coords.y() - static_cast<float>(y_floor);

    int width = gridmap_->getWidth();

    int index = y_floor * width + x_floor;

    // up left point
    if(!cache_.containsCachedData(index, surround_point_intensities[0]))
    {
      surround_point_intensities[0] = getCellProbability(index);
      cache_.cacheData(index, surround_point_intensities[0]);
    }

    // up right point
    ++index;
    if(!cache_.containsCachedData(index, surround_point_intensities[1]))
    {
      surround_point_intensities[1] = getCellProbability(index);
      cache_.cacheData(index, surround_point_intensities[1]);
    }

    // buttom left point
    index += (width - 1);
    if(!cache_.containsCachedData(index, surround_point_intensities[2]))
    {
      surround_point_intensities[2] = getCellProbability(index);
      cache_.cacheData(index, surround_point_intensities[2]);
    }

    // buttom right point
    ++index;
    if(!cache_.containsCachedData(index, surround_point_intensities[3]))
    {
      surround_point_intensities[3] = getCellProbability(index);
      cache_.cacheData(index, surround_point_intensities[3]);
    }

    float dx1 = surround_point_intensities[0] - surround_point_intensities[1];
    float dx2 = surround_point_intensities[2] - surround_point_intensities[3];

    float dy1 = surround_point_intensities[0] - surround_point_intensities[2];
    float dy2 = surround_point_intensities[1] - surround_point_intensities[3];

    occupancy_value = ((surround_point_intensities[0] * (1.0f - x_factor) + surround_point_intensities[1] * x_factor) * (1.0f - y_factor)) + ((surround_point_intensities[2] * (1.0f - x_factor) + surround_point_intensities[3] * x_factor) * y_factor);
    derivative_x = -((dx1 * (1.0f - x_factor)) + (dx2 * x_factor));
    derivative_y = -((dy1 * (1.0f - y_factor)) + (dy2 * y_factor));

    return true;
  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

