#ifndef __CORE_HPP__
#define __CORE_HPP__

#include <iostream>
#include <list>
#include <vector>

#include "APlayer.hpp"
#include "Ia.hpp"
#include "CoreMap.hpp"
#include "Option.hpp"
#include "CoreMap.hpp"
#include "Bomb.hpp"
#include "GameClock.hpp"

class Bomb;

class			Core
{
public:
  Core(gdl::GameClock*);
  ~Core();

private:
  CoreMap		                *_map;
  Music					* _musicBomb;
  gdl::GameClock			*gameClock_;
  std::list<APlayer*>			_players;
  std::list<Bomb*>			_bombs;

  bool					_firstMusicBomb;
  float					_timeInGame;
  
public:
  void					setMusic(Music *);
  void					checkBomb(void);
  void					genPlayers(const Option & opt);
  void					genIa(const Option & opt);
  Position				*genPositionPlayers(const Option& opt);
  APlayer*				getPlayerById(const unsigned int& id) const;
  CoreMap*				getMap() const;
  void					setMap(CoreMap* map);
  void					setPlayers(std::list<APlayer*> players);
  void					setBombs(std::list<Bomb*> bombs);
  std::list<APlayer*>			getPlayer() const;
  std::list<Bomb*>			getBomb() const;
  unsigned int				getXMax() const;
  unsigned int				getYMax() const;
  void					isPlayer(unsigned int x, unsigned int y);
  void					addBomb(Bomb* newBomb);
  gdl::GameClock		        *getGameClock() const;
  bool					hasBombOnPos(const unsigned int & x, const unsigned int & y);

  float					getTime(void) const;
  void					setTime(const float & time);

  unsigned int				isBomb(const unsigned int& x, const unsigned int& y, const unsigned int& prevRet);
};


#endif

