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
    sgbot::tf::Transform2D state_tf = getStateTransform(estimate_pose);

    // debug
    std::cout << "state tf: " << state_tf.getMatrix() << std::endl;

    float sin_val = sgbot::math::sin(estimate_pose.theta());
    float cos_val = sgbot::math::cos(estimate_pose.theta());

    float tf_x = 0.0f;
    float tf_y = 0.0f;
    float tf_theta = 0.0f;

    // debug
    //std::cout << scan;

    hessian.zero();

    // TODO: set below for{} segment in openmp frameworks
    for(int i = 0; i < scan.getCount(); ++i)
    {
      const sgbot::Point2D& p = scan.getPoint(i);
      sgbot::Point2D point_in_pose = state_tf.transform(p);

      float occ, dx, dy;

      if(!interpMapValueWithDerivatives(state_tf.transform(p), occ, dx, dy))
      {
        // TODO: should put error process segment here

        // debug
        std::cout << "interpMapValueWithDerivatives fail!" << std::endl;

        continue;
      }
      
      float inv_occ = 1.0f - occ;

      // debug
      //std::cout << "interp: " << occ << "," << dx << "," << dy << std::endl;

      float rotate_deriv = (-sin_val * p.x() - cos_val * p.y()) * dx + (cos_val * p.x() - sin_val * p.y()) * dy;

      tf_x += (dx * inv_occ);
      tf_y += (dy * inv_occ);
      tf_theta += (rotate_deriv * inv_occ);

      hessian(0, 0) += sgbot::math::sqr(dx);
      hessian(1, 1) += sgbot::math::sqr(dy);
      hessian(2, 2) += sgbot::math::sqr(rotate_deriv);

      hessian(0, 1) += dx * dy;
      hessian(0, 2) += dx * rotate_deriv;
      hessian(1, 2) += dy * rotate_deriv;
    }
    hessian(1, 0) = hessian(0, 1);
    hessian(2, 0) = hessian(0, 2);
    hessian(2, 1) = hessian(1, 2);

    delta_transformation.setValue(tf_x, tf_y, tf_theta, 1.0f);
  }

  sgbot::la::Matrix<float, 3, 3> OccupancyGridMapOptimizer::getPoseCovariance(const sgbot::Pose2D& map_pose, const sgbot::sensor::Lidar2D& scan)
  {
    float delta_tf_x = 1.5f;
    float delta_tf_y = 1.5f;
    float delta_tf_theta = 0.05f;

    float x = map_pose.x();
    float y = map_pose.y();
    float theta = map_pose.theta();

    // TODO: to check this matrix is correct
    sgbot::la::Matrix<float, 3, 7> sigma;
    // column 1
    sigma(0, 0) = x + delta_tf_x;
    sigma(1, 0) = y;
    sigma(2, 0) = theta;
    // column 2
    sigma(0, 1) = x - delta_tf_x;
    sigma(1, 1) = y;
    sigma(2, 1) = theta;
    // column 3
    sigma(0, 2) = x;
    sigma(1, 2) = y + delta_tf_y;
    sigma(2, 2) = theta;
    // column 4
    sigma(0, 3) = x;
    sigma(1, 3) = y - delta_tf_y;
    sigma(2, 3) = theta;
    // column 5
    sigma(0, 4) = x;
    sigma(1, 4) = y;
    sigma(2, 4) = theta + delta_tf_theta;
    // column 6
    sigma(0, 5) = x;
    sigma(1, 5) = y;
    sigma(2, 5) = theta - delta_tf_theta;
    // column 7
    sigma(0, 6) = x;
    sigma(1, 6) = y;
    sigma(2, 6) = theta;

    sgbot::la::Matrix<float, 7, 1> likelihoods;
    likelihoods(0, 0) = getStateLikelihood(sgbot::Pose2D((x + delta_tf_x), y, theta), scan);
    likelihoods(1, 0) = getStateLikelihood(sgbot::Pose2D((x - delta_tf_x), y, theta), scan);
    likelihoods(2, 0) = getStateLikelihood(sgbot::Pose2D(x, (y + delta_tf_y), theta), scan);
    likelihoods(3, 0) = getStateLikelihood(sgbot::Pose2D(x, (y - delta_tf_y), theta), scan);
    likelihoods(4, 0) = getStateLikelihood(sgbot::Pose2D(x, y, (theta + delta_tf_theta)), scan);
    likelihoods(5, 0) = getStateLikelihood(sgbot::Pose2D(x, y, (theta - delta_tf_theta)), scan);
    likelihoods(6, 0) = getStateLikelihood(sgbot::Pose2D(x, y, theta), scan);

    // TODO: print this variant to debug
    float inv_lh_norm = 1 / likelihoods.sum();

    // debug
    std::cout << "inv_lh_norm: " << inv_lh_norm << std::endl;

    sgbot::la::Matrix<float, 3, 1> mean;
    for(int i = 0; i < 7; ++i)
    {
      sgbot::la::Matrix<float, 3, 1> sigma_column;
      sigma_column(0, 0) = sigma(0, i);
      sigma_column(1, 0) = sigma(1, i);
      sigma_column(2, 0) = sigma(2, i);
      mean += sigma_column * likelihoods(i, 0);
    }

    mean *= inv_lh_norm;

    sgbot::la::Matrix<float, 3, 3> cov_matrix_map;

    for(int i = 0; i < 7; ++i)
    {
      sgbot::la::Matrix<float, 3, 1> sigma_min_mean;
      sigma_min_mean(0, 0) = sigma(0, i) - mean(0, 0);
      sigma_min_mean(1, 0) = sigma(1, i) - mean(1, 0);
      sigma_min_mean(2, 0) = sigma(2, i) - mean(2, 0);
      
      sgbot::la::Matrix<float, 3, 3> temp = (sigma_min_mean * sigma_min_mean.transpose());
      cov_matrix_map += temp * (likelihoods(i, 0) * inv_lh_norm);
    }

    return cov_matrix_map;
  }

  sgbot::la::Matrix<float, 3, 3> OccupancyGridMapOptimizer::getWorldCoordsCovariance(const sgbot::la::Matrix<float, 3, 3>& map_coords_cov)
  {
    sgbot::la::Matrix<float, 3, 3> cov_matrix_world;

    float scale = gridmap_->getCellLength();
    float scale_sqr = sgbot::math::sqr(scale);

    cov_matrix_world(0, 0) = map_coords_cov(0, 0) * scale_sqr;
    cov_matrix_world(1, 1) = map_coords_cov(1, 1) * scale_sqr;

    cov_matrix_world(1, 0) = map_coords_cov(1, 0) * scale_sqr;
    cov_matrix_world(0, 1) = cov_matrix_world(1, 0);

    cov_matrix_world(2, 0) = map_coords_cov(2, 0) * scale;
    cov_matrix_world(0, 2) = cov_matrix_world(2, 0);

    cov_matrix_world(2, 1) = map_coords_cov(2, 1) * scale;
    cov_matrix_world(1, 2) = cov_matrix_world(2, 1);
    
    cov_matrix_world(2, 2) = map_coords_cov(2, 2);    

    return cov_matrix_world;
  }

  float OccupancyGridMapOptimizer::getStateResidual(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points)
  {
    int step = 1;
    float residual = 0.0f;

    sgbot::tf::Transform2D state_tf = getStateTransform(state);

    for(int i = 0; i < points.getCount(); i += step)
    {
      float inv_occ = 1.0f - getInterpMapValue(state_tf.transform(points.getPoint(i)));
      residual += inv_occ;
    }

    return residual;
  }

  float OccupancyGridMapOptimizer::getResidualLikelihood(float residual, int scan_points_count)
  {
    float a = static_cast<int>(scan_points_count);
    float count = static_cast<float>(a);
    return (1 - residual / count);
  }

  float OccupancyGridMapOptimizer::getStateLikelihood(const sgbot::Pose2D& state, const sgbot::sensor::Lidar2D& points)
  {
    float residual = getStateResidual(state, points);

    return getResidualLikelihood(residual, points.getCount());
  }

  float OccupancyGridMapOptimizer::getInterpMapValue(const sgbot::Point2D& coords)
  {
    if(gridmap_->isPointOutOfMap(coords))
    {
      return 0.0f;
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

    return ((surround_point_intensities[0] * (1.0f - x_factor) + surround_point_intensities[1] * x_factor) * (1.0f - y_factor)) + ((surround_point_intensities[2] * (1.0f - x_factor) + surround_point_intensities[3] * x_factor) * y_factor);
  }

  bool OccupancyGridMapOptimizer::interpMapValueWithDerivatives(const sgbot::Point2D& coords, float& occupancy_value, float& derivative_x, float& derivative_y)
  {
    if(gridmap_->isPointOutOfMap(coords))
    {
      // debug
      std::cout << "coord is out of bound!" << std::endl;
      return false;
    }

    int x_floor = static_cast<int>(coords.x());
    int y_floor = static_cast<int>(coords.y());

    float x_factor = coords.x() - static_cast<float>(x_floor);
    float y_factor = coords.y() - static_cast<float>(y_floor);

    // debug
    //std::cout << "ind_min: " << x_floor << "," << y_floor << std::endl;
    //std::cout << "factor: " << x_factor << "," << y_factor << std::endl;

    int width = gridmap_->getWidth();

    // debug
    //std::cout << "width: " << width << std::endl;

    int index = y_floor * width + x_floor;

    // debug
    //std::cout << "index: " << index << std::endl;

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

    // debug
    //std::cout << "intensities: " << surround_point_intensities[0] << "," << surround_point_intensities[1] << "," << surround_point_intensities[2] << "," << surround_point_intensities[3] << std::endl;

    float dx1 = surround_point_intensities[0] - surround_point_intensities[1];
    float dx2 = surround_point_intensities[2] - surround_point_intensities[3];

    float dy1 = surround_point_intensities[0] - surround_point_intensities[2];
    float dy2 = surround_point_intensities[1] - surround_point_intensities[3];

    occupancy_value = ((surround_point_intensities[0] * (1.0f - x_factor) + surround_point_intensities[1] * x_factor) * (1.0f - y_factor)) + ((surround_point_intensities[2] * (1.0f - x_factor) + surround_point_intensities[3] * x_factor) * y_factor);
    // TODO: to check below code, because its different from pape to implements
    // origin code in ros-hector
    //derivative_x = -((dx1 * (1.0f - x_factor)) + (dx2 * x_factor));
    //derivative_y = -((dy1 * (1.0f - y_factor)) + (dy2 * y_factor));
    // implement from pape
    derivative_x = -((dx1 * (1.0f - y_factor)) + (dx2 * y_factor));
    derivative_y = -((dy1 * (1.0f - x_factor)) + (dy2 * x_factor));

    return true;
  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

