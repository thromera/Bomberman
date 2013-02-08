#include <stdlib.h>
#include <unistd.h>
#include "Model.hpp"
#include <iostream>

#define UPP	1
#define LEFTT	2
#define DOWNN	3
#define RIGHTT	4

namespace Model
{
  Bomberman::Bomberman(void)
  {
    
  }
  
  Bomberman::~Bomberman(void)
  {
    
  }
  
  void Bomberman::initialize(void)
  {
    monboll = false; 
    dir = DOWN; 
    this->model_ = gdl::Model::load("assets/marvin.fbx");
    this->pos_.setPos(0.0, -280.0, 0.0);
    this->rot_.setPos(0, 0, 0);
    this->model_.cut_animation(model_,"Take 001", 30, 65,"new_anim_intro");
    this->toui = 0;
  }

  void Bomberman::initialize(float const & x, float const & y, float const & z)
  {
    this->pos_.setPos(x, y, z);
    this->rot_.setPos(0, 0, 0);
  }


  void Bomberman::changeDir_(int n)
  {
    std::cout << this->dir << " - " << n << std::endl; 
    if (this->dir + 2 == n || this->dir - 2 == n)
      this->rot_.y = ((int)rot_.y + 180) % 360;
    else if (this->dir + 1 == n || this->dir - 3 == n)
      this->rot_.y = ((int)rot_.y + 90) % 360;
    else if (this->dir - 1 == n || this->dir + 3 == n)
      this->rot_.y = ((int)rot_.y - 90) % 360;
    this->dir = n;
  }

  void Bomberman::play(gdl::GameClock const & gameClock)
  {
    this->model_.update(gameClock);
    this->model_.play("new_anim_intro");
  }
  
  void Bomberman::set_anim_speed(std::string const &name,double speed)
  {
    this->model_.set_anim_speed(name,speed);
  }
  
  
  void Bomberman::update(gdl::GameClock const & gameClock, gdl::Input & input)
  {  
    this->model_.update(gameClock);
    if (input.isKeyDown(gdl::Keys::P) == true)
      this->model_.play("new_anim_intro");
  }

  void Bomberman::draw(void)
  {
    glPushMatrix();
    glTranslatef(this->pos_.getX(), this->pos_.getY(), this->pos_.getZ());
    glRotatef(this->rot_.getY(), 0.0f, 1.0f, 0.0f);
    this->rot_.x = ((int)rot_.x - 1) % 360;
    this->model_.draw();
    glPopMatrix();
  }

}
