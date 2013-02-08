#ifndef __POSITION_HPP__
#define __POSITION_HPP__

/*
** Class Position
*/

class			Position
{
public:
  Position(const double& x, const double& y);
  ~Position(){};

  double		_x;
  double		_y;
};

#endif
