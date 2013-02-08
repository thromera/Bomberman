#include <unistd.h>
#include <iostream>
#include "Music.hpp"
#include "APlayer.hpp"
#include "all.hpp"
#include "Core.hpp"

APlayer::APlayer(const unsigned int& id, const double& posx, const double& posy, Caracteristique* carac, bool ia)
{
  this->_id = id;
  this->_pos = new Position(posx, posy);
  this->_carac = carac;
  this->_ia = ia;
  this->_dir = UP;
}

APlayer::APlayer(const unsigned int& id, Position* pos, Caracteristique* carac, bool ia)
{
  this->_id = id;
  this->_pos = pos;
  this->_carac = carac;
  this->_dir = UP;
  this->_ia = ia;
}

void			APlayer::initialize(void)
{
  int	j = rand() % 250;
  int	k = rand() % 250;
  int	n = rand() % 250;
  int   i = rand() % 250;
  _dir = DOWN; 
  this->_model = gdl::Model::load("assets/marvin.fbx");
  gdl::Color random(i,n,j,k);
 
  this->_model.set_default_model_color(random);
  this->_pos3f.setPos(1.5 * SIZE_BLOC, -280.0, 1.5 * SIZE_BLOC);
  this->_rot.setPos(0, 0, 0);
  this->_model.cut_animation(_model,"Take 001", 55, 65,"new_anim");
}

void			APlayer::initialize(float x, float y, float z)
{
  this->_model = gdl::Model::load("assets/marvin.fbx");
  this->_pos3f.setPos(x, y, z);
  this->_rot.setPos(0, 0, 0);
}

Position&		APlayer::getPosition(void) const
{
  return *_pos;
}

Caracteristique&	APlayer::getCaracteristique(void) const
{
  return *_carac;
}

Direction		APlayer::getDirection(void) const
{
  return this->_dir;
}

gdl::Model      APlayer::getModel(void) const
{
  return this->_model;
}

unsigned int		APlayer::getId(void) const
{
  return this->_id;
}

double			APlayer::getX(void) const
{
  return this->_pos->_x;
}

double			APlayer::getY(void) const
{
  return this->_pos->_y;
}

bool      APlayer::isIA() const
{
  return this->_ia;
}

void			APlayer::setPosition(Position*& pos)
{
  this->_pos = pos;
}

void			APlayer::setPosition(const double& x, const double& y)
{
  this->_pos = new Position(x, y);
}

void			APlayer::setCaracteristique(Caracteristique*& carac)
{
  this->_carac = carac;
}

void			APlayer::setDirection(const Direction& dir)
{
  this->_dir = dir;
}

void			APlayer::takeDamage(const unsigned int& damage, Core* core)
{
  std::list<APlayer*> pl;

  pl = core->getPlayer();
  if (this->getCaracteristique().getLife() > 0)
    this->getCaracteristique().setLife(this->getCaracteristique().getLife() - damage);
}

void			APlayer::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  Direction dir;

  this->_model.update(gameClock);
  dir = this->getDirection();
  switch (dir)
    {
    case RIGHT :
      this->changeDir(RIGHT);
      this->setPosition(this->getX() + SCALE_SPEED * this->getCaracteristique().getSpeed(), this->getY());
      break;
    case LEFT :
      this->changeDir(LEFT);
      this->setPosition(this->getX() - SCALE_SPEED * this->getCaracteristique().getSpeed(), this->getY());
      break;
    case DOWN : 
      this->changeDir(DOWN);
      this->setPosition(this->getX(), this->getY() + SCALE_SPEED * this->getCaracteristique().getSpeed());
      break;
    default :
      this->changeDir(UP);
      this->setPosition(this->getX(), this->getY() - SCALE_SPEED * this->getCaracteristique().getSpeed());
    }
 this->_model.play("new_anim");
}

void			APlayer::changeDir(Direction n)
{
  if (this->_dir + 2 == n || this->_dir - 2 == n)
    this->_rot.y = ((int)_rot.y + 180) % 360;
  else if (this->_dir + 1 == n || this->_dir - 3 == n)
    this->_rot.y = ((int)_rot.y + 90) % 360;
  else if (this->_dir - 1 == n || this->_dir + 3 == n)
    this->_rot.y = ((int)_rot.y - 90) % 360;
  this->_dir = (Direction)n;
}

void			APlayer::draw(const CoreMap* map)
{
  glPushMatrix();
  glTranslatef(-((double)map->getXMax() / 2) * SIZE_BLOC, 0 , -((double)map->getYMax() /2) * SIZE_BLOC);
  glTranslatef((this->getX()) * SIZE_BLOC, -280.0, (this->getY()) * SIZE_BLOC);
  glTranslatef(-0.5 * SIZE_BLOC, 0, -0.5 * SIZE_BLOC);
  glRotatef(this->_rot.getY(), 0.0f, 1.0f, 0.0f);
  this->_model.draw();
  glPopMatrix();
}

void      APlayer::addBonus(const unsigned int& bonus)
{
  switch (bonus)
    {
    case LIFE :
      this->getCaracteristique().increaseLife(1);
      break;
    case BOMB :
      this->getCaracteristique().increaseBomb(1);
      break;
    case SPEED :
      this->getCaracteristique().increaseSpeed(1);
      break;
    case RANGE :
      this->getCaracteristique().increaseRange(1);
      break;
    }
}
