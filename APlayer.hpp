#ifndef __APLAYER_HPP__
#define __APLAYER_HPP__

#include "all.hpp"
#include "Position.hpp"
#include "Caracteristique.hpp"
#include "Pos3f.hpp"
#include "CoreMap.hpp"
#include "Music.hpp"

#define MULT 20

/*
** Player class
*/

class Core;
class CoreMap;

enum			Direction
  {
    UP,
    LEFT,
    DOWN,
    RIGHT
  };



class			APlayer
{
public:
  APlayer(const unsigned int& id, const double& posx, const double& posy, Caracteristique*, bool _ia = true);
  APlayer(const unsigned int& id, Position* pos, Caracteristique* carac, bool _ia = true);

private:
  unsigned int			_id;
  Position*			_pos;
  Caracteristique*		_carac;
  Direction			_dir;
  bool			        _ia;
  Pos3f			        _pos3f;
  Pos3f			        _rot;
  gdl::Model			_model; 

public:
  void			        initialize(void);
  void			        initialize(float, float, float);

  Position&			getPosition(void) const;
  Caracteristique&		getCaracteristique(void) const;
  unsigned int			getId(void) const;
  Direction			getDirection(void)const;
  double		        getX(void) const;
  double		        getY(void) const;
  gdl::Model			getModel(void) const;
  void			        setPosition(Position*& pos);
  void			        setPosition(const double& x, const double& y);
  void			        setCaracteristique(Caracteristique*& carac);
  void			        setDirection(const Direction &direction);
  void			        takeDamage(const unsigned int&, Core* core);

  bool			        isIA() const;


  void			        update(gdl::GameClock const & gameClock, gdl::Input & input);
  void			        draw(const CoreMap* map);
  void			        changeDir(Direction);
  void				addBonus(const unsigned int& bonus);
};

#endif
