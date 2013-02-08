#ifndef __AOB__
#define __AOB__

#include "Pos3f.hpp"

class AObject
{
protected:
  Pos3f pos_;
  Pos3f rot_;

public:
  AObject(void) : pos_(0.0f, 0.0f, 0.0f), rot_(0.0f, 0.0f, 0.0f) { }
  virtual void initialize(void) = 0;
  virtual void initialize(float const &, float const &, float const &) = 0;
  virtual void update(gdl::GameClock const &, gdl::Input &) = 0;
  virtual void draw(void) = 0;
};

#endif
