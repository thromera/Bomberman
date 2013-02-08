#ifndef __ENDGAME_H__
#define __ENDGAME_H__

#include <list>
#include <SFML/Audio.hpp>
#include "APlayer.hpp"
#include "all.hpp"                                                                   
#include "AObject.hpp"                                                              
#include "Pos3f.hpp"
#include "TextMap.hpp"   
#include "Model.hpp"
#include "Camera.hpp"
#include "Music.hpp"


#define BACKGROUND 220

enum WhoWin
  {
    P1,
    P2,
    IA,
  };

class EndGame// : public AObject
{
public:
  EndGame(void);
  ~EndGame(void);
  void endMusic();
  void startMusic();
  void initialize(void);
  void initialize(float, float, float);
  void update( );
  void draw(enum WhoWin who);
  void music();

private:
  //  Model::Bomberman model_;
  Pos3f	pos_;
  Camera camera_;
  bool mu;
  gdl::Image  textureP1w_;
  gdl::Image  textureP2w_;
  gdl::Image textureIaa_;
  TextMap	text_;
  sf::Sound	Sound_;
  sf::SoundBuffer Buffer_;
  Music *music_;
  void initialize_(void);
  std::list<APlayer*> _pl;
};

#endif
