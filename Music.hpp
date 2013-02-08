//
// Music.hpp for music in /home/emirot_n//rendu/bomberman-2015-romera_t/projet
// 
// Made by nolan emirot
// Login   <emirot_n@epitech.net>
// 
// Started on  Fri May 25 14:01:33 2012 nolan emirot
// Last update Sun Jun  3 22:58:58 2012 nolan emirot
//



#ifndef __MUSIC_H__
#define __MUSIC_H__
#include <SFML/Audio.hpp>

#include <string>
#include <iostream>


class Music
{
  
public:
  Music();
  ~Music();
  void   playSong(const char *s);
  void stopSong();
  void  introS();
  void  menuS();
  void bombS();
  void  powerUp();
  void  gameS();
  void  endS();

private:
  sf::Sound *Soundintro_;
  sf::SoundBuffer *Bufferintro_;
  sf::Music *Soundbomb_;
  sf::Music *Soundmenu_;
  sf::Music *Soundpower_;
  sf::Sound  *Soundgame_;
  sf::SoundBuffer *Buffergame_;

  sf::Sound  *Soundend_;
  sf::SoundBuffer *Bufferend_;
};

typedef struct sM
{
  const char *a;
  void (Music::*f)();
}tM;


#endif
