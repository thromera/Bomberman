#include "Core.hpp"

Core::Core(gdl::GameClock *clock)
{
  this->_firstMusicBomb = false;
  this->_map = new CoreMap();
  this->gameClock_ = clock;
  this->_timeInGame = 0;
}

Core::~Core()
{
  delete(_map);
  while (!this->_players.empty())
    {
      delete this->_players.front();
      this->_players.pop_front();
    }
  while (!this->_bombs.empty())
    {
      delete this->_bombs.front();
      this->_bombs.pop_front();
    }
}

void					Core::setMusic(Music * mus)
{
  this->_musicBomb = mus;
}

void					Core::checkBomb()
{
  std::list<Bomb*>::iterator		it;
  if (_bombs.size() > 0)
    it = _bombs.begin();
  for (it = _bombs.begin(); _bombs.size() > 0 && it != _bombs.end(); it++)
    {
      if ((*it)->isExpired(gameClock_->getTotalGameTime()) == true)
	{
	  this->_musicBomb->playSong("bombS");
	  (*it)->explose(this);
	  this->getPlayerById((*it)->getIdPlayer())->getCaracteristique().delBomb();
	  delete *it;
	  it = _bombs.erase(it);
	}
    }
}

bool					Core::hasBombOnPos(const unsigned int &x, const unsigned int &y)
{
  std::list<Bomb*>::iterator		it = _bombs.begin();

  for (; it != _bombs.end(); it++)
    {
      if ((unsigned int)(*it)->getX() == x && (unsigned int)(*it)->getY() == y)
	return true;
    }
  return false;
}

void					Core::setMap(CoreMap* map)
{
  this->_map = map;
}

void					Core::setPlayers(std::list<APlayer*> players)
{
  this->_players = players;
}

Position*				Core::genPositionPlayers(const Option& opt)
{
  unsigned int				x;
  unsigned int				y;
  bool					findPlace = true;
  std::list<APlayer*>::iterator		it;

  while (findPlace)
    {
      findPlace = false;
      x = 1 + (rand() % (opt.getXMap() - 1));
      y = 1 + (rand() % (opt.getYMap() - 1));
      if (x % 2 == 0)
	x < (opt.getXMap() / 2)? x++: x--;
      if (y % 2 == 0)
	y < (opt.getXMap() / 2)? y++: y--;
      it = this->_players.begin();
      while (it != this->_players.end())
	{
	  if ((unsigned int)(*it)->getX() == x && (unsigned int)(*it)->getY() == y)
	    findPlace = true;
	  it++;
	}
    }
  float posX = (float)x + 0.5;
  float posY = (float)y + 0.5;
  Position *ret = new Position(posX, posY);
  return ret;
}

void					Core::genPlayers(const Option & opt)
{
  unsigned int				id = 0;
  unsigned int				nb = opt.getNbPlayer() + opt.getNbIa();
  unsigned int				nb_tmp = 0;
  double				x = 1.5;
  double				y = 1.5;
  Caracteristique			*carac;
  APlayer				*player;

  while (nb_tmp < nb)
    {
      carac = new Caracteristique(5);
      if (id < opt.getNbPlayer())
	player = new APlayer(id, this->genPositionPlayers(opt), carac, false);
      else
	player = new APlayer(id, genPositionPlayers(opt), carac, true);
      player->initialize();
      this->_players.push_back(player);
      nb_tmp++;
      id++;
    }
}

APlayer*				Core::getPlayerById(const unsigned int& id) const
{
  std::list<APlayer*>::iterator		it;
  std::list<APlayer*>			pl = this->getPlayer();

  for (it = pl.begin(); it != pl.end() && (*it)->getId() != id; it++)
    ;
  if ((*it)->getId() != id)
    return NULL;
  return (*it);
}

CoreMap*				Core::getMap() const
{
  return _map;
}

std::list<APlayer*>			Core::getPlayer() const
{
  return _players;
}

void					Core::isPlayer(unsigned int x, unsigned int y)
{
  std::list<APlayer*>::iterator		it;

  for (it = _players.begin(); it != _players.end(); it++)
    {
      if ((int)(*it)->getX() == x && (int)(*it)->getY() == y)
	(*it)->takeDamage(1, this);
    }
}


void					Core::setBombs(std::list<Bomb*> bombs)
{
  this->_bombs = bombs;
}

unsigned int				Core::isBomb(const unsigned int& x, const unsigned int& y, const unsigned int &prevRet)
{
  std::list<Bomb*>::iterator it;

  for (it = this->_bombs.begin(); it != this->_bombs.end(); it++)
    {
      if ((unsigned int)(*it)->getX() == x && (unsigned int)(*it)->getY() == y)
	return INDES;
    }
  return prevRet;
}

unsigned int				Core::getXMax(void) const
{
  return _map->getXMax();
}

unsigned int				Core::getYMax(void) const
{
  return _map->getYMax();
}

void					Core::addBomb(Bomb* newBomb)
{
  this->_bombs.push_back(newBomb);
}

std::list<Bomb*>			Core::getBomb() const
{
  return _bombs;
}

gdl::GameClock				*Core::getGameClock() const
{
  return gameClock_;
}

float					Core::getTime(void) const
{
  return this->_timeInGame;
}

void					Core::setTime(const float & time)
{
  this->_timeInGame = time;
}
