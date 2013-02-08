#ifndef __BOMB_HPP__
#define __BOMB_HPP__

#include "all.hpp"
#include "Position.hpp"
#include "MyGame.hpp"
#include "Core.hpp"
#include "Music.hpp"

class Core;
class			Bomb
{
public:
  Bomb(const double& x, const double& y, const unsigned int & id, const unsigned int & range, const float& startTimer);
  Bomb(APlayer* player, const float& startTimer);
  ~Bomb();

private:
  ObjMap::BlockFire       BlockFire;
  unsigned int		  _idPlayer;
  unsigned int		  _range;
  float			  _delayMs;
  float			  _startTimer;
  Position*		  _pos;
  gdl::Model		  _model;
  Pos3f			  _rot;
  
public:
  void			draw(const CoreMap*, const float& time);
  void			draw_explode_(const CoreMap*);
  Position&		getPosition(void) const;
  double&		getX(void) const;
  double& 		getY(void) const;
  const unsigned int&	getIdPlayer(void) const;
  const unsigned int&   getRange(void) const;
  const float&		getTimer(void) const;
  const float&		getDelay(void) const;
  bool			isExpired(const float& time) const;

  void			setDelay(const float &d);
  void			setPosition(Position*&);
  void			setX(const double&);
  void			setY(const double&);
  void			setTimer(const float & timer);
  void			setIdPlayer(const unsigned int&);
  void			setRange(const unsigned int&);
  void			explose(Core *);
  int			touiter(int const & , int const &, Core *);
};

#endif
