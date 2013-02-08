
#ifndef		__OPTION_HPP__
#define		__OPTION_HPP__

#define		XMAP_DEFAULT		25;
#define		YMAP_DEFAULT		25;
#define		DENSITYBLOC_DEFAULT	80;

/*
** Class Option
*/

class Option
{
  int		_xMap;
  int		_yMap;
  int		_densityBloc;
  unsigned int	_nbPlayer;
  unsigned int	_nbIa;
  unsigned int	_bonus;

public:
  Option(const int & x, const int & y, const int & dens, const unsigned int & nb_player, const unsigned int & nb_ia);
  ~Option();

  void			setNbPlayer(const unsigned int & nb);
  void			setNbIa(const int & nb);
  void			setDensityBloc(const int & d);
  void			setXMap(const int & x);
  void			setYMap(const int & x);
  int			getXMap() const;
  int			getYMap() const;
  int			getDensityBloc() const;
  unsigned int		getNbPlayer() const;
  unsigned int		getNbIa() const;
  void			setBonusDensity(int const & nb);
  unsigned int		getBonusDensity() const;
};

#endif /* __OPTION_HPP__ */
