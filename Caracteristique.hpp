#ifndef __CARACTERISTIQUE_HPP__
#define __CARACTERISTIQUE_HPP__

/*
** Class for caracteristique for each char;
*/

class			Caracteristique
{
public:
  Caracteristique(const unsigned int& life = 5);
  ~Caracteristique();

private:
  unsigned int			_life;
  unsigned int			_speed;
  unsigned int			_actualBomb;
  unsigned int			_maxBomb;
  unsigned int			_range;

public:
  const unsigned int&		getLife(void) const;
  const unsigned int&		getSpeed(void) const;
  const unsigned int&		getMaxBomb() const;
  const unsigned int&		getActualBomb() const;
  const unsigned int&		getRange(void) const;
  void				setLife(const unsigned int& life);
  void				setSpeed(const unsigned int& speed);
  void				setActualBomb(const unsigned int& bomb);
  void				setMaxBomb(const unsigned int&);
  void				setRange(const unsigned int& range);
  bool				putBomb(void);
  void				delBomb();
  void				increaseBomb(const unsigned int& toAdd);
  void				increaseSpeed(const unsigned int&);
  void				increaseRange(const unsigned int&);  
  void				increaseLife(const unsigned int& toAdd);
};

#endif
