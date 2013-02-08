//
/// Music.cpp for music in /home/emirot_n//rendu/bomberman-2015-romera_t/projet
// 
// Made by nolan emirot
// Login   <emirot_n@epitech.net>
// 
// Started on  Fri May 25 14:01:25 2012 nolan emirot
// Last update Sun Jun  3 23:01:23 2012 nolan emirot
//

#include "all.hpp"
#include <SFML/Audio.hpp>
#include "Music.hpp"


Music::Music()
{

  Bufferintro_= new sf::SoundBuffer;
  Soundintro_=new sf::Sound();

  Bufferend_= new sf::SoundBuffer;
  Soundend_=new sf::Sound();

  Soundmenu_=new sf::Music;
  Soundbomb_=new sf::Music;
  Soundpower_ = new sf::Music;
  
  Soundgame_=new sf::Sound;
  Buffergame_= new sf::SoundBuffer;

  Bufferintro_->LoadFromFile("Sounds/bomberman_orchestra.wav");
  Soundbomb_->OpenFromFile("Sounds/bomb.ogg");
  Soundmenu_->OpenFromFile("Sounds/click.ogg");
  Soundpower_->OpenFromFile("Sounds/power_up.ogg");
  Buffergame_->LoadFromFile("Sounds/Super_Bomberman.wav");
  Bufferend_->LoadFromFile("Sounds/soundEnd.wav");
}


Music::~Music()
{
  delete Soundintro_;
  delete Soundmenu_;
  delete Soundpower_;
  delete Soundbomb_;
  delete Soundgame_;
  delete Buffergame_;
}


void Music::introS()
{
  this->Soundintro_->SetBuffer(*this->Bufferintro_);
  this->Soundintro_->Play();
}

void Music::bombS()
{
  Soundbomb_->Play();
}

void Music::menuS()
{
      Soundmenu_->Play(); 
}

void Music::powerUp()
{
      Soundpower_->Play();
      Soundpower_->SetVolume(10.f);

}

void Music::gameS()
{
      Soundgame_->SetBuffer(*Buffergame_);
      Soundgame_->Play();
      Soundgame_->SetVolume(10.f);
}


void Music::endS()
{
  Soundend_->SetBuffer(*Bufferend_);
  Soundend_->Play();
}


tM  tab1[]=
  {
    {"introS",&Music::introS},
    {"bombS",&Music::bombS},
    {"menuS",&Music::menuS},
    {"powerUp",&Music::powerUp},
    {"gameS",&Music::gameS},
    {"endS",&Music::endS},
    {0,0},
  };


void Music::playSong(const char *s)
{
  int i=0;
  std::string so;
  so =s;
  while(tab1[i].a)
    {
      if(tab1[i].a == so)
	{
	  (this->*tab1[i].f)();
	}
      i++;
    }
}


void Music::stopSong()
{
  Soundintro_->Stop();
  Soundmenu_->Stop();
  Soundbomb_->Stop();
  Soundpower_->Stop();
  Soundgame_->Stop();
  Soundend_->Stop();
}
