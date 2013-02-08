#include <sstream>
#include <fstream>
#include <iostream>
#include "all.hpp"
#include "Menu.hpp"
#include "MyGame.hpp"
#include "ObjMenu/ObjMenu.hpp"
#include "TextMap.hpp"
#include "Music.hpp"

void				MyGame::reset_menu_(void)
{
  this->posMenu_.where_ = MENU;
  this->posMenu_.who_ = OPTION_ONE;
  this->posMenu_.what_ = MENU_FIRST;
  this->camera_.reset_cam_menu();
}

void				MyGame::initialize_menu_(void)
{
  this->text_ = new TextMap;
  this->items_.initialize();
  this->reset_menu_();
}


void					MyGame::menu_map_(void)
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->key_ == false)
    {
      switch (this->items_.update(0, this->posMenu_.what_))
	{
	case OPTION_ONE:
	  {
	    this->text_->setContent("Content In DLC !");
	    break;
	  }
	case OPTION_TWO:
	  {
	    this->text_->setContent("Content In DLC !");
	    break;
	  }
	case OPTION_THR:
	  {
	    //	    Song so;
	    /// so = gameS;
	    music_->playSong("gameS");
	    endGame_->startMusic();
	    this->camera_.reset_cam_game(this->options_->getXMap(), this->options_->getYMap());
	    delete(this->_core);
	    this->new_game();
	    this->posMenu_.where_ = GAME;
	    this->items_.setNewGame(false);
	    break;
	  }
	case MAX_MAP:
	  {
	    this->posMenu_.what_ = MENU_FIRST;
	    this->posMenu_.who_ = OPTION_ONE;
	    this->items_.update(this->posMenu_.who_);
	    break;
	  }
	}
    }
}

void					MyGame::menu_optGen_(void)
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->key_ == false)
    {
      switch (this->items_.update(0, this->posMenu_.what_))
	{
	case OPTION_ONE:
	  {
	    this->posMenu_.what_ = MENU_OPTMAP;
	    this->posMenu_.who_ = OPTION_ONE;
	    this->items_.update(this->posMenu_.who_);
	    break;
	  }
	case OPTION_TWO:
	  {
	    this->posMenu_.what_ = MENU_OPTPLAY;
	    this->posMenu_.who_ = OPTION_ONE;
	    this->items_.update(this->posMenu_.who_);
	    break;
	  }
	case OPTION_THR:
	  {
	    this->posMenu_.what_ = MENU_CREDITS;
	    this->posMenu_.who_ = OPTION_ONE;
	    this->items_.update(this->posMenu_.who_);
	    break;
	  }
	case MAX_OPTGEN:
	  {
	    this->posMenu_.what_ = MENU_FIRST;
	    this->posMenu_.who_ = OPTION_ONE;
	    this->items_.update(this->posMenu_.who_);
	    break;
	  }
	}
    }
}

void					MyGame::menu_credits_(void)
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->key_ == false)
    {
      this->posMenu_.what_ = MENU_OPTGEN;
      this->posMenu_.who_ = OPTION_ONE;
      this->items_.update(this->posMenu_.who_);
    }
}

void					MyGame::menu_optMap_(void)
{
  switch (this->items_.update(0, this->posMenu_.what_))
    {
    case OPTION_ONE:
      {
	if (input_.isKeyDown(gdl::Keys::Right) == true && this->key_ == false)
	  this->options_->setXMap(this->options_->getXMap() + 1);
	if (input_.isKeyDown(gdl::Keys::Left) == true && this->key_ == false)
	  this->options_->setXMap(this->options_->getXMap() - 1);
	break;
      }
    case OPTION_TWO:
      {
	if (input_.isKeyDown(gdl::Keys::Right) == true && this->key_ == false)
	  this->options_->setYMap(this->options_->getYMap() + 1);
	if (input_.isKeyDown(gdl::Keys::Left) == true && this->key_ == false)
	  this->options_->setYMap(this->options_->getYMap() - 1);
	break;
      }
    case OPTION_THR:
      {
	if (input_.isKeyDown(gdl::Keys::Right) == true && this->key_ == false)
	  this->options_->setDensityBloc(this->options_->getDensityBloc() + 5);
	if (input_.isKeyDown(gdl::Keys::Left) == true && this->key_ == false)
	  this->options_->setDensityBloc(this->options_->getDensityBloc() - 5);
	break;
      }
    case OPTION_FOU:
      {
	if (input_.isKeyDown(gdl::Keys::Right) == true && this->key_ == false)
	  this->options_->setBonusDensity(this->options_->getBonusDensity() + 5);
	if (input_.isKeyDown(gdl::Keys::Left) == true && this->key_ == false)
	  this->options_->setBonusDensity(this->options_->getBonusDensity() - 5);
	break;
      }
    case MAX_OPTMAP:
      {
	if (input_.isKeyDown(gdl::Keys::Return) == true && this->key_ == false)
	  {
	    this->posMenu_.what_ = MENU_OPTGEN;
	    this->posMenu_.who_ = OPTION_ONE;
	    this->items_.update(this->posMenu_.who_);
	  }
	break;
      }
    }
}

void					MyGame::menu_optPlay_(void)
{
  switch (this->items_.update(0, this->posMenu_.what_))
    {
    case OPTION_ONE:
      {
	if (input_.isKeyDown(gdl::Keys::Right) == true && this->key_ == false)
	  this->options_->setNbPlayer(this->options_->getNbPlayer() + 1);
	if (input_.isKeyDown(gdl::Keys::Left) == true && this->key_ == false)
	  this->options_->setNbPlayer(this->options_->getNbPlayer() - 1);
	break;
      }
    case OPTION_TWO:
      {
	if (input_.isKeyDown(gdl::Keys::Right) == true && this->key_ == false)
	  this->options_->setNbIa(this->options_->getNbIa() + 1);
	if (input_.isKeyDown(gdl::Keys::Left) == true && this->key_ == false)
	  this->options_->setNbIa(this->options_->getNbIa() - 1);
	break;
      }
    case MAX_OPTPLAY:
      {
	if (input_.isKeyDown(gdl::Keys::Return) == true && this->key_ == false)
	  {
	    this->posMenu_.what_ = MENU_OPTGEN;
	    this->posMenu_.who_ = OPTION_ONE;
	    this->items_.update(this->posMenu_.who_);
	  }
	break;
      }
    }
}

void					MyGame::update_menu_(void)
{
  if (input_.isKeyDown(gdl::Keys::Up) == true && this->key_ == false)
    {
      music_->playSong("menuS");
      this->items_.update(MUP, this->posMenu_.what_);
      this->text_->setPopup(false);
    }
 if (input_.isKeyDown(gdl::Keys::Down) == true && this->key_ == false)
    {
      music_->playSong("menuS");
      this->items_.update(MDOWN, this->posMenu_.what_);
      this->text_->setPopup(false);
    }
  switch (this->posMenu_.what_)
    {
    case MENU_FIRST:
      this->menu_first_();
      break;
    case MENU_OPTGEN:
      this->menu_optGen_();
      break;
    case MENU_OPTPLAY:
      this->menu_optPlay_();
      break;
    case MENU_OPTMAP:
      this->menu_optMap_();
      break;
    case MENU_MAP:
      this->menu_map_();
      break;
    case MENU_CREDITS:
      this->menu_credits_();
      break;
    }
  this->posMenu_.who_ = this->items_.update(0, this->posMenu_.what_);

  this->key_ = input_.isKeyDown(gdl::Keys::Up) | input_.isKeyDown(gdl::Keys::Down)
    | input_.isKeyDown(gdl::Keys::Left) | input_.isKeyDown(gdl::Keys::Right)
    | input_.isKeyDown(gdl::Keys::Return) | input_.isKeyDown(gdl::Keys::Escape);

  camera_.update(gameClock_, input_);
}

void					MyGame::draw_menu_(void)
{
  this->text_->popup();
  this->items_.draw(*(this->options_), this->posMenu_.what_);
}

void					MyGame::menu_first_(void)
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->key_ == false)
    {
      switch (this->items_.update(0, this->posMenu_.what_))
	{
	case OPTION_ONE:
	  {
	    this->posMenu_.what_ = MENU_MAP;
	    this->posMenu_.who_ = OPTION_ONE;
	    this->items_.update(this->posMenu_.who_);
	    break;
	  }
	case OPTION_TWO:
	  {
	    if (this->items_.isNewGame() == false)
	      {
		this->camera_.reset_cam_game(this->options_->getXMap(), this->options_->getYMap());
		this->posMenu_.where_ = GAME;
		this->panel_.initialize(this->options_->getXMap(), -this->options_->getYMap(), 0);
	      }
	    break;
	  }
	case OPTION_THR:
	  {
	    if (load_game() == true)
	      {
		music_->playSong("gameS");
		this->camera_.reset_cam_game(this->options_->getXMap(), this->options_->getYMap());
		this->posMenu_.where_ = GAME;
		this->panel_.initialize(this->options_->getXMap(), -this->options_->getYMap(), 0);
		this->items_.setNewGame(false);
	      }
	    break;
	  }
	case OPTION_FOU:
	  {
	    this->posMenu_.what_ = MENU_OPTGEN;
	    this->posMenu_.who_ = OPTION_ONE;
	    this->items_.update(this->posMenu_.who_);
	    break;
	  }
	case MAX_MENU:
	  {
	    save_game();
	    this->window_.close();
	    break;
	  }
	}
    }
}
