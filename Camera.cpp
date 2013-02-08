#include "all.hpp"
#include "Camera.hpp"

Camera::Camera(void) : pos_(0.0f, 0.0f, 900.0f), rot_(0.0f, 0.0f, 0.0f)
{
}

void		Camera::reset_cam_menu(void)
{
  pos_.x = 0.0f;
  pos_.y = 0.0f;
  pos_.z = 900.0f;

  posn_.x = 0.0f;
  posn_.y = 0.0f;
  posn_.z = -1.0f;
}

void		Camera::reset_cam_game(float const & x, float const & y)
{
  pos_.x = 0.0f;
  pos_.y = (x + y) * (DEMI/1.5);
  pos_.z = 1200.0f;

  posn_.x = 0.0f;
  posn_.y = 0.0f;
  posn_.z = -1.0f;

}

void		Camera::initialize(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, LARGEUR_ECRAN/HAUTEUR_ECRAN, 1.0f, 10000.0f);
  gluLookAt(pos_.x, pos_.y, pos_.z,
	    posn_.x, posn_.y, posn_.z,
	    0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void		Camera::initializeN(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, LARGEUR_ECRAN/HAUTEUR_ECRAN, 1.0f, 10000.0f);
  gluLookAt(pos_.x, pos_.y, pos_.z,0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void		Camera::initialize(float const & a, float const & b)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, LARGEUR_ECRAN/HAUTEUR_ECRAN, 1.0f, 10000.0f);
  pos_.x = a + b;
  gluLookAt(pos_.x, pos_.y, pos_.z,
	    posn_.x, pos_.y, posn_.z,
	    0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void		Camera::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(pos_.x, pos_.y, pos_.z,
	    posn_.x, posn_.y, posn_.z,
	    0.0f, 1.0f, 0.0f);
  (void) gameClock;
  (void) input;
}

void		Camera::getKeys(gdl::GameClock const & gameClock, gdl::Input & input)
{
  if (input.isKeyDown(gdl::Keys::W) == true)
    this->pos_.y += 25;
  if (input.isKeyDown(gdl::Keys::S) == true)
    this->pos_.y -= 25;
  if (input.isKeyDown(gdl::Keys::A) == true)
    this->pos_.x -= 25;
  if (input.isKeyDown(gdl::Keys::D) == true)
    this->pos_.x += 25;

  this->update(gameClock, input);
}

Pos3f		Camera::getPos(void) const
{
  return this->pos_;
}

Pos3f		Camera::getPosn(void) const
{
  return this->posn_;
}

Pos3f		Camera::getRot(void) const
{
  return this->rot_;
}

void		Camera::setPos(Pos3f const & pos)
{
  this->pos_ = pos;
}

void		Camera::setPosn(Pos3f const & posn)
{
  this->posn_ = posn;
}

void		Camera::setRot(Pos3f const & rot)
{
  this->rot_ = rot;
}
