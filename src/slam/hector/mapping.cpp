/* Created slam/hector/mapping.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#include <slam/hector/mapping.h>

namespace sgbot {
namespace slam {
namespace hector {

  void HectorMapping::updateByScan(const sgbot::sensor::Lidar2D& scan)
  {
    processor_->update((scan * processor_->getMapScaleFactor()), processor_->getLastScanMatchPose(), true);
  }

  void updateByScanWithGyro(const sgbot::sensor::Lidar2D& scan, const sgbot::sensor::Gyro& gyro)
  {

  }

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

