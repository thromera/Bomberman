//
// Ia.hpp for Ia in /home/emirot_n//rendu/bomberman-2015-romera_t/projet
// 
// Made by nolan emirot
// Login   <emirot_n@epitech.net>
// 
// Started on  Tue May 29 14:57:47 2012 nolan emirot
// Last update Sun Jun  3 19:45:45 2012 eric audran
//

#ifndef __IA_HPP__
#define __IA_HPP__

#include <vector>

class MyGame;

class Ia
{
public:
  Ia( MyGame *realMyGame,APlayer *);
  ~Ia();
  void  fillVecPoids(gdl::Input&, gdl::GameClock&);

  bool isNextZoneSafe(int x, int y);
  bool proxDesAndVoid(int x, int y);

  int safeZone();
  int toBonnus();
  int toPutBomb();

  void putBomb(gdl::Input&, gdl::GameClock&);
  void	outOfBomb(gdl::Input&, gdl::GameClock&);
  void toBonnus(gdl::Input&, gdl::GameClock&);

  void	turnRand(gdl::Input&, gdl::GameClock&);
  Direction  recSaferDir(unsigned int x, unsigned int y, Direction dir, unsigned int size);
  Direction    getSaferDir();
private:
  APlayer			*_ia;
  std::vector<int>		_poids;
  MyGame			*_myGameTmp;
  int				_indexBomb;
  Direction			_dirBonnus;
};

#endif
