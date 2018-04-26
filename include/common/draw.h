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
#include <sensor/lidar2d.h>
#include <linear-algebra/matrix.h>

namespace sgbot {

  class DrawCallbacks {
  public:
    DrawCallbacks() {}

    virtual ~DrawCallbacks() {}

    virtual void drawScan(const sgbot::sensor::Lidar2D& scan) = 0;

    virtual void drawPose(const sgbot::Pose2D& pose) = 0;

    virtual void drawPoseWithCovariance(const sgbot::Pose2D& pose,const sgbot::la::Matrix<float,3,3>& covariance) = 0;

    virtual void drawPoint(const sgbot::Point2D& point) = 0;

    virtual void update() = 0;

    virtual void reset() = 0;
  };  // calss DrawCallbacks

  class Draw {
  public:
    Draw()
      : inst_(NULL)
    {}

    virtual ~Draw()
    {}

    void setCallbacks(DrawCallbacks* inst)
    {
      assert(inst);
      inst_ = inst;
    }

    void drawScan(const sgbot::sensor::Lidar2D& scan)
    {
      if(inst_)
      {
        inst_->drawScan(scan);
      }
    }

    void drawPose(const sgbot::Pose2D& pose)
    {
      if(inst_)
      {
        inst_->drawPose(pose);
      }
    }

    void drawPoseWithCovariance(const sgbot::Pose2D& pose, const sgbot::la::Matrix<float, 3, 3>& covariance)
    {
      if(inst_)
      {
        inst_->drawPoseWithCovariance(pose, covariance);
      }
    }

    void drawPoint(const sgbot::Point2D& point)
    {
      if(inst_)
      {
        inst_->drawPoint(point);
      }
    }

    void update()
    {
      if(inst_)
      {
        inst_->update();
      }
    }

    void reset()
    {
      if(inst_)
      {
        inst_->reset();
      }
    }

    bool active()
    {
      return !(inst_ == NULL);
    }

  private:
    DrawCallbacks* inst_;
  };  // class Debug
  
  static Draw draw;
}  // namespace sgbot

#endif  // _DRAW_H_
