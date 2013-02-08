#ifndef __OBJMENU__
#define __OBJMENU__

#include "../all.hpp"
#include "../AObject.hpp"
#include "../Pos3f.hpp"
#include "../TextMap.hpp"
#include "../Menu.hpp"
#include "../Option.hpp"

namespace ObjMenu
{
  class MenuBomb
  {
  public:
    MenuBomb(void);
    ~MenuBomb(void);
    void	reset_bomb(float const &);
    void	initialize(void);
    void	initialize(float const &);
    void	setSpace(float const &);
    void	update(float const &);
    void	draw(void);
  private:
    Pos3f	pos_;
    Pos3f	rot_;
    gdl::Model	model_;
    float	space_;

    void	initialize_(void);
  };

  class Accueil
  {
  public:
    Accueil(void);
    ~Accueil(void);
    void	reset_accueil(void);
    void	initialize(void);
    void	initialize(float const &, float const &, float const &);
    int		update(int const & );
    int		update(int const & , int const & );
    void	draw(Option const & opt, int const & mod);
    bool	isNewGame(void) const;
    void	setNewGame(bool const & );
  
  private:
    Pos3f	pos_;
    gdl::Image  tTitle_;
    gdl::Image  tOption_;
    TextMap	text_;
    MenuBomb	mb_;
    bool	key_;
    bool  ng_;
    int		who_;

    void	menu_first_(int const & );
    void	menu_optGen_(int const & );
    void	menu_optMap_(int const & );
    void	menu_optPlay_(int const & );
    void	menu_map_(int const & );
    void	menu_credits_(int const & );
    void	initialize_(void);
    void	draw_first_(void);
    void	draw_credits_(void);
    void	draw_optGen_(void);
    void	draw_map_(void);
    void	draw_optMap_(Option const & opt);
    void	draw_optPlay_(Option const & opt);
  };
}

#endif
