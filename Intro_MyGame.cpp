#include "all.hpp"
#include "Menu.hpp"
#include "MyGame.hpp"
#include "ObjIntro/Intro.hpp"
#include "TextMap.hpp"

void		MyGame::initialize_intro_(void)
{
  intro_ = new Intro();
  intro_->initialize();
}

void		MyGame::update_intro_(gdl::GameClock const & gameClock, gdl::Input & input)  
{
  this->posMenu_.where_ =  intro_->update(gameClock,input);  
  camera_.update(gameClock_, input_);
}

void		MyGame::draw_intro_(void)
{
  intro_->draw();
}
