#ifndef __CAM__
#define __CAM__

#include "Pos3f.hpp"
#include "Music.hpp"
class Camera
{
public:
  Camera(void);
  void		reset_cam_menu(void);
  void		reset_cam_game(float const & x, float const & y);
  void		initialize(void);
  void		initializeN(void);
  void		initialize(float const & a, float const & b);
  void		update(gdl::GameClock const &, gdl::Input & input);
  void		getKeys(gdl::GameClock const &, gdl::Input & input);

  Pos3f		getPos(void) const;
  Pos3f		getPosn(void) const;
  Pos3f		getRot(void) const;
  void		setPos(Pos3f const & pos);
  void		setPosn(Pos3f const & posn);
  void		setRot(Pos3f const & pos);
private:
  Music		music_;
  Pos3f		pos_;
  Pos3f		posn_;
  Pos3f		rot_;
};

#endif
