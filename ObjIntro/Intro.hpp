#ifndef __INTRO_H__
#define __INTRO_H__

#include "../all.hpp"                                                                   
#include "../AObject.hpp"                                                              
#include "../Pos3f.hpp"
#include "../TextMap.hpp"   
#include "Model.hpp"
#include <SFML/Audio.hpp>
#include "../Music.hpp"

#define BACK 920

class Intro
{

public:
  Intro(void);
  ~Intro(void);
  void initialize(void);
  void initialize(float const &, float const &, float const &);
  int update(gdl::GameClock const &, gdl::Input &);
  void draw(void);
  void music();

private:
  Model::Bomberman model_;
  Pos3f	pos_;
  gdl::Image  texture_;
  gdl::Image  texture2_;
  TextMap	text_;
  sf::Sound	Sound_;
  sf::SoundBuffer Buffer_;
  Music *music_;
  void initialize_(void);
};

#endif
