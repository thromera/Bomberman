#include "all.hpp"
#include <iomanip>
#include <SFML/Audio.hpp>
#include "MyGame.hpp"
#include "TextMap.hpp"
#include "EndGame.hpp"
#include "Music.hpp"

EndGame::EndGame()
{
  music_ = new Music;
}

EndGame::~EndGame(void)
{
  delete music_;
}

void	EndGame::endMusic()
{
  music_->stopSong();
}

void	EndGame::startMusic()
{
  mu = false;
}


void EndGame::initialize_()
{
 this->textureP1w_ = gdl::Image::load("Textures/bombermanp1w.png");
 this->textureP2w_ = gdl::Image::load("Textures/bombermanp2w.png");
 this->textureIaa_ = gdl::Image::load("Textures/bomberman_ia.png");   
}

void EndGame::initialize(void)
{
  this->pos_.setPos(0.0, 0.0, 1.0);
  this->initialize_();
}

void EndGame::initialize(float x, float y, float z)
{
  this->pos_.setPos(x, y, z);
  this->initialize_();
}
  
void EndGame::update()
{
   camera_.initializeN();
}

void EndGame::draw(WhoWin who)
{
  if(mu == false)  
    {
      music_->playSong("endS");  
      mu = true;
    }
  this->update();
  if(who == P1)
  textureP1w_.bind();
  else if (who == P2)
    textureP2w_.bind();
  else
    textureIaa_.bind();
  
  glClearColor(0.55f ,0.0f, 0.55f, 1.0f);
  glClearDepth(1.0f);
  
  glPushMatrix();
  glBegin(GL_QUADS);
  glTexCoord2d(0,0); glVertex3f(-BACKGROUND, BACKGROUND, BACKGROUND);
  glTexCoord2d(0,1); glVertex3f(-BACKGROUND, -BACKGROUND, BACKGROUND);
  glTexCoord2d(1,1); glVertex3f(BACKGROUND, -BACKGROUND, BACKGROUND);
  glTexCoord2d(1,0); glVertex3f(BACKGROUND, BACKGROUND, BACKGROUND);
  glEnd();
  glPopMatrix();  
}
