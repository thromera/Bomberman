#include <sstream>

#include "ObjMap.hpp"

namespace ObjMap
{
  Panel::Panel()
  {

  }

  Panel::~Panel()
  {
    delete hu_;
    delete fu_;
    delete bu_;
    delete su_;
    delete text_;
  }

  void Panel::initialize()
  {
    fu_ = new (BonusMap::FireUp);
    hu_ = new (BonusMap::HeartUp);
    su_ = new (BonusMap::SpeedUp);
    bu_ = new (BonusMap::BombUp);
    text_ = new TextMap("font/panda_bonus.png");
    text_->setSize(DEMI);//SIZE_BLOC);
    fu_->initialize();
    su_->initialize();
    bu_->initialize();
    hu_->initialize();
  }

  void Panel::initialize(float const & x, float const & y, float const & z)
  {
    x_ = x;
    y_ = y;
    (void)z;
    hu_->initialize(-4.5 * SIZE_BLOC, SIZE_BLOC, y * DEMI);
    fu_->initialize(-2.5 * SIZE_BLOC, SIZE_BLOC, y * DEMI);
    su_->initialize(-0.5 * SIZE_BLOC, SIZE_BLOC, y * DEMI);
    bu_->initialize(1.5 * SIZE_BLOC, SIZE_BLOC, y * DEMI);
  }

  void Panel::update(gdl::GameClock const & gclock, gdl::Input & input)
  {
    (void) gclock;
    (void) input;
  }

  int		Panel::checkValue_(int const & value) const
  {
    if (value > 9)
      return (9);
    else if (value < 0)
      return (0);
    return(value);
  }

  void 	Panel::draw_player_one_(Caracteristique const & cara)
  {
    std::ostringstream		life;
    std::ostringstream		range;
    std::ostringstream		speed;
    std::ostringstream		bomb;

    life << checkValue_(cara.getLife());
    range << checkValue_(cara.getRange() + 1);
    speed << checkValue_(cara.getSpeed() - 2);
    bomb << checkValue_(cara.getMaxBomb());
    glPushMatrix();
    glTranslatef(-5.5 * SIZE_BLOC, SIZE_BLOC + DEMI, (y_ * DEMI));
    text_->putStr("P1");
    glTranslatef(2 * SIZE_BLOC, 0, 0);
    text_->putStr(life.str());
    glTranslatef(2 * SIZE_BLOC, 0, 0);
    text_->putStr(range.str());
    glTranslatef(2 * SIZE_BLOC, 0, 0);
    text_->putStr(speed.str());
    glTranslatef(2 * SIZE_BLOC, 0, 0);
    text_->putStr(bomb.str());
    glPopMatrix();
  }

  void 	Panel::draw_player_two_(Caracteristique const & cara)
  {
    std::ostringstream		life;
    std::ostringstream		range;
    std::ostringstream		speed;
    std::ostringstream		bomb;

    life << checkValue_(cara.getLife());
    range << checkValue_(cara.getRange() + 1);
    speed << checkValue_(cara.getSpeed() - 2);
    bomb << checkValue_(cara.getMaxBomb());
    glPushMatrix();
    glTranslatef(-5.5 * SIZE_BLOC, SIZE_BLOC + DEMI, (y_ * DEMI) + DEMI);
    text_->putStr("P2");
    glTranslatef(2 * SIZE_BLOC, 0, 0);
    text_->putStr(life.str());
    glTranslatef(2 * SIZE_BLOC, 0, 0);
    text_->putStr(range.str());
    glTranslatef(2 * SIZE_BLOC, 0, 0);
    text_->putStr(speed.str());
    glTranslatef(2 * SIZE_BLOC, 0, 0);
    text_->putStr(bomb.str());
    glPopMatrix();
  }

  void Panel::draw(Caracteristique const & cara, int const & i)
  {
    if (i == 0)
      {
	hu_->draw();
	fu_->draw();
	su_->draw();
	bu_->draw();
	this->draw_player_one_(cara);	
      }
    else
      this->draw_player_two_(cara);
  }
}
