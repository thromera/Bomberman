#ifndef __LOAD_HPP__
#define __LOAD_HPP__

#include <iostream>
#include <fstream>
#include "Core.hpp"
#include "Position.hpp"
#include "Option.hpp"
#include "MyGame.hpp"

class		Load
{
public:
  Load(const std::string & filename);
  ~Load();
private:
  std::ifstream		file;
  float			gameclock;
  float			gametime;
public:
  bool			isFileOpen(void) const;
  bool			parse(Core* & core, Option* & option, Camera & camera);
private:
  // Conversion des strings en nombre
  template<typename T>
  T			convertNumber(T & type, const std::string & str);
  // Fonctions de parsage du fichier XML
  std::string*		getValue(const std::string & buf, const std::string & id);
  std::vector<Ibloc>	splitLine(const std::string & strValue, const char & separator);
  Position*		parsePosition(const std::string & str);
  // Fonctions parsant les tagname
  CoreMap*		map(void);
  APlayer*		player(void);
  Option*		option(void);
  Bomb*			bomb(gdl::GameClock const *currentGC);
  bool			camera(Camera & camera);
};

#endif
