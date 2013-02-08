#include <iostream>
#include "Caracteristique.hpp"

Caracteristique::Caracteristique(const unsigned int& life)
{
  this->_life = 1;
  this->_speed = 2;
  this->_actualBomb = 0;
  this->_maxBomb = 1;
  this->_range = 0;
}

const unsigned int&				Caracteristique::getLife() const
{
  return this->_life;
}

const unsigned int&				Caracteristique::getSpeed() const
{
  return this->_speed;
}

const unsigned int&				Caracteristique::getMaxBomb(void) const
{
  return this->_maxBomb;
}

const unsigned int&				Caracteristique::getActualBomb(void) const
{
  return this->_actualBomb;
}

const unsigned int&				Caracteristique::getRange(void) const
{
  return this->_range;
}

void						Caracteristique::setLife(const unsigned int& life)
{
  this->_life = life;
}

void						Caracteristique::setSpeed(const unsigned int& speed)
{
  this->_speed = speed;
}

void						Caracteristique::setRange(const unsigned int& range)
{
  this->_range = range;
}

void						Caracteristique::setActualBomb(const unsigned int& bomb)
{
  this->_actualBomb = bomb;
}

void						Caracteristique::setMaxBomb(const unsigned int& maxBomb)
{
  this->_maxBomb = maxBomb;
}

bool						Caracteristique::putBomb(void)
{
  if (this->_actualBomb < _maxBomb)
    {
      _actualBomb++;
      return true;
    }
  return false;
}

void						Caracteristique::delBomb(void)
{
  this->_actualBomb--;
}

void						Caracteristique::increaseSpeed(const unsigned int& toAdd)
{
  if (this->_speed < 6)
    this->_speed += toAdd;
}

void						Caracteristique::increaseLife(const unsigned int& toAdd)
{
  this->_life += toAdd;
}
void						Caracteristique::increaseRange(const unsigned int& toAdd)
{
  this->_range += toAdd;
}

void						Caracteristique::increaseBomb(const unsigned int& toAdd)
{
  this->_maxBomb += toAdd;
}
