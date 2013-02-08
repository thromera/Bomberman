#include <iostream>
#include <fstream>
#include <iterator>
#include "all.hpp"
#include "Menu.hpp"
#include "Caracteristique.hpp"
#include "CoreMap.hpp"
#include "Option.hpp"
#include "MyGame.hpp"
#include "Save.hpp"

Save::Save(const std::string & filename)
{
  this->file.open(filename.c_str(), std::ios::out);
}

Save::~Save()
{
  if (this->file.is_open())
    this->file.close();
}

bool			Save::isFileOpen() const
{
  if (this->file.is_open())
    return (true);
  else
    return (false);
}

void			Save::caracteristique_player(const Caracteristique *carac)
{
  this->file << "<caract>\n\t\t";
  this->file << "<life>" << carac->getLife() << "</life>\n\t\t";
  this->file << "<speed>" << carac->getSpeed() << "</speed>\n\t\t";
  this->file << "<maxBomb>" << carac->getMaxBomb() << "</maxBomb>\n\t\t";
  this->file << "<actualBomb>" << carac->getActualBomb() << "</actualBomb>\n\t";
  this->file << "</caract>\n";
}

void			Save::players(std::list<APlayer*> players)
{
  gdl::Color		color;
  std::list<APlayer*>::iterator	it;

  for (it = players.begin(); it != players.end(); ++it)
    {
      this->file << "<player>\n\t";
      this->file << "<id>" << (*it)->getId() << "</id>\n\t";
      color = ((*it)->getModel()).get_default_model_color();
      this->file << "<colorR>" << static_cast<int>(color.r) << "</colorR>\n\t";
      this->file << "<colorG>" << static_cast<int>(color.g) << "</colorG>\n\t";
      this->file << "<colorB>" << static_cast<int>(color.b) << "</colorB>\n\t";
      this->file << "<colorA>" << static_cast<int>(color.a) << "</colorA>\n\t";
      this->file << "<pos>" << (*it)->getX() << ";" << (*it)->getY() << "</pos>\n\t";
      this->file << "<direction>" << (*it)->getDirection() << "</direction>\n\t";
      this->file << "<ia>" << (*it)->isIA() << "</ia>\n\t";
      caracteristique_player(&((*it)->getCaracteristique()));
      this->file << "</player>\n";
    }
}

void			Save::bombs(std::list<Bomb*> bombs)
{
  std::list<Bomb*>::iterator	it;

  for (it = bombs.begin(); it != bombs.end(); ++it)
    {
      this->file << "<bomb>\n\t";
      this->file << "<idPlayer>" << (*it)->getIdPlayer() << "</idPlayer>\n\t";
      this->file << "<pos>" << (*it)->getX() << ";" << (*it)->getY() << "</pos>\n\t";
      this->file << "<timer>" << (*it)->getTimer() << "</timer>\n\t";
      this->file << "<delay>" << (*it)->getDelay() << "</delay>\n\t";
      this->file << "<range>" << (*it)->getRange() << "</range>\n";
      this->file << "</bomb>\n";
    }
}

void			Save::option(const Option* option, gdl::GameClock *gameclock, const float & gameTime, const bool & gameRunning)
{
  this->file << "<option>\n\t";
  this->file << "<run>" << gameRunning << "</run>\n\t";
  this->file << "<gameclock>" << gameclock->getTotalGameTime() << "</gameclock>\n\t";
  this->file << "<xmap>" << option->getXMap() << "</xmap>\n\t";
  this->file << "<ymap>" << option->getYMap() << "</ymap>\n\t";
  this->file << "<density>" << option->getDensityBloc() << "</density>\n\t";
  this->file << "<bonus>" << option->getBonusDensity() << "</bonus>\n\t";
  this->file << "<nbPlayer>" << option->getNbPlayer() << "</nbPlayer>\n\t";
  this->file << "<nbIA>" << option->getNbIa() << "</nbIA>\n";
  this->file << "</option>\n";
}

void			Save::map(CoreMap *map)
{
  this->file << "<map>\n\t";
  this->file << "<xmax>" << map->getXMax() << "</xmax>\n\t";
  this->file << "<ymax>" << map->getYMax() << "</ymax>\n";
  for (int i = 0; i < map->getYMax(); ++i)
    {
      this->file << "\t<line>";
      for (int j = 0; j < map->getYMax(); ++j)
	{
	  this->file << map->getAt(j, i);
	  if (j + 1 < map->getYMax())
	    this->file << ";";
	}
      this->file << "</line>\n";
    }

  this->file << "</map>\n";
}

void      Save::camera(const Camera & camera)
{
  this->file << "<camera>\n\t";
  this->file << "<posX>" << camera.getPos().getX() << "</posX>\n\t";
  this->file << "<posY>" << camera.getPos().getY() << "</posY>\n\t";
  this->file << "<posZ>" << camera.getPos().getZ() << "</posZ>\n\t";
  this->file << "<posnX>" << camera.getPosn().getX() << "</posnX>\n\t";
  this->file << "<posnY>" << camera.getPosn().getY() << "</posnY>\n\t";
  this->file << "<posnZ>" << camera.getPosn().getZ() << "</posnZ>\n\t";
  this->file << "<rotX>" << camera.getRot().getX() << "</rotX>\n\t";
  this->file << "<rotY>" << camera.getRot().getY() << "</rotY>\n\t";
  this->file << "<rotZ>" << camera.getRot().getZ() << "</rotZ>\n";
  this->file << "</camera>\n";
}

void			MyGame::save_game(void)
{
  Save			save("save.xml");

  if (this->_core != NULL)
    {
      this->_core->setTime(this->getCore().getGameClock()->getTotalGameTime() - this->_core->getTime());
      if (save.isFileOpen() && this->_core->getPlayer().size() > 0)
	{
	  save.option(this->options_, this->getCore().getGameClock(), this->_core->getTime(), this->gameRunning_);
	  save.players(this->_core->getPlayer());
	  save.bombs(this->_core->getBomb());
	  save.map(this->_core->getMap());
	  save.camera(this->camera_);
	}
    }
}
