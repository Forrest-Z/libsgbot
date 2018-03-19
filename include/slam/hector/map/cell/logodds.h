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
#include <distribution/functions.h>

namespace sgbot {
namespace slam {
namespace hector {

  class LogOddsCell {
  public:
    LogOddsCell() {}
    
    virtual ~LogOddsCell() {}

    void setValue(float value)
    {
      value_ = value;
    }

    float getValue() const
    {
      return value_;
    }

    void setIndex(int index)
    {
      update_index_ = index;
    }

    int getIndex() const
    {
      return update_index_;
    }

    bool isOccupied() const
    {
      return value_ > 0.0f;
    }

    bool isFree() const
    {
      return value_ < 0.0f;
    }

    void reset()
    {
      value_ = 0.0f;
      update_index_ = -1;
    }

  private:
    float value_;
    int update_index_;
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
      float cell_value = cell.getValue();
      if (cell_value < 50.0f)
      {
        cell.setValue(cell_value + log_odds_occupied_);
      }
    }

    void setFree(LogOddsCell& cell) const
    {
      float cell_value = cell.getValue();
      cell.setValue(cell_value + log_odds_free_);
    }

    void unsetFree(LogOddsCell& cell) const
    {
      float cell_value = cell.getValue();
      cell.setValue(cell_value - log_odds_free_);
    }

    float getProbability(const LogOddsCell& cell) const
    {
      return sgbot::distr::logistic(cell.getValue());
    }

    void setFreeFactor(float factor)
    {
      log_odds_free_ = sgbot::distr::logit(factor);
    }

    void setOccupiedFactor(float factor)
    {
      log_odds_occupied_ = sgbot::distr::logit(factor);
    }

  private:

    float log_odds_occupied_;
    float log_odds_free_;

  };  // class LogOddsCellFactor

}  // namespace hector
}  // namespace slam
}  // namespace sgbot

#endif  // _SLAM_HECTOR_MAP_CELL_LOG_ODDS_H_
