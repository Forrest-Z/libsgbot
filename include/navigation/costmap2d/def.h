/* Created navigation/costmap2d/def.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _NAVIGATION_COSTMAP2D_DEF_H_
#define _NAVIGATION_COSTMAP2D_DEF_H_

namespace sgbot {
namespace nav {

  typedef unsigned char CostValue;

  const CostValue UNKNOWN_SPACE = 255;
  const CostValue LETHAL_OBSTACLE = 254;
  const CostValue INFLATED_OBSTACLE = 253;
  const CostValue KNOWN_SPACE = 0;

}  // namespace nav
}  // namespace sgbot

#endif  // _NAVIGATION_COSTMAP2D_DEF_H_
