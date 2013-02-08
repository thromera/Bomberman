#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include "APlayer.hpp"
#include "all.hpp"
#include "Menu.hpp"
#include "MyGame.hpp"
#include "ObjMap/ObjMap.hpp"
#include "ObjMenu/ObjMenu.hpp"
#include "CoreMap.hpp"
#include "Bomb.hpp"

void					MyGame::new_game(void)
{
  this->_core = new Core(&gameClock_);
  this->_core->getMap()->setObjects(this->_obj);
  this->_core->setMusic(this->music_);
  this->getCore().genPlayers(*(this->options_));
  this->getCore().getMap()->genMap(*(this->options_));
  this->getCore().getMap()->adjustMapWithPlayers(this->getCore().getPlayer());
  this->panel_.initialize(this->options_->getXMap(), -this->options_->getYMap(), 0);
  this->_core->setTime(0);
}

void					MyGame::initialize_game_(void)
{
  music_ = new Music();
  this->panel_.initialize();
  this->options_ = new Option(10, 10, 50, 1, 1);
  this->_obj = new Objects;
}

void					MyGame::initialize(void)
{
  window_.setTitle("Bomberman");
  window_.setWidth(LARGEUR_ECRAN);
  window_.setHeight(HAUTEUR_ECRAN);
  window_.create();
  camera_.initialize();
  this->posMenu_.where_ = LOADB;
}

void					MyGame::initialize_all_(void)
{
  this->initialize_menu_();
  this->initialize_game_();
  this->initialize_intro_();
  this->key_ = false;
  this->_core = NULL;
  this->new_game();
  this->endGame_ = new EndGame();
  this->endGame_->initialize();
  this->posMenu_.where_ = INTRO;
  this->gameRunning_ = true;
}


void					MyGame::toIa(APlayer *p, MyGame *mygame, gdl::Input &input_)
{
  Ia					*bob = new Ia(mygame, p);

  bob->fillVecPoids(input_, gameClock_);
  delete bob;
}

void					MyGame::update_game_(void)
{
  APlayer				*pl;
  std::list<APlayer*>::iterator		 it;

  if (input_.isKeyDown(gdl::Keys::Z) == true && this->key_ == false)
    {
      music_->stopSong();
      this->endGame_->endMusic();
      save_game();
      this->reset_menu_();
    }
  if (gameRunning_ == true)
    {
      std::list<APlayer*> plist = this->getCore().getPlayer();
      for (it = plist.begin(); it != plist.end(); it++)
	{
	  if ((*it)->getCaracteristique().getLife() > 0 && (*it)->isIA() == true)
	    {
	      this->toIa(*it, this, input_);
	      this->checkBonus(*it);
	    }
	}
      if ((pl = this->getCore().getPlayerById(0)) != NULL && pl->isIA() == false && pl->getCaracteristique().getLife() > 0)
	player_one_(input_);
      if ((pl = this->getCore().getPlayerById(1)) != NULL && pl->isIA() == false&& pl->getCaracteristique().getLife() > 0)
	player_two_(input_);
      this->getCore().checkBomb();
    }
  this->key_ = input_.isKeyDown(gdl::Keys::Z);
  panel_.update(gameClock_, input_);
}

void				MyGame::update(void)
{
  switch (this->posMenu_.where_)
    {
    case MENU:
      this->update_menu_();
      break;
    case INTRO:
      this->update_intro_(gameClock_, input_);
      break;
    case GAME:
      this->update_game_();
      break;
    case LOAD:
      this->initialize_all_();
      break;
    }
  if (input_.isKeyDown(gdl::Keys::Escape) == true)
    {
      save_game();
      this->window_.close();
    }
  usleep(19000);
  this->camera_.update(gameClock_, input_);
}

bool					MyGame::isEndGame() const
{
  std::list<APlayer*>::iterator it;
  std::list<APlayer*>		_pl;
  unsigned int			nb_alive = 0;
  unsigned int			id = 2;
  unsigned int			nb_ia = 0;
  unsigned int			nb_pl = 0;

  _pl = this->getCore().getPlayer();
  for (it = _pl.begin(); it != _pl.end(); it++)
    {
      if ((*it)->getCaracteristique().getLife() > 0)
	{
	  nb_alive++;
	  (*it)->isIA() == true ? (id = 2) : (id = (*it)->getId());
	  (*it)->isIA() == true ? (nb_ia++) : (nb_pl++);
	}
      if (nb_alive > 1 && nb_pl != 0)
	return(true);
    }
  this->getEndGame()->draw((WhoWin)id);
  return(false);
}

void					MyGame::draw_game_(void)
{
  std::list<Bomb*>		bomb;
  std::list<APlayer*>		pl;
  std::list<Bomb*>::iterator	itb;
  std::list<APlayer*>::iterator itp;

  pl = this->getCore().getPlayer();
  this->getCore().getMap()->draw();
  for (itp = pl.begin(); itp != pl.end(); itp++)
    if ((*itp)->getCaracteristique().getLife() > 0)
      (*itp)->draw(this->getCore().getMap());
  bomb = this->getCore().getBomb();
  for (itb = bomb.begin(); itb != bomb.end(); itb++)
    (*itb)->draw(this->getCore().getMap(), gameClock_.getTotalGameTime());
  panel_.draw((this->getCore().getPlayerById(0)->getCaracteristique()), 0);
  if (this->options_->getNbPlayer() == 2)
    panel_.draw((this->getCore().getPlayerById(1)->getCaracteristique()), 1);
  gameRunning_ = isEndGame();
}

void					MyGame::draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.74f, 0.84f, 95.0f, 1.0f);
  glClearDepth(1.0f);

  switch (this->posMenu_.where_)
    {
    case MENU:
      music_->stopSong();
      this->draw_menu_();
      break;
    case INTRO :
      this->draw_intro_();
      break;
    case GAME :
      this->draw_game_();
      break;
    default:
      this->posMenu_.where_ = LOAD;
      break;
    }
  this->window_.display();
}

void					MyGame::unload(void)
{
  music_->stopSong();
  delete _core;
  delete _obj;
  delete endGame_;
  delete text_;
  delete intro_;
  delete music_;
  delete options_;
}

unsigned int				MyGame::getLastId(void)
{
  return this->_lastId;
}

Core&					MyGame::getCore(void) const
{
  return *_core;
}

unsigned int				MyGame::canMove(const APlayer* player, Direction dir)
{
  unsigned int				ret;

  double				x = player->getX();
  double				y = player->getY();

  switch (dir)
    {
    case RIGHT :
      x = player->getX() + 0.2 + SCALE_SPEED * player->getCaracteristique().getSpeed();
      break;
    case LEFT :
      x = player->getX() - 0.2 - SCALE_SPEED * player->getCaracteristique().getSpeed();
      break;
    case UP :
      y = player->getY() - 0.2 - SCALE_SPEED * player->getCaracteristique().getSpeed();
      break;
    case DOWN :
      y = player->getY() + 0.2 + SCALE_SPEED * player->getCaracteristique().getSpeed();
      break;
    }
  if ((int)player->getX() == (int)x && (int)player->getY() == (int)y)
    ret = VOID;
  else
    {
      ret = this->getCore().getMap()->getAt(x, y);
      ret = this->getCore().isBomb(x, y, ret);
    }
  return ret;
}

unsigned int				MyGame::canMove(const double xp, const double yp, Direction dir, double speed)
{
  unsigned int				ret;
  double				x;
  double				y;

  switch (dir)
    {
    case RIGHT :
      x = xp + 0.2 + SCALE_SPEED * speed;
      break;
    case LEFT :
      x = xp - 0.2 - SCALE_SPEED * speed;
      break;
    case UP :
      y = yp - 0.2 - SCALE_SPEED * speed;
      break;
    case DOWN :
      y = yp + 0.2 + SCALE_SPEED * speed;
      break;
    }
  if ((int)xp == (int)x && (int)yp == (int)y)
    ret = VOID;
  else
    {
      ret = this->getCore().getMap()->getAt(x, y);
      ret = this->getCore().isBomb(x, y, ret);
    }
  return ret;
}

void					MyGame::setLightBonus()
{
  std::list<Bomb*>			bm;
  std::list<Bomb*>::iterator		itb;

  this->getCore().getBomb().clear();
  bm = this->getCore().getBomb();
  for (itb = bm.begin(); itb != bm.end(); itb++)
    {
      (*itb)->setTimer(getCore().getGameClock()->getTotalGameTime() - 2.7f);
      (*itb)->draw_explode_(this->getCore().getMap());
    }    
}

void					MyGame::checkBonus(APlayer* player)
{
  unsigned int				bloc;
  
  bloc = this->getCore().getMap()->getAt(player->getX(), player->getY());
  if (bloc > VOID)
    {
      music_->playSong("powerUp");
      player->addBonus(bloc);
      if (bloc == LIGHT)
	this->setLightBonus();
      this->getCore().getMap()->setAt((int)player->getX(), (int)player->getY(), VOID);
    }
}

EndGame*				MyGame::getEndGame(void) const
{
  return this->endGame_;
}

void					MyGame::player_two_(gdl::Input & input_)
{
  APlayer				*pl;

  pl = this->getCore().getPlayerById(1);
  if (input_.isKeyDown(gdl::Keys::Numpad6) == true)
    {
      pl->changeDir(RIGHT);
      if (this->canMove(pl, RIGHT) >= VOID)
	pl->update(*(this->getCore().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::Numpad4) == true )
    {
      pl->changeDir(LEFT);
      if (this->canMove(pl, LEFT) >= VOID)
	pl->update(*(this->getCore().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::Numpad5) == true)
    {
      pl->changeDir(DOWN);
      if (this->canMove(pl, DOWN) >= VOID)
	pl->update(*(this->getCore().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::Numpad8) == true)
    {
      pl->changeDir(UP);
      if (this->canMove(pl, UP) >= VOID)
	pl->update(*(this->getCore().getGameClock()), input_);
    }
  this->checkBonus(pl);
  if (input_.isKeyDown(gdl::Keys::Numpad0) == true)
    {
      if (pl->getCaracteristique().getActualBomb() < pl->getCaracteristique().getMaxBomb()
	  && this->getCore().hasBombOnPos((unsigned int)pl->getX(), (unsigned int)pl->getY()) == false)
	{
	  this->getCore().addBomb(new Bomb(pl, gameClock_.getTotalGameTime()));
	  pl->getCaracteristique().putBomb();
	}
    }
}

void					MyGame::player_one_(gdl::Input & input_)
{

  APlayer				*pl;

  pl = this->getCore().getPlayerById(0);
  if (input_.isKeyDown(gdl::Keys::D) == true)
    {
      pl->changeDir(RIGHT);
      if (this->canMove(pl, RIGHT) >= VOID)
	pl->update(*(this->getCore().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::A) == true )
    {
      pl->changeDir(LEFT);
      if (this->canMove(pl, LEFT) >= VOID)
	pl->update(*(this->getCore().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::S) == true)
    {
      pl->changeDir(DOWN);
      if (this->canMove(pl, DOWN) >= VOID)
	pl->update(*(this->getCore().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::W) == true)
    {
      pl->changeDir(UP);
      if (this->canMove(pl, UP) >= VOID)
	pl->update(*(this->getCore().getGameClock()), input_);
    }
  this->checkBonus(pl);
  if (input_.isKeyDown(gdl::Keys::Space) == true)
    {
      if (pl->getCaracteristique().getActualBomb() < pl->getCaracteristique().getMaxBomb()
	  && this->getCore().hasBombOnPos((unsigned int)pl->getX(), (unsigned int)pl->getY()) == false)
	{
	  this->getCore().addBomb(new Bomb(pl, gameClock_.getTotalGameTime()));
	  pl->getCaracteristique().putBomb();
	}
    }
}
