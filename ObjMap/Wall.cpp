#include "ObjMap.hpp"

namespace ObjMap
{
  void Wall::initialize(void)
  {
    this->texture_ = gdl::Image::load("Textures/caisse.jpg");
  }

  void Wall::initialize(float const & x, float const & y, float const & z)
  {
    this->pos_.setPos(x, y, z);
  }

  void Wall::update(gdl::GameClock const & gameClock, gdl::Input & input)
  {
    (void) gameClock;
    (void) input;
  }

  void Wall::draw(void)
  {
    texture_.bind();
    glPushMatrix();
    glTranslatef(this->pos_.getX(), this->pos_.getY(), this->pos_.getZ());

    glBegin(GL_QUADS);

    //    glColor3f(0.0f, 0.10f, 2.05f);
    /// Vertex superieur gauche
    glTexCoord2d(0.33, 1); glVertex3f(-DEMI, DEMI, DEMI);
    /// Vertex inferieur gauche
    glTexCoord2d(0.33, 0.33); glVertex3f(-DEMI, -DEMI, DEMI);
    /// Vertex inferieur droit
    glTexCoord2d(1, 0.33); glVertex3f(DEMI, -DEMI, DEMI);
    /// Vertex superieur droit
    glTexCoord2d(1, 1); glVertex3f(DEMI, DEMI, DEMI);

    //    glColor3f(1.0f, 0.10f, 2.05f);
    /// Vertex superieur gauche
    glTexCoord2d(0.33, 1); glVertex3f(-DEMI, DEMI, -DEMI);
    /// Vertex inferieur gauche
    glTexCoord2d(0.33, 0.33); glVertex3f(-DEMI, -DEMI, -DEMI);
    /// Vertex inferieur droit
    glTexCoord2d(1, 0.33); glVertex3f(-DEMI, -DEMI, DEMI);
    /// Vertex superieur droit
    glTexCoord2d(1, 1); glVertex3f(-DEMI, DEMI, DEMI);

    /// Vertex superieur gauche
    glTexCoord2d(0.33, 1); glVertex3f(DEMI, DEMI, -DEMI);
    /// Vertex inferieur gauche
    glTexCoord2d(0.33, 0.33); glVertex3f(DEMI, -DEMI, -DEMI);
    /// Vertex inferieur droit
    glTexCoord2d(1, 0.33); glVertex3f(-DEMI, -DEMI, -DEMI);
    /// Vertex superieur droit
    glTexCoord2d(1, 1); glVertex3f(-DEMI, DEMI, -DEMI);

    /// Vertex superieur gauche
    glTexCoord2d(0.33, 1); glVertex3f(DEMI, DEMI, DEMI);
    /// Vertex inferieur gauche
    glTexCoord2d(0.33, 0.33); glVertex3f(DEMI, -DEMI, DEMI);
    /// Vertex inferieur droit
    glTexCoord2d(1, 0.33); glVertex3f(DEMI, -DEMI, -DEMI);
    /// Vertex superieur droit
    glTexCoord2d(1, 1); glVertex3f(DEMI, DEMI, -DEMI);

    //    glColor3f(1.0f, 1.10f, 0.05f);
    /// Vertex superieur gauche
    glTexCoord2d(0, 1); glVertex3f(-DEMI, DEMI, DEMI);
    /// Vertex superieur gauche
    glTexCoord2d(0, 0); glVertex3f(-DEMI, DEMI, -DEMI);
    /// Vertex superieur gauche
    glTexCoord2d(0.33, 0); glVertex3f(DEMI, DEMI, -DEMI);
    /// Vertex superieur gauche
    glTexCoord2d(0.33, 1); glVertex3f(DEMI, DEMI, DEMI);

    glEnd();
    glPopMatrix();
  }
}
