#include "all.hpp"
#include "TextMap.hpp"

TextMap::TextMap(): xMax_(16), yMax_(16), size_(100)
{
  this->setMap("font/panda.png");
  this->content_ = "";
  this->pop_ = false;
}

TextMap::TextMap(std::string const & file): xMax_(16), yMax_(16), size_(100)
{
  this->setMap(file);
  this->content_ = "";
  this->pop_ = false;
}

TextMap::TextMap(std::string const & file, int nbCharX, int nbCharY): xMax_(nbCharX), yMax_(nbCharY), size_(100)
{
  this->setMap(file);
  this->content_ = "";
  this->pop_ = false;
}

TextMap::~TextMap()
{

}

void		TextMap::setContent(std::string const & content)
{
  this->content_ = content;
  this->pop_ = true;
}

void		TextMap::setPopup(bool const & pop)
{
  this->pop_ = pop;
}

void		TextMap::setMap(std::string const & file)
{
  this->texture_ = gdl::Image::load(file);
}

void		TextMap::setSize(int size)
{
  this->size_ = size;
}

void		TextMap::putChar(char c)
{
  float		l = (this->size_ * 8) / 10;
  float		a = 1.0f / this->xMax_;
  float		b = 1.0f / this->yMax_;

  float		x1 = (c % this->xMax_) * a;
  float		y1 = (c / this->yMax_) * b;
  float		x2 = x1 + a;
  float		y2 = y1 + b;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  texture_.bind();
  glBegin(GL_QUADS);
  glTexCoord2d(x1, y1); glVertex3f(-l, l, l);
  glTexCoord2d(x1, y2); glVertex3f(-l, -l, l);
  glTexCoord2d(x2, y2); glVertex3f(l, -l, l);
  glTexCoord2d(x2, y1); glVertex3f(l, l, l);
  glEnd();
  glDisable(GL_BLEND);
}

void		TextMap::putStr(std::string const str)
{
  int		i = 0;

  glPushMatrix();
  while(str[i])
  {
    if (str[i] != '\n')
    {
     this->putChar(str[i++]);
     glTranslatef(this->size_, 0, 0);
   }
   else 
   {
     i++;
     glPopMatrix();
     glPushMatrix();
     glTranslatef(0, -this->size_, 0);
     this->putStr(str.substr(i));
     break;
   }
 }
 glPopMatrix();
}

void		TextMap::popup(void)
{
  if (this->pop_ == true)
    {
      glPushMatrix();
      glTranslatef(-500, 0, 0);
      this->putStr(this->content_);
      glPopMatrix();
    }
}
