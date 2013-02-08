#ifndef __COREMAP_HPP__
#define __COREMAP_HPP__

#include <vector>
#include "Option.hpp"
#include "APlayer.hpp"
#include "TextMap.hpp"
#include "all.hpp"
#include "Objects.hpp"

class APlayer;

#define ROUND(x) x + 0.5f
typedef enum e_bloc
{
    INDES, // 0
    DES,  // 1
    DESB, // 2
    DESS, // 3
    DESR, // 4
    DESL,
    DESC,
    VOID, // 5
    BOMB, // 6
    SPEED, //7
    RANGE, // 8
    LIFE,
    LIGHT
  }		Ibloc;

  class					        CoreMap
  {
    std::vector<std::vector<Ibloc> >		_map;
    unsigned int				_xmax;
    unsigned int				_ymax;
    Objects					* _obj;

  public:
    CoreMap(){};
    ~CoreMap(){};

    void						draw();

    void						genMap(const Option & opt);
    std::vector<std::vector<Ibloc> >			getMap() const;
    unsigned int					getXMax() const;
    unsigned int					getYMax() const;
    void				                setXMax(const unsigned int &x);
    void						setYMax(const unsigned int &y);
    void						setObjects(Objects *);
    void						setMap(std::vector<std::vector<Ibloc> >& map);
    Ibloc						getAt(const double &dx, const double &dy) const;

    void						setAt(const double &dd, const double&d, Ibloc);
    Ibloc						genBonus(const Option&);
    void						adjustMapWithPlayers(std::list<APlayer*> playerList);
  };

#endif
