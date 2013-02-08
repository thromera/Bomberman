#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "Core.hpp"
#include "Ia.hpp"
#include "all.hpp"
#include "MyGame.hpp"

#define ABS(a) (((a) < 0) ? -(a) : (a))

Ia::Ia(MyGame *realmygame, APlayer *ia)
{
  this->_ia = ia;
  this->_myGameTmp = realmygame;
}

Ia::~Ia()
{
}

void				Ia::toBonnus(gdl::Input& a, gdl::GameClock &b)
{
  if (this->_myGameTmp->canMove(this->_ia, this->_dirBonnus) >= VOID)
    {
      this->_ia->changeDir(this->_dirBonnus);
      this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), a);
    }
  

}

bool				Ia::isNextZoneSafe(int x, int y)
{
  std::list<Bomb*> bom = this->_myGameTmp->getCore().getBomb();
  std::list<Bomb*>::iterator it = bom.begin();
  
  while (it != bom.end())
    {
      if (((int)(*it)->getX() == (int)x && ABS( (int)(*it)->getY() - (int)y ) <= (*it)->getRange()) || ((int)(*it)->getY() == (int)y && ABS((int)(*it)->getX() - (int)x) <= (*it)->getRange()))
	return false;
      ++it;
    }
  return true;
}

int				Ia::toBonnus()
{
  int				i = 0;
  int				x = this->_ia->getX();
  int				y = this->_ia->getY();
  int				xMax = this->_myGameTmp->getCore().getMap()->getXMax();
  int				yMax = this->_myGameTmp->getCore().getMap()->getYMax();

  std::vector<std::vector<Ibloc> > map = this->_myGameTmp->getCore().getMap()->getMap();
  while (x > 0)
    {
      x--;
      if (isNextZoneSafe(x,y))
	{
	  if (map[y][x] == VOID);
	  else if (map[y][x] >= 8)
	    {
	      this->_dirBonnus = LEFT;
	      return 10000;
	    }
	  else
	    break;
	}
      else 
	break;
    }

  x = this->_ia->getX();

  while (x < xMax)
    {
      x++;
      if (isNextZoneSafe(x,y))
	{
	  if (map[y][x] == VOID);
	  else if (map[y][x] >= 7)
	    {
	      this->_dirBonnus = RIGHT;
	      return 10000;
	    }
	  else
	    break;
	}
      else 
	break;
    }

  x = this->_ia->getX();

  while (y < yMax)
    {
      y++; 
      if (isNextZoneSafe(x,y))
	{
	  if (map[y][x] == VOID);
	  else if (map[y][x] >= 7)
	    {
	      this->_dirBonnus = DOWN;
	      return 10000;
	    }
	  else
	    break;
	}
      else 
	break;
    }

  y = this->_ia->getY();

  while (y > 0)
    {
      y--;
      if (isNextZoneSafe(x,y))
	{
	  if (map[y][x] == VOID);
	  else if (map[y][x] >= 7)
	    {
	      this->_dirBonnus = UP;
	      return 10000;
	    }
	  else
	    break;
	}
      else 
	break;
    }
  return 0;
}

bool				Ia::proxDesAndVoid(int x, int y)
{

}

int				Ia::toPutBomb()
{
  if ((int)this->_ia->getX() % 2 == 0 || (int)this->_ia->getY() % 2 == 0)
    return 2;
  return 0;
}

void				Ia::turnRand(gdl::Input& input_, gdl::GameClock& a)
{
  int i = rand() % 4;

  if (i == 0 && this->_myGameTmp->canMove(this->_ia, RIGHT) >= VOID)
    {
      this->_ia->changeDir(RIGHT);
      this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
    }
  else if (i == 1 && this->_myGameTmp->canMove(this->_ia, UP) >= VOID)
    {
      this->_ia->changeDir(UP);
      this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
    }
  else if (i == 2 && this->_myGameTmp->canMove(this->_ia, DOWN) >= VOID)
    {
      this->_ia->changeDir(DOWN);
      this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
    }
  else if (this->_myGameTmp->canMove(this->_ia, LEFT) >= VOID)
    {
      this->_ia->changeDir(LEFT);
      this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
    }
}

void				Ia::putBomb(gdl::Input &a, gdl::GameClock &b)
{
  if (this->_ia->getCaracteristique().getActualBomb() < this->_ia->getCaracteristique().getMaxBomb() && this->_myGameTmp->getCore().hasBombOnPos((unsigned int)this->_ia->getX(), (unsigned int)this->_ia->getY()) == false)
    {
      this->_myGameTmp->getCore().addBomb(new Bomb(this->_ia, b.getTotalGameTime()));
      this->_ia->getCaracteristique().putBomb();
    }
}

int				Ia::safeZone()
{
  double x = this->_ia->getX();
  double y = this->_ia->getY();
  std::list<Bomb*> bom = this->_myGameTmp->getCore().getBomb();
  std::list<Bomb*>::iterator it = bom.begin();
  int	index = 0;

  while (it != bom.end())
    {
      if ( ((int)(*it)->getX() == (int)x && ABS( (int)(*it)->getY() - (int)y ) <= (*it)->getRange()) || ((int)(*it)->getY() == (int)y && ABS((int)(*it)->getX() - (int)x) <= (*it)->getRange()))
	{
	  this->_indexBomb = index;
	  return 1000;
	}
      index++;
      ++it;
    }
  return 0;
}

Direction				Ia::recSaferDir(unsigned int x, unsigned int y, Direction dir, unsigned int size)
{
  if (size == 5)
    return dir;
  if (dir != DOWN && this->_myGameTmp->canMove(_ia->getX(), _ia->getY(), DOWN, _ia->getCaracteristique().getSpeed()) >= VOID)
    dir = recSaferDir(x , y + 0.2 * _ia->getCaracteristique().getSpeed(), DOWN, size + 1);
  if (dir != UP && this->_myGameTmp->canMove(_ia->getX(), _ia->getY(), UP, _ia->getCaracteristique().getSpeed()) >= VOID)
    dir = recSaferDir(x, y - 0.2 * _ia->getCaracteristique().getSpeed(), UP, size + 1);
  if ( dir != LEFT && this->_myGameTmp->canMove(_ia->getX(), _ia->getY(), LEFT, _ia->getCaracteristique().getSpeed()) >= VOID)
    dir = recSaferDir(x - 0.2 * _ia->getCaracteristique().getSpeed(), y, LEFT, size + 1);
  if (dir != RIGHT && this->_myGameTmp->canMove(_ia->getX(), _ia->getY(), RIGHT, _ia->getCaracteristique().getSpeed()) >= VOID)
    dir = recSaferDir(x + 0.2 * _ia->getCaracteristique().getSpeed(), y, RIGHT, size + 1);
  return dir;
}

Direction				Ia::getSaferDir()
{
  Direction	ret;

  ret = recSaferDir(_ia->getX(), _ia->getY(), _ia->getDirection(), 0);
  return ret;
}

void					Ia::outOfBomb(gdl::Input & input_, gdl::GameClock &b)
{
  std::list<Bomb*> bom = this->_myGameTmp->getCore().getBomb();
  std::list<Bomb*>::iterator it = bom.begin();
  int	i = 0;
  double x = this->_ia->getX();
  double y = this->_ia->getY();

  while (i < this->_indexBomb)
    {
      it++;
      i++;
    }

  std::vector<std::vector<Ibloc> > map = this->_myGameTmp->getCore().getMap()->getMap();

  if ((int)(*it)->getY() == (int)y && ABS((int)(*it)->getX() - (int)x) <= (*it)->getRange()) // SUR LA LIGNE
    {
      if (map[(int)y - 1][(int)x] == VOID && this->_myGameTmp->canMove(this->_ia, UP) >= VOID)
	{
	  this->_ia->changeDir(UP);
	  this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
	}
      else if (map[(int)y + 1][(int)x] == VOID && this->_myGameTmp->canMove(this->_ia, DOWN) >= VOID)
	{
	  this->_ia->changeDir(DOWN);
	  this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
	}
      else
	{
	  if (map[(int)y][(int)x - 1] == VOID && (int)(*it)->getX() - (int)x >= 0 && this->_myGameTmp->canMove(this->_ia, LEFT) >= VOID)
	    {
	      this->_ia->changeDir(LEFT);
	      this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
	    }
	  else if (this->_myGameTmp->canMove(this->_ia, RIGHT) >= VOID)
	    {
	      this->_ia->changeDir(RIGHT);
	      this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
	    }
	}
    }
  else if ((int)(*it)->getX() == (int)x && ABS((int)(*it)->getY() - (int)y) <= (int)(*it)->getRange())
    {
      if (map[(int)y][(int)x - 1] == VOID && this->_myGameTmp->canMove(this->_ia, LEFT) >= VOID)
	{
	  this->_ia->changeDir(LEFT);
	  this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
	}
      else if (map[(int)y][(int)x + 1] == VOID && this->_myGameTmp->canMove(this->_ia, RIGHT) >= VOID)
	{
	  this->_ia->changeDir(RIGHT);
	  this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
	}
      else
	{
	  if ((int)(*it)->getY() - (int)y >= 0 && this->_myGameTmp->canMove(this->_ia, UP) >= VOID)
	    {
	      this->_ia->changeDir(UP);
	      this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
	    }
	  else if (this->_myGameTmp->canMove(this->_ia, DOWN) >= VOID)
	    {
	      this->_ia->changeDir(DOWN);
	      this->_ia->update(*(this->_myGameTmp->getCore().getGameClock()), input_);
	    }
	}
    }
}

typedef struct s_ft1
{
  const char *str;
  int (Ia::*f)();
}t_ft1;

t_ft1 tab[]=
{
  {"safeZone",&Ia::safeZone},
  {"toputbomb",&Ia::toPutBomb},
  {"tobonnus",&Ia::toBonnus},
  {0,0}
};

typedef struct s_ft2
{
  const int a;
  void (Ia::*f)(gdl::Input&, gdl::GameClock&);
}t_ft2;

t_ft2 tab2[]=
  {
    {0,&Ia::outOfBomb},
    {1,&Ia::putBomb},
    {2,&Ia::toBonnus},
    {2,0}
  };

void Ia::fillVecPoids(gdl::Input &a, gdl::GameClock& b)
{
  int i = 0;

  while (tab[i].str)
    {
      this->_poids.push_back((this->*tab[i].f)());
      i++;
    }

  std::vector<int>::iterator it = this->_poids.begin();
  int indexValMax = -1;
  int valMax = 0;
  i = 0;

  while (it != this->_poids.end())
    {
      if ((*it) > valMax)
	{
	  valMax = *it;
	  indexValMax = i;
	}
      ++it;
      i++;
    }
  if (valMax > 0)
    (this->*tab2[indexValMax].f)(a, b);
  else
    this->turnRand(a, b);
  this->_poids.clear();
}
