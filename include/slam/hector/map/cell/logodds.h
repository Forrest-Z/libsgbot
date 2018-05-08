/* Created slam/hector/map/cell/logodds.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SLAM_HECTOR_MAP_CELL_LOG_ODDS_H_
#define _SLAM_HECTOR_MAP_CELL_LOG_ODDS_H_

#include <common/exception.h>
#include <slam/hector/map/cell/base.h>
#include <distribution/functions.h>

namespace sgbot {
namespace slam {
namespace hector {

  class LogOddsCell : public CellBase {
  public:
    LogOddsCell() 
    {
      reset();
    }
    
    virtual ~LogOddsCell() {}

    virtual bool isOccupied() const
    {
      return value > 0.0f;
    }

    virtual bool isFree() const
    {
      return value < 0.0f;
    }

    virtual void reset()
    {
      value = 0.0f;
      index = -1;
    }

  };  // class LogOddsCell


  class LogOddsCellFactor {
  public:
    LogOddsCellFactor()
    {
      setFreeFactor(0.4f);
      setOccupiedFactor(0.6f);
    }

    virtual ~LogOddsCellFactor() {}

    void setOccupied(LogOddsCell& cell) const
    {
      if (cell.value < 50.0f)
      {
        cell.value += log_odds_occupied_;
      }
      // debug
      //std::cout << "setOccupied: " << cell.index << "," << cell.value << std::endl;
    }

    void setFree(LogOddsCell& cell) const
    {
      cell.value += log_odds_free_;

      // debug
      //std::cout << "setFree: " << cell.index << "," << cell.value << std::endl;
    }

    void unsetFree(LogOddsCell& cell) const
    {
      cell.value -= log_odds_free_;

      // debug
      //std::cout << "unsetFree: " << cell.index << "," << cell.value << std::endl;
    }

    float getProbability(const LogOddsCell& cell) const
    {
      float result = sgbot::distr::logistic(cell.value);

      // debug
      //std::cout << "getProbability:" << result << ",cell.getValue:" << cell.value << std::endl;

      return result;
    }

    void setFreeFactor(float factor)
    {
      log_odds_free_ = sgbot::distr::logit(factor);
      // debug
      //std::cout << "log_odds_free_:" << log_odds_free_ << ",factor:" << factor << std::endl;
    }

    void setOccupiedFactor(float factor)
    {
      log_odds_occupied_ = sgbot::distr::logit(factor);
      // debug
      //std::cout << "log_odds_occupied_:" << log_odds_occupied_ << ",factor:" << factor << std::endl;
    }

  private:

    float log_odds_occupied_;
    float log_odds_free_;

  };  // class LogOddsCellFactor

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_CELL_LOG_ODDS_H_
