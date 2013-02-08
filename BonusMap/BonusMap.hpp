#ifndef __BONUSMAP__
#define __BONUSMAP__

#include "../all.hpp"
#include "../AObject.hpp"
#include "../Pos3f.hpp"

#define POWER_UP	500.0f
#define DEMI_UP		POWER_UP / 2
#define BORDER_UP	DEMI_UP / 2

namespace BonusMap
{
  class FireUp : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };

  class HeartUp : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };

  class BombUp : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };

  class SpeedUp : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };

  class Light : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };
}

#endif
