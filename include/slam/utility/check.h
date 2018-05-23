/* Created slam/utility/check.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_UTILITY_CHECK_H_
#define _SLAM_UTILITY_CHECK_H_

#include <type/lidar2d.h>

namespace sgbot {
namespace slam {

  bool checkFitScan(sgbot::Lidar2d& scan)
  {
    for(int i = 0; i < scan.getCount(); i++)
    { 
      
    }
  }

}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_UTILITY_CHECK_H_
