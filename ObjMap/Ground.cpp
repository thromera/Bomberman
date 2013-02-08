#include "ObjMap.hpp"

namespace ObjMap
{
  void Ground::initialize(void)
  {
    this->texture_ = gdl::Image::load("Textures/floor.png");
  }

  void Ground::initialize(float const & x, float const & y, float const & z)
  {
    this->pos_.setPos(x, y, z);
  }

  void Ground::update(gdl::GameClock const & gameClock, gdl::Input & input)
  {
    (void) gameClock;
    (void) input;
  }

  void Ground::draw(void)
  {
    texture_.bind();
    glPushMatrix();
    glTranslatef(this->pos_.getX(), this->pos_.getY() - SIZE_BLOC, this->pos_.getZ());

    glBegin(GL_QUADS);

    /// Vertex superieur gauche
    glTexCoord2d(0, 1); glVertex3f(-DEMI, DEMI, DEMI);
    /// Vertex superieur gauche
    glTexCoord2d(0, 0); glVertex3f(-DEMI, DEMI, -DEMI);
    /// Vertex superieur gauche
    glTexCoord2d(1, 0); glVertex3f(DEMI, DEMI, -DEMI);
    /// Vertex superieur gauche
    glTexCoord2d(1, 1); glVertex3f(DEMI, DEMI, DEMI);

    glEnd();
    glPopMatrix();
  }
}
