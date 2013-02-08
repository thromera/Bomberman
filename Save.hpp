#ifndef __SAVE_HPP__
#define __SAVE_HPP__

#include <iostream>
#include <fstream>
#include "Core.hpp"
#include "Option.hpp"
#include "MyGame.hpp"

class		Save
{
public:
  Save(const std::string & filename);
  ~Save();
private:
  std::ofstream	file;
public:
  bool		isFileOpen(void) const;
  void		players(std::list<APlayer*> players);
  void		caracteristique_player(const Caracteristique *carac);
  void		bombs(std::list<Bomb*> bombs);
  void    	option(const Option* option, gdl::GameClock *gameclock, const float & gameTime, const bool & gameRunning);
  void		map(CoreMap *map);
  void		camera(const Camera & camera);
};

#endif
