#include "ObjMenu.hpp"
#include "../Menu.hpp"

namespace ObjMenu
{
  MenuBomb::MenuBomb(void)
  {
  }

  MenuBomb::~MenuBomb(void)
  {
  }
  
  void		MenuBomb::reset_bomb(float const & y)
  {
    this->pos_.y = y;
  }

  void		MenuBomb::initialize_()
  {
    this->model_ = gdl::Model::load("assets/bomb.fbx");
    this->rot_.setPos(0.0, 0.0, 0.0);
    this->space_ = SPACE_MENU;
  }

  void		MenuBomb::initialize()
  {
    this->pos_.setPos(0, 0, 0);
    this->initialize_();
  }  

  void		MenuBomb::initialize(float const & y)
  {
    this->pos_.setPos(0, y, 0);
    this->initialize_();
  }

  void		MenuBomb::setSpace(float const & size)
  {
    this->space_ = size;
  }

  void		MenuBomb::update(float const & y)
  {
    this->pos_.y = y;
  }

  void		MenuBomb::draw(void)
  {
    glPushMatrix();
    glTranslatef(-(LARGEUR_ECRAN), (HAUTEUR_ECRAN) - (HAUTEUR_ECRAN / 2), 0);
    glTranslatef(this->pos_.getX(), -(this->pos_.getY() * this->space_), 0);
    this->model_.draw();
    glPopMatrix();
  }
}
