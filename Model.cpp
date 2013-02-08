#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "Model.hpp"

#define UPP	1
#define LEFTT	2
#define DOWNN	3
#define RIGHTT	4

namespace Model
{
  /* BomberMarvin */
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
    this->pos_.setPos(1.0 * SIZEBLOC, -280.0, 1 * SIZEBLOCK);
    this->rot_.setPos(0, 0, 0);
    this->model_.cut_animation(model_,"Take 001", 55, 65,"new_anim");
  }

  void Bomberman::initialize(float const & x, float const & y, float const & z)
  {
    this->model_ = gdl::Model::load("assets/marvin.fbx");
    this->pos_.setPos(x, y, z);
    this->rot_.setPos(0, 0, 0);
  }
  
  
  
  void Bomberman::update(gdl::GameClock const & gameClock, gdl::Input & input)
  {
    this->model_.update(gameClock);
    if (input.isKeyDown(gdl::Keys::P) == true)
      this->model_.play("new_anim");
    
    if (input.isKeyDown(gdl::Keys::Right) == true)
      {
	this->changeDir_(RIGHTT);
	this->pos_.x = this->pos_.x + 100 ;
	this->model_.play("new_anim");
      }
    else if (input.isKeyDown(gdl::Keys::Left) == true )
      {
	this->changeDir_(LEFTT);
	this->pos_.x = this->pos_.x - 100 ;
	this->model_.play("new_anim");
      }
    else if (input.isKeyDown(gdl::Keys::Down) == true)
      {
	this->changeDir_(DOWNN);
	this->pos_.z = this->pos_.z + 100 ;
	this->model_.play("new_anim");
      }
    else if (input.isKeyDown(gdl::Keys::Up) == true)
      {
	this->changeDir_(UPP);
	this->pos_.z = this->pos_.z - 100 ;
	this->model_.play("new_anim");
      }
  }
    void Bomberman::changeDir_(int n)
  {
    if (this->dir + 2 == n || this->dir - 2 == n)
      this->rot_.y = ((int)rot_.y + 180) % 360;
    else if (this->dir + 1 == n || this->dir - 3 == n)
      this->rot_.y = ((int)rot_.y + 90) % 360;
    else if (this->dir - 1 == n || this->dir + 3 == n)
      this->rot_.y = ((int)rot_.y - 90) % 360;
    this->dir = n;
  }

  void Bomberman::draw(void)
  {
    glPushMatrix();
    glTranslatef(this->pos_.getX(), this->pos_.getY(), this->pos_.getZ());
    glRotatef(this->rot_.getY(), 0.0f, 1.0f, 0.0f);
    this->model_.draw();
    glPopMatrix();
  }

  /* Bomb */
  Bomb::Bomb(void)
  {
  }

  Bomb::~Bomb(void)
  {
  }

  void Bomb::initialize(void)
  {
    this->model_ = gdl::Model::load("assets/bomb.fbx");
    this->pos_.setPos(0.0, 0.0, 1.0);
    this->rot_.setPos(100.0, 40.0, 40.0);
  }

  void Bomb::initialize(float const & x, float const & y, float const & z)
  {
    this->model_ = gdl::Model::load("assets/bomb.fbx");
    this->pos_.setPos(x, y, z);
    this->rot_.setPos(100.0, 40.0, 40.0);
  }
  


  void Bomb::draw(void)
  {
    /// Affichage du modele
    glPushMatrix();
    glTranslatef(this->pos_.getX(), this->pos_.getY(), this->pos_.getZ());
    glRotatef(this->rot_.getX(), this->rot_.getY(), this->rot_.getZ(), 1);
    this->model_.draw();
    glPopMatrix();
  }
}
