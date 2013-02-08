#include "Game.hpp"
#include "Option.hpp"
#include <string>
#include <iostream>

Option::Option(const int & x, const int & y, const int & dens, const unsigned int & nb_player, const unsigned int & nb_ia)
{
  this->setXMap(x);
  this->setYMap(y);
  this->setDensityBloc(dens);
  this->setNbPlayer(nb_player);
  this->setNbIa(nb_ia);
  this->_bonus = 50;
}

Option::~Option()
{
}

void		Option::setXMap(const int & x)
{
  if (this->_xMap > x)
    this->_xMap = x - 1;
  else if (x % 2 == 0)
    this->_xMap = x + 1;
  else
    this->_xMap = x;
  if (this->_xMap < 9)
    this->_xMap = 9;
  if (this->_xMap > 19)
    this->_xMap = 19;
}

int		Option::getXMap() const
{
  return this->_xMap;
}

void		Option::setYMap(const int & y)
{
  if (this->_yMap > y)
    this->_yMap = y - 1;
  else if (y % 2 == 0)
    this->_yMap = y + 1;
  else
    this->_yMap = y;
  if (this->_yMap < 9)
    this->_yMap = 9;
  if (this->_yMap > 19)
    this->_yMap = 19;
}

int		Option::getYMap() const
{
  return this->_yMap;
}

void		Option::setDensityBloc(const int & d)
{
  this->_densityBloc = d;
  if (d > 100)
    this->_densityBloc = 0;
  else if (d < 0)
    this->_densityBloc = 100;
}

int		Option::getDensityBloc() const
{
  return this->_densityBloc;
}

void		Option::setNbPlayer(const unsigned int & nb)
{
  this->_nbPlayer = nb;
  if (nb > 2)
    this->_nbPlayer = 2;
  else if (nb < 1)
  this->_nbPlayer = 1;
}

unsigned int	Option::getNbPlayer() const
{
  return this->_nbPlayer;
}

void		Option::setNbIa(const int & nb)
{
  this->_nbIa = nb;
  if (nb > 10)
    this->_nbIa = 0;
  else if (nb < 0)
    this->_nbIa = 10;
}

unsigned int	Option::getNbIa() const
{
  return this->_nbIa;
}

void          Option::setBonusDensity(int const & nb)
{
  this->_bonus = nb;
  if (nb > 100)
    this->_bonus = 0;
  else if (nb < 0)
    this->_bonus = 100;
}

unsigned int	Option::getBonusDensity() const
{
  return this->_bonus;
}
