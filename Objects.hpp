#ifndef __OBJECTS__
#define __OBJECTS__

#include "ObjMap/ObjMap.hpp"
#include "BonusMap/BonusMap.hpp"

class Objects
{
public:
  ObjMap::Block		block;
  ObjMap::BlockDes	wall;
  ObjMap::Ground	ground;
  ObjMap::BlockFire	blockFire;
  BonusMap::BombUp	bBomb;
  BonusMap::SpeedUp	bSpeed;
  BonusMap::FireUp	bRange;
  BonusMap::HeartUp	bLife;
  BonusMap::Light	bLight;

  Objects();
  ~Objects();
};

#endif
