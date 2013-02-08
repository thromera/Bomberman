#include "Objects.hpp"

Objects::Objects(void)
{
  wall.initialize();
  block.initialize();
  ground.initialize();
  bBomb.initialize();
  bSpeed.initialize();
  bRange.initialize();
  bLife.initialize();
  bLight.initialize();
  blockFire.initialize();
}

Objects::~Objects(void)
{

}
