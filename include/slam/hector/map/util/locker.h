/* Created slam/hector/map/util/locker.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_UTIL_LOCKER_H_
#define _SLAM_HECTOR_MAP_UTIL_LOCKER_H_

#include <common/exception.h>
#include <boost/thread/mutex.hpp>

namespace sgbot {
namespace slam {
namespace hector {

  class MapLocker {
  public:
    MapLocker() {}
    virtual ~MapLocker() {}

    void lock()
    {
      mutex_.lock();
    }

    void unlock()
    {
      mutex_.unlock();
    }

  private:
    boost::mutex mutex_;
  };  // class MapLocker

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_UTIL_LOCKER_H_
