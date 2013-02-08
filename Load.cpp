#include <list>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "all.hpp"
#include "Menu.hpp"
#include "Bomb.hpp"
#include "Caracteristique.hpp"
#include "Option.hpp"
#include "CoreMap.hpp"
#include "MyGame.hpp"
#include "Load.hpp"

Load::Load(const std::string & filename)
{
  this->file.open(filename.c_str(), std::ios::in);
  this->gameclock = 0;
}

Load::~Load()
{
  if (this->file.is_open())
    this->file.close();
}

template<typename T>
T			Load::convertNumber(T & type, const std::string & str)
{
  std::istringstream	ss(str);

  ss >> type;

  return (type);
}

bool			Load::isFileOpen(void) const
{
  if (this->file.is_open())
    return (true);

  return (false);
}

std::string*		Load::getValue(const std::string & buf, const std::string & id)
{
  int			start;
  int			end;

  if ((start = buf.find("<" + id + ">")) != std::string::npos)
    {
      end = buf.find("</" + id + ">");
      std::string *str = new std::string(buf, (start + 2 + id.length()), end - (start + 2 + id.length()));
      return (str);
    }

  return (NULL);
}

std::vector<Ibloc>	Load::splitLine(const std::string & strValue, const char & separator)
{
  std::vector<Ibloc>	vecstrResult;
  unsigned int		tmp;
  int			startpos = 0;
  int			endpos = 0;

  endpos = strValue.find_first_of(separator, startpos);
  while (endpos != -1)
    {
      vecstrResult.push_back(static_cast<Ibloc>(convertNumber(tmp, strValue.substr(startpos, endpos-startpos))));
      startpos = endpos+1;
      endpos = strValue.find_first_of(separator, startpos);
      if(endpos == -1)
	vecstrResult.push_back(static_cast<Ibloc>(convertNumber(tmp, strValue.substr(startpos))));
    }

  return vecstrResult;
}

CoreMap*		Load::map(void)
{
  std::vector<std::vector<Ibloc> >	map;
  std::string		*res = NULL;
  std::string		buf;
  unsigned int		xmax = 0;
  unsigned int		ymax = 0;

  getline(this->file, buf);
  while (buf.find("</map>") == std::string::npos)
    {
      if ((res = this->getValue(buf, "xmax")) != NULL)
        convertNumber(xmax, *res);
      else if ((res = this->getValue(buf, "ymax")) != NULL)
        convertNumber(ymax, *res);
      else if ((res = this->getValue(buf, "line")) != NULL)
	map.push_back(this->splitLine(*res, ';'));
      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }
  if (xmax < 0 || ymax < 0)
    return (NULL);
  CoreMap* coremap = new CoreMap();
  coremap->setXMax(xmax);
  coremap->setYMax(ymax);
  coremap->setMap(map);

  return (coremap);
}

Position*		Load::parsePosition(const std::string & str)
{
  std::string		strX(str, 0, str.find(";"));
  std::string		strY(str, str.find(";") + 1, str.length() - str.find(";"));
  double		x = 0;
  double		y = 0;

  convertNumber(x, strX);
  convertNumber(y, strY);

  if (x < 0 || y < 0)
    return (NULL);
  Position* pos = new Position(x, y);

  return (pos);
}

APlayer*		Load::player(void)
{
  std::string		buf;
  std::string		*res = NULL;
  std::string		sid = "";
  unsigned int	       	id;
  Position		*pos = NULL;
  unsigned int		dir = 1;
  bool			ia;
  unsigned int		life;
  unsigned int		speed;
  unsigned int		actualBomb;
  unsigned int		maxBomb;
  unsigned int		range;
  std::string		col;
  unsigned int		r = 0;
  unsigned int		g = 0;
  unsigned int		b = 0;
  unsigned int		a = 255;

  getline(this->file, buf);
  while (buf.find("</player>") == std::string::npos)
    {
      if ((res = this->getValue(buf, "id")) != NULL)
        sid = *res;
      else if ((res = this->getValue(buf, "colorR")) != NULL)
        convertNumber(r, *res);
      else if ((res = this->getValue(buf, "colorG")) != NULL)
        convertNumber(g, *res);
      else if ((res = this->getValue(buf, "colorB")) != NULL)
        convertNumber(b, *res);
      else if ((res = this->getValue(buf, "colorA")) != NULL)
        convertNumber(a, *res);
      else if ((res = this->getValue(buf, "pos")) != NULL)
	pos = parsePosition(*res);
      else if ((res = this->getValue(buf, "direction")) != NULL)
        convertNumber(dir, *res);
      else if ((res = this->getValue(buf, "ia")) != NULL)
        convertNumber(ia, *res);
      else if ((res = this->getValue(buf, "life")) != NULL)
        convertNumber(life, *res);
      else if ((res = this->getValue(buf, "speed")) != NULL)
        convertNumber(speed, *res);
      else if ((res = this->getValue(buf, "maxBomb")) != NULL)
        convertNumber(maxBomb, *res);
      else if ((res = this->getValue(buf, "actualBomb")) != NULL)
        convertNumber(actualBomb, *res);
      else if ((res = this->getValue(buf, "range")) != NULL)
        convertNumber(range, *res);

      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }

  if (pos == NULL || sid == "" || pos == NULL)
    return (NULL);
  convertNumber(id, sid);
  gdl::Color color(r, g, b, a);
  Caracteristique *caracteristique = new Caracteristique(life);
  caracteristique->setSpeed(speed);
  caracteristique->setActualBomb(actualBomb);
  caracteristique->setMaxBomb(maxBomb);
  APlayer* player = new APlayer(id, pos, caracteristique, ia);
  player->initialize();
  player->changeDir(static_cast<Direction>(dir));
  player->getModel().set_default_model_color(color);

  return (player);
}

Bomb*			Load::bomb(gdl::GameClock const *currentGC)
{
  std::string		buf;
  std::string		*res = NULL;
  unsigned int		idPlayer;
  unsigned int		range;
  Position		*pos = NULL;
  float			delayMs;
  float			startTimer;

  getline(this->file, buf);
  while (buf.find("</bomb>") == std::string::npos)
    {
      if ((res = this->getValue(buf, "idPlayer")) != NULL)
        convertNumber(idPlayer, *res);
      else if ((res = this->getValue(buf, "range")) != NULL)
        convertNumber(range, *res);
      else if ((res = this->getValue(buf, "timer")) != NULL)
        convertNumber(startTimer, *res);
      else if ((res = this->getValue(buf, "delay")) != NULL)
        convertNumber(delayMs, *res);
      else if ((res = this->getValue(buf, "pos")) != NULL)
	pos = parsePosition(*res);
      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }
  Bomb* bomb = new Bomb(0, 0, idPlayer, range, currentGC->getTotalGameTime());
  bomb->setPosition(pos);
  bomb->setDelay(delayMs - (this->gameclock - startTimer));

  return (bomb);
}

Option*			Load::option(void)
{
  std::string		buf;
  std::string		*res = NULL;
  int			xMap;
  int			yMap;
  int			densityBloc;
  unsigned int		nbPlayer;
  unsigned int		nbIa;
  unsigned int		bonus;

  getline(this->file, buf);
  while (buf.find("</option>") == std::string::npos)
    {
      if ((res = this->getValue(buf, "gameclock")) != NULL)
        convertNumber(this->gameclock, *res);
      else if ((res = this->getValue(buf, "xmap")) != NULL)
        convertNumber(xMap, *res);
      else if ((res = this->getValue(buf, "ymap")) != NULL)
        convertNumber(yMap, *res);
      else if ((res = this->getValue(buf, "density")) != NULL)
        convertNumber(densityBloc, *res);
      else if ((res = this->getValue(buf, "bonus")) != NULL)
        convertNumber(bonus, *res);
      else if ((res = this->getValue(buf, "nbPlayer")) != NULL)
        convertNumber(nbPlayer, *res);
      else if ((res = this->getValue(buf, "nbIA")) != NULL)
        convertNumber(nbIa, *res);
      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }

  if (xMap < 0 || yMap < 0 || densityBloc < 0 || res == NULL)
    return (NULL);
  Option* option = new Option(xMap, yMap, densityBloc, nbPlayer, nbIa);
  option->setBonusDensity(bonus);

  return (option);
}

bool			Load::camera(Camera & camera)
{
  std::string		buf;
  std::string		*res = NULL;
  float			posx = -1;
  float			posy = -1;
  float			posz = -1;
  float			posnx = -1;
  float			posny = -1;
  float			posnz = -2;
  float			rotx = -1;
  float			roty = -1;
  float			rotz = -1;

  getline(this->file, buf);
  while (buf.find("</camera>") == std::string::npos)
    {
      if ((res = this->getValue(buf, "posX")) != NULL)
        convertNumber(posx, *res);
      else if ((res = this->getValue(buf, "posY")) != NULL)
        convertNumber(posy, *res);
      else if ((res = this->getValue(buf, "posZ")) != NULL)
        convertNumber(posz, *res);
      else if ((res = this->getValue(buf, "posnX")) != NULL)
        convertNumber(posnx, *res);
      else if ((res = this->getValue(buf, "posnY")) != NULL)
        convertNumber(posny, *res);
      else if ((res = this->getValue(buf, "posnZ")) != NULL)
        convertNumber(posnz, *res);
      else if ((res = this->getValue(buf, "rotX")) != NULL)
        convertNumber(rotx, *res);
      else if ((res = this->getValue(buf, "rotY")) != NULL)
        convertNumber(roty, *res);
      else if ((res = this->getValue(buf, "rotZ")) != NULL)
        convertNumber(rotz, *res);
      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }

  if (posx == -1 || posy == -1 || posz == -1 ||
      posnx == -1 || posny == -1 || posnz == -2 ||
      rotx == -1 || roty == -1 || rotz == -1)
    return (false);

  Pos3f pos(posx, posy, posz);
  Pos3f posn(posnx, posny, posnz);
  Pos3f rot(rotx, roty, rotz);

  camera.setPos(pos);
  camera.setPosn(posn);
  camera.setRot(rot);

  return (true);
}

bool			Load::parse(Core* & core, Option* & option, Camera & camera)
{
  std::string		buf;
  CoreMap*		map = NULL;
  Option*		opt = NULL;
  std::list<APlayer*>	players;
  std::list<Bomb*>	bombs;

  while (this->file.good())
    {
      getline(this->file, buf);
      if (buf.find("<map>") != std::string::npos)
	if ((map = this->map()) == NULL)
	  return (false);
      if (buf.find("<camera>") != std::string::npos)
	if (this->camera(camera) == false)
	  return (false);
      if (buf.find("<player>") != std::string::npos)
	{
	  players.push_back(this->player());
	  if (players.back() == NULL)
	    {
	      while (!core->getPlayer().empty())
		{
		  delete core->getPlayer().front();
		  core->getPlayer().pop_front();
		}
	      return (false);
	    }
	}
      if (buf.find("<option>") != std::string::npos)
	if ((opt = this->option()) == NULL)
	  return (false);
      if (buf.find("<bomb>") != std::string::npos)
	bombs.push_back(this->bomb(core->getGameClock()));
    }

  if (opt != NULL)
    option = opt;
  else
    return (false);
  if (map != NULL)
    {
      if (core->getMap() != NULL)
        delete core->getMap();
      core->setMap(map);
    }
  else
    return (false);
  while (!core->getBomb().empty())
    {
      delete core->getBomb().front();
      core->getBomb().pop_front();
    }
  if (!bombs.empty())
    core->setBombs(bombs);
  while (!core->getPlayer().empty())
    {
      delete core->getPlayer().front();
      core->getPlayer().pop_front();
    }
  if (players.empty())
    return (false);
  else
    core->setPlayers(players);
  return (true);
}

bool			MyGame::load_game(void)
{
  Load			load("save.xml");

  if (this->gameRunning_ == false)
    return (false);
  if (load.isFileOpen())
    {
      if (this->_core != NULL)
	delete this->_core;
      this->_core = new Core(&gameClock_);
      this->_core->setMusic(this->music_);
      if (load.parse(this->_core, this->options_, this->camera_) == false)
	return (false);
      this->_core->getMap()->setObjects(this->_obj);
      this->panel_.initialize(this->options_->getXMap(), this->options_->getYMap(), 0);
    }
  else
    return (false);

  return (true);
}
