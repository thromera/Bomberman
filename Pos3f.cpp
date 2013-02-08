#include "Pos3f.hpp"

Pos3f::Pos3f(void) : x(0.0f), y(0.0f), z(0.0f)
{
}

Pos3f::Pos3f(float x, float y, float z) : x(x), y(y), z(z)
{
}

Pos3f::~Pos3f()
{
}

void		Pos3f::setPos(const float x, const float y, const float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

float		Pos3f::getX() const 
{
  return(this->x);
}

float		Pos3f::getY() const 
{
  return(this->y);
}

float		Pos3f::getZ() const 
{
  return(this->z);
}


void Pos3f::setX(const float x)
{
  this->x = x;
}

void Pos3f::setY(const float y)
{
  this->y = y;
}

void Pos3f::setZ(const float z)
{
  this->z = z;
}
