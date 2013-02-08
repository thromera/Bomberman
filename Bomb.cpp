#include <SFML/Audio.hpp>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include "Bomb.hpp"
#include "Music.hpp"
#include "EndGame.hpp"

Bomb::Bomb(const double& x, const double& y, const unsigned int & id, const unsigned int & range, const float& startTimer)
{
  this->_pos = new Position(x, y);
  this->_idPlayer = id;
  this->_range = range;
  this->_startTimer = startTimer;
  this->_delayMs = 3;
  this->_model = gdl::Model::load("assets/bomb.fbx");
  this->_rot.setPos(x * SIZE_BLOC, 40.0, y * SIZE_BLOC);
}

Bomb::Bomb(APlayer* player, const float& startTimer)
{
  this->_pos = new Position((int)player->getX() + 0.5, (int)player->getY() + 0.5);
  this->_idPlayer = player->getId();
  this->_range = player->getCaracteristique().getRange() + 1;
  this->_startTimer = startTimer;
  this->_delayMs = 3;
  this->_model = gdl::Model::load("assets/bomb.fbx");
  this->_rot.setPos(player->getX() * SIZE_BLOC, 40.0, player->getY() * SIZE_BLOC);
}


Bomb::~Bomb()
{
  delete this->_pos;
}

bool			Bomb::isExpired(const float& time) const 
{
  if (_startTimer + _delayMs < time)
  {
    return true;
  }
  return false;
}

Position&		Bomb::getPosition(void) const
{
  return *this->_pos;
}

double&			Bomb::getX(void) const
{
  return this->_pos->_x;
}

double&     Bomb::getY(void) const
{
  return this->_pos->_y;
}

const float&     Bomb::getTimer(void) const
{
  return this->_startTimer;
}

const float&     Bomb::getDelay(void) const
{
  return this->_delayMs;
}

const unsigned int&		Bomb::getIdPlayer(void) const
{
  return this->_idPlayer;
}

const unsigned int&		Bomb::getRange(void) const
{
  return this->_range;
}

void			Bomb::setDelay(const float &d)
{
  this->_delayMs = d;
}

void      Bomb::setTimer(const float & timer)
{
  this->_startTimer = timer;
}

void			Bomb::setPosition(Position*& pos)
{
  this->_pos = pos;
}

void			Bomb::setX(const double& x)
{
  this->_pos->_x = x;
}

void			Bomb::setY(const double& y)
{
  this->_pos->_y = y;
}

void			Bomb::setIdPlayer(const unsigned int& id)
{
  this->_idPlayer = id;

}

void			Bomb::setRange(const unsigned int& r)
{
  this->_range = r;
}

int 			Bomb::touiter(int const & x, int const & y, Core * game)
{
  Ibloc     bloc;
  Ibloc			nbloc;

  game->isPlayer(x, y);
  bloc = game->getMap()->getAt(x, y);
  if (bloc != VOID)
    {
      if (bloc == DES || bloc == DESB || bloc == DESR || bloc == DESS || bloc == DESL || bloc == DESC)
	{
	  bloc == DESB ? nbloc = BOMB :
	    bloc == DESS ? nbloc = SPEED :
	    bloc == DESR ? nbloc = RANGE :
	    bloc == DESL ? nbloc = LIFE :
	    bloc == DESC ? nbloc = LIGHT :
	    nbloc = VOID;
	  game->getMap()->setAt(x, y, nbloc);
	}
      else if (bloc == BOMB || bloc == SPEED || bloc == RANGE || bloc == LIFE || bloc == LIGHT)
	game->getMap()->setAt(x, y, VOID);
      return 0;
    }
  return 1;
}

void			Bomb::explose(Core * game)
{
  std::vector<std::vector<Ibloc> >	gmap;
  unsigned int				x;
  unsigned int				y;
  unsigned int        size_explose = this->_range;

  gmap = game->getMap()->getMap();
  y = this->_pos->_y;
  for (x = this->_pos->_x; x <= this->_pos->_x + size_explose && x <= game->getXMax(); x++)
    if (touiter(x, y, game) == 0)
      break;
  for (x = this->_pos->_x - 1; x >= this->_pos->_x - size_explose - 1 && x >= 0; x--)
    if (touiter(x, y, game) == 0)
      break;
  x = this->_pos->_x;
  for (y = this->_pos->_y + 1; y <= this->_pos->_y + size_explose && y <= game->getYMax(); y++)
    if (touiter(x, y, game) == 0)
      break;
  for (y = this->_pos->_y - 1; y >= this->_pos->_y - size_explose - 1 && y >= 0; y--)
    if (touiter(x, y, game) == 0)
      break;
  
}

void			Bomb::draw_explode_(const CoreMap* map)
{
  Ibloc			bloc;
  int			x = 0;
  int			y = 0;
  int			size_explose = this->_range - 1;

  this->BlockFire.initialize();
  BlockFire.initialize(this->getX() , -230, this->getY());
  BlockFire.draw();
  y = this->_pos->_y;
  glPushMatrix();
  for (x = this->_pos->_x + 1; x <= this->_pos->_x + this->_range && x <= map->getXMax(); x++)
    {
      bloc = map->getAt(x, y);
      glTranslatef(SIZE_BLOC, 0, 0);
      BlockFire.draw();
      if (bloc != VOID)
        break;
    }
  glPopMatrix();
  glPushMatrix();
  for (x = this->_pos->_x - 1; x >= this->_pos->_x - this->_range - 1 && x >= 0; x--)
    {
      bloc = map->getAt(x, y);
      glTranslatef(-SIZE_BLOC, 0, 0);
      BlockFire.draw();
      if (bloc != VOID)
	break;
    }
  glPopMatrix();
  x = this->_pos->_x;
  glPushMatrix();
  for (y = this->_pos->_y + 1; y <= this->_pos->_y + this->_range && y <= map->getYMax(); y++)
    {
      bloc = map->getAt(x, y);
      glTranslatef(0, 0, SIZE_BLOC);
      BlockFire.draw();
      if (bloc != VOID)
	break;
    }
  glPopMatrix();
  glPushMatrix();
  for (y = this->_pos->_y - 1; y >= this->_pos->_y - this->_range - 1 && y >= 0; y--)
    {
      bloc = map->getAt(x, y);
      glTranslatef(0, 0, -SIZE_BLOC);
      BlockFire.draw();
      if (bloc != VOID)
	break;
    }
  glPopMatrix();

}

void			Bomb::draw(const CoreMap* map, const float& time)
{
  glPushMatrix();
  glTranslatef(-((double)map->getXMax() / 2) * SIZE_BLOC, 0 , -((double)map->getYMax() /2) * SIZE_BLOC);
  glTranslatef(this->getX() * SIZE_BLOC, -230, this->getY() * SIZE_BLOC);
  glTranslatef(-0.5 * SIZE_BLOC, 0, -0.5 * SIZE_BLOC);
  this->_model.draw();
  if (_startTimer + _delayMs - 0.3f < time)
    this->draw_explode_(map);
  glPopMatrix();
}
