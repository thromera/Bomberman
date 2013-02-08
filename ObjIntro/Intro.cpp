#include "../all.hpp"
#include <iomanip>
#include <SFML/Audio.hpp>
#include "Intro.hpp"
#include "../MyGame.hpp"
#include "../TextMap.hpp"
#include "../Music.hpp"



Intro::Intro(void)
{
  music_ = new Music;
}

Intro::~Intro(void)
{
  delete music_;
}

void Intro::initialize_()
{
  music_->playSong("introS");
  this->texture_ = gdl::Image::load("Textures/test1.jpg");
  this->model_.initialize();
  this->text_.setSize(55);   
  this->model_.initialize(-200,-450,1000);
}

void Intro::initialize(void)
{
  this->pos_.setPos(0.0, 0.0, 1.0);
  this->initialize_();
}

void Intro::initialize(float const & x, float const & y, float const & z)
{
  this->pos_.setPos(x, y, z);
  this->initialize_();
}
  
int Intro::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  if (input.isKeyDown(gdl::Keys::P) == true)
    {   
      music_->stopSong();
      return(MENU);
    } 
  this->model_.update(gameClock, input);
  this->model_.play(gameClock);
  this->model_.set_anim_speed("Take 001",4.0);
  return(INTRO); 
}



void Intro::draw(void)
{
  this->model_.draw();
  texture_.bind();
  glClearColor(0.55f ,0.0f, 0.55f, 1.0f);
  glClearDepth(1.0f);
  
  glPushMatrix();
  //  glLoadIdentity();
  glRotatef(90,1,0,0);
  glBegin(GL_QUADS);
  /// Vertex superieur gauche
  glTexCoord2d(0,1); glVertex3f(-BACK, BACK, BACK);
  /// Vertex superieur gauche
  glTexCoord2d(0,0); glVertex3f(-BACK, BACK, -BACK);
  /// Vertex superieur gauche
  glTexCoord2d(1,0); glVertex3f(BACK, BACK, -BACK);
  /// Vertex superieur gauche
  glTexCoord2d(1,1); glVertex3f(BACK, BACK, BACK);
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-500, 200, 1000);
  this->text_.putStr("Press \"P\" to START! \n");   
  glPopMatrix();    
}
