#ifndef __MODEL__
#define __MODEL__

#include "../all.hpp"
#include "../AObject.hpp"
#include "../Pos3f.hpp"

namespace Model
{
  class Bomberman : public AObject
  {
  public:
    Bomberman(void);
    ~Bomberman(void);
    void initialize(void);
    void initialize(float const &, float const &, float const &);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
    void play(gdl::GameClock const & gameClock);
    void set_anim_speed(std::string const & name,double speed);

    enum direction {UP=1,LEFT=2,DOWN=3,RIGHT=4};
  private:
    int dir;
    void changeDir_(int n);
    void setDirection(direction dir, int);
    Pos3f	pos_;
    Pos3f	rot_;
    bool monboll;
    gdl::Model model_;
    int toui;

  };
}

#endif
