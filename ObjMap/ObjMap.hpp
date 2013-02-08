#ifndef __OBJMAP__
#define __OBJMAP__

#include "../all.hpp"
#include "../AObject.hpp"
#include "../Pos3f.hpp"
#include "../TextMap.hpp"
#include "../BonusMap/BonusMap.hpp"
#include "../Caracteristique.hpp"

namespace ObjMap
{
  class Wall : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };

  class Ground : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };

  class Block : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };


  class BlockFire : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };

  class BlockDes : public AObject
  {
  public:
    void initialize(void);
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  private:
    gdl::Image	texture_;
  };
  
  class Panel
  {
  public:
    Panel();
    ~Panel();
    void initialize();
    void initialize(float const & x, float const & y, float const & z);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(Caracteristique const & cara, int const & i);
  
  private:
    BonusMap::BombUp      * bu_;
    BonusMap::SpeedUp     * su_;
    BonusMap::FireUp      * fu_;
    BonusMap::HeartUp     * hu_;
    TextMap               * text_;
    int                   x_;
    int                   y_;

    void draw_player_one_(Caracteristique const & cara);
    void draw_player_two_(Caracteristique const & cara);
    int checkValue_(int const & value) const; 
  };
}

#endif
