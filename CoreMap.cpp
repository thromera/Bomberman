#include <sstream>
#include <fstream>
#include <cstdlib>
#include "CoreMap.hpp"
#include "ObjMap/ObjMap.hpp"
#include "BonusMap/BonusMap.hpp"


std::vector<std::vector<Ibloc> >	CoreMap::getMap() const
{
  return _map;
}

unsigned int				CoreMap::getXMax() const
{
  return _xmax;
}

unsigned int				CoreMap::getYMax() const
{
  return _ymax;
}

void					CoreMap::setXMax(const unsigned int &x)
{
  this->_xmax = x;
}

void					CoreMap::setYMax(const unsigned int &y)
{
  this->_ymax = y;
}

void					CoreMap::setObjects(Objects * obj)
{
  this->_obj = obj;
}

void					CoreMap::setMap(std::vector<std::vector<Ibloc> > &map)
{
  this->_map = map;
}

Ibloc					CoreMap::genBonus(const Option& opt)
{
  Ibloc		ret = DES;

  if (rand() % 100 <= opt.getBonusDensity())
    {
      ret = (Ibloc)(rand() % 5 + (DES + 1));
    }
  return ret;
}

void					CoreMap::adjustMapWithPlayers(std::list<APlayer*> playerList)
{
  int	x = 0;
  int	y = 0;
  std::list<APlayer*>::iterator it = playerList.begin();

  while (it != playerList.end())
    {
      if ((*it)->getX() < this->getXMax() / 2 && (*it)->getY() < getYMax() / 2)
	{
	  this->_map[(*it)->getY()][(*it)->getX() + 1] = VOID;
	  this->_map[(*it)->getY() + 1][(*it)->getX()] = VOID;
	}
      else if ((*it)->getX() > this->getXMax() / 2 && (*it)->getY() < getYMax() / 2)
	{
	  this->_map[(*it)->getY() + 1][(*it)->getX()] = VOID;
	  this->_map[(*it)->getY()][(*it)->getX() - 1] = VOID;
	}
      else if ((*it)->getX() < this->getXMax() / 2 && (*it)->getY() > getYMax() / 2)
	{
	  this->_map[(*it)->getY()][(*it)->getX() + 1] = VOID;
	  this->_map[(*it)->getY() - 1][(*it)->getX()] = VOID;
	}
      else
	{
	  this->_map[(*it)->getY()][(*it)->getX() - 1] = VOID;
	  this->_map[(*it)->getY() - 1][(*it)->getX()] = VOID;
	}
      this->_map[(*it)->getY()][(*it)->getX()] = VOID;
      it++;
    }
}


void					CoreMap::genMap(const Option & opt)
{
  std::vector<Ibloc>	tmp;
  int			xmax = opt.getXMap();
  int			ymax = opt.getYMap();
  int	x = 0;
  int	y = 0;

  _xmax = opt.getXMap();
  _ymax = opt.getYMap();
  while (y < ymax)
    {
      while (x < xmax)
	{
	  if (y == 0 || y == ymax - 1 || x == 0 || x == xmax - 1 || (y % 2 == 0 && x % 2 == 0))
	    tmp.push_back(INDES);
	  else if ((y >= 1 && y <= 2 && (x == 1 || x == xmax - 2)) ||
		   (y >= ymax - 3 && y <= ymax - 2 && (x == 1 || x == xmax - 2)) ||
		   (x >= 1 && x <= 2 && (y == 1 || y == ymax - 2)) ||
		   (x >= xmax - 3 && x <= xmax - 2 && (y == 1 || y == ymax - 2)))
	    tmp.push_back(VOID);
	  else if (rand() % 100 < opt.getDensityBloc())
	    tmp.push_back(genBonus(opt));
	  else
	    tmp.push_back(VOID);
	  x++;
	}
      this->_map.push_back(tmp);
      tmp.clear();
      x = 0;
      y++;
    }
}

Ibloc					CoreMap::getAt(const double &dx, const double &dy) const
{
  unsigned int	x, y;

  x = ROUND(dx);
  y = ROUND(dy);
  return _map[dy][dx];
}

void					CoreMap::draw()
{
  int x		= 0;
  int y		= 0;

  glPushMatrix();
  glTranslatef(-(this->getXMax() * DEMI), 0, -(this->getYMax() * DEMI));

  while (y < this->getYMax())
    {
      while (x < this->getXMax())
	{
	  if (_map[y][x] == DES ||_map[y][x] == DESR || _map[y][x] == DESB || _map[y][x] == DESS || _map[y][x] == DESL || _map[y][x] == DESC)
	    {
	      this->_obj->wall.initialize(x * SIZE_BLOC, 0, y * SIZE_BLOC);
	      this->_obj->wall.draw();
	    }
	  else if (_map[y][x] == SPEED)
	    {
	      this->_obj->bSpeed.initialize(x * SIZE_BLOC, 0, y * SIZE_BLOC);
	      this->_obj->bSpeed.draw();
	    }
	  else if (_map[y][x] == BOMB)
	    {
	      this->_obj->bBomb.initialize(x * SIZE_BLOC, 0, y * SIZE_BLOC);
	      this->_obj->bBomb.draw();
	    }
	  else if (_map[y][x] == RANGE)
	    {
	      this->_obj->bRange.initialize(x * SIZE_BLOC, 0, y * SIZE_BLOC);
	      this->_obj->bRange.draw();
	    }
	  else if (_map[y][x] == LIFE)
	    {
	      this->_obj->bLife.initialize(x * SIZE_BLOC, 0, y * SIZE_BLOC);
	      this->_obj->bLife.draw();
	    }
	  else if (_map[y][x] == LIGHT)
	    {
	      this->_obj->bLight.initialize(x * SIZE_BLOC, 0, y * SIZE_BLOC);
	      this->_obj->bLight.draw();
	    }
	  else if (_map[y][x] == INDES)
	    {
	      this->_obj->block.initialize(x * SIZE_BLOC, 0, y * SIZE_BLOC);
	      this->_obj->block.draw();
	    }
	  else
	    {
	      this->_obj->ground.initialize(x * SIZE_BLOC, 0, y * SIZE_BLOC);
	      this->_obj->ground.draw();
	    }
	  if (_map[y][x] == BOMB || _map[y][x] == RANGE || _map[y][x] == SPEED || _map[y][x] == LIFE || _map[y][x] == LIGHT)
	    {
	      this->_obj->ground.initialize(x * SIZE_BLOC, 0, y * SIZE_BLOC);
	      this->_obj->ground.draw();
	    }
	  x++;
	}
      x = 0;
      y++;
    }
  glPopMatrix();
}

void					CoreMap::setAt(const double & dx, const double &dy, Ibloc value)
{
  double	x, y;

  x = ROUND(dx);
  y = ROUND(dy);
  _map[y][x] = value;
}
