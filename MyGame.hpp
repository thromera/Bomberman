///////////////////////////////////////////////////////////////////////////////
/// Declaration de la classe MyGame
////////////////////////////////////////////////////////////////////////////////

#ifndef __MYGAME_HPP__
#define __MYGAME_HPP__


#include <cstdlib>
#include <list>
#include <vector>
#include <iostream>

#include "all.hpp"
#include "Objects.hpp"
#include "Camera.hpp"
#include "AObject.hpp"
#include "Menu.hpp"
#include "ObjMenu/ObjMenu.hpp"
#include "ObjMap/ObjMap.hpp"
#include "ObjIntro/Intro.hpp"
#include "ObjIntro/Model.hpp"
#include "Music.hpp"
#include "BonusMap/BonusMap.hpp"
#include "Core.hpp"
#include "EndGame.hpp"

#define MENU	0
#define GAME	1
#define INTRO   2
#define LOAD	3
#define LOADB	4

class Bomb;
class Core;

class MyGame : public gdl::Game
{
private:
  unsigned int				_lastId;
  bool					key_;
  bool					gameRunning_;
  Core					* _core;
  Intro					*intro_;
  Music					*music_;
  Option				* options_;
  EndGame				*endGame_;
  TextMap				*text_;
  Camera				camera_;
  Menu					posMenu_;
  Objects				* _obj;
  std::list<AObject*>			objects_;
  ObjMenu::Accueil			items_;
  ObjMap::Panel				panel_;
  BonusMap::FireUp			fu_;
  BonusMap::BombUp			bu_;
  BonusMap::SpeedUp			su_;

  void					reset_menu_(void);

  void					initialize_menu_(void);
  void					initialize_game_(void);
  void					initialize_intro_(void);

  void					menu_first_(void);
  void					menu_map_(void);
  void					menu_optGen_(void);
  void					menu_credits_(void);
  void					menu_optMap_(void);
  void					menu_optPlay_(void);
  void					update_menu_(void);
  void					update_game_(void);
  void					update_intro_(gdl::GameClock const &, gdl::Input &);

  void					draw_menu_(void);
  void					draw_game_(void);
  void					draw_intro_(void);
  void					toIa(APlayer*, MyGame*, gdl::Input&);
  void					checkBonus(APlayer* player);
  void					player_one_(gdl::Input &);
  void					player_two_(gdl::Input &);
  void					select_map(unsigned int map);
  EndGame*				getEndGame() const;
  bool					isEndGame(void) const;

  void					save_game(void);
  bool					load_game(void);
  void					setLightBonus();

public:
  void					new_game(void);
  void					initialize_all_();
  Core&					getCore(void) const;
  void					initialize(void);
  void					update(void);
  void					draw(void);
  unsigned int				getLastId(void);
  void					unload(void);
  void					launchPlayer(void);
  unsigned int				canMove(const APlayer*, Direction);
  unsigned int				canMove(const double xp, const double yp, Direction dir, double speed);

};

#endif
