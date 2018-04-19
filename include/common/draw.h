/* Created common/draw.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _DRAW_H_
#define _DRAW_H_

#include <exception>
#include <iostream>
#include <string>
#include <type/point2d.h>
#include <type/pose2d.h>

namespace sgbot {

  typedef void (*DrawScanCallback)(const sgbot::sensor::Lidar2D&);
  typedef void (*DrawPoseCallback)(const sgbot::Pose2D&);
  typedef void (*DrawPoseWithCovarianceCallback)(const sgbot::Pose2D&, const sgbot::la::Matrix<float, 3, 3>&);
  typedef void (*DrawPointCallback)(const sgbot::Point2D&);

  typedef void (*UpdateCallback)(void);
  typedef void (*ResetCallback)(void);

  class Draw {
  public:
    Draw()
    {}

    virtual ~Draw()
    {}

    void setDisplayScanCallback(DrawScanCallback draw_scan_cb)
    {
      draw_scan_cb_ = draw_scan_cb;
    }

    void setDrawPoseCallback(DrawPoseCallback draw_pose_cb)
    {
      draw_pose_cb_ = draw_pose_cb;
    }

    void setDrawPoseWithCovarianceCallback(DrawPoseWithCovarianceCallback draw_pose_with_covariance_cb)
    {
      draw_pose_with_covariance_cb_ = draw_pose_with_covariance_cb;
    }

    void setDrawPointCallback(DrawPointCallback draw_point_cb)
    {
      draw_point_cb_ = draw_point_cb;
    }

    void setUpdateCallback(UpdateCallback update_cb)
    {
      update_cb_ = update_cb;
    }

    void setResetCallback(ResetCallback reset_cb)
    {
      reset_cb_ = reset_cb;
    }

    void drawScan(const sgbot::sensor::Lidar2D& scan)
    {
      if(draw_scan_cb_)
      {
        draw_scan_cb_(scan);
      }
    }

    void drawPose(const sgbot::Pose2D& pose)
    {
      if(draw_pose_cb_)
      {
        draw_pose_cb_(pose);
      }
    }

    void drawPoseWithCovariance(const sgbot::Pose2D& pose, const sgbot::la::Matrix<float, 3, 3>& covariance)
    {
      if(draw_pose_with_covariance_cb_)
      {
        draw_pose_with_covariance_cb_(pose, covariance);
      }
    }

    void drawPoint(const sgbot::Point2D& point)
    {
      if(draw_point_cb_)
      {
        draw_point_cb_(point);
      }
    }

    void update()
    {
      if(update_cb_)
      {
        update_cb_();
      }
    }

    void reset()
    {
      if(reset_cb_)
      {
        reset_cb_();
      }
    }

  private:
    DrawScanCallback draw_scan_cb_;
    DrawPoseCallback draw_pose_cb_;
    DrawPoseWithCovarianceCallback draw_pose_with_covariance_cb_;
    DrawPointCallback draw_point_cb_;

    UpdateCallback update_cb_;
    ResetCallback reset_cb_;
  };  // class Debug
  
  Draw* draw;
}  // namespace sgbot

#endif  // _DRAW_H_
