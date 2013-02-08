#include <sstream>

#include "ObjMenu.hpp"
#include "../Menu.hpp"

namespace ObjMenu
{

  Accueil::Accueil(void)
  {
  }

  Accueil::~Accueil(void)
  {
  }

  void		Accueil::reset_accueil(void)
  {
    this->mb_.reset_bomb(this->who_);
  }

  void		Accueil::initialize_(void)
  {
    this->tTitle_ = gdl::Image::load("Textures/title.png");
    this->tOption_ = gdl::Image::load("Textures/title.png");
    this->text_.setMap("font/panda.png");
    this->text_.setSize(150);
    this->key_ = false;
    this->ng_ = true;
    this->who_ = 1;
    this->mb_.initialize(this->who_);
  }

  void		Accueil::initialize(void)
  {
    this->pos_.setPos(0.0, 0.0, 1.0);
    this->initialize_();
  }

  void		Accueil::initialize(float const & x, float const & y, float const &z)
  {
    this->pos_.setPos(x, y, z);
    this->initialize_();
  }

  void		Accueil::menu_first_(int const & dir)
  {
    if (dir == MUP)
      this->who_ -= 1;
    else if (dir == MDOWN)
      this->who_ += 1;
    
    if (this->who_ > (MAX_MENU))
      this->who_ = 1;
    else if (this->who_ < 1)
      this->who_ = (MAX_MENU);
    
    this->mb_.setSpace(SPACE_MENU);
    this->mb_.update(this->who_);
  }

  void    Accueil::menu_optGen_(int const & dir)
  {
    if (dir == MUP)
      this->who_ -= 1;
    else if (dir == MDOWN)
      this->who_ += 1;
    
    if (this->who_ > MAX_OPTGEN)
      this->who_ = OPTION_ONE;
    else if (this->who_ < OPTION_ONE)
      this->who_ = MAX_OPTGEN;

    this->mb_.setSpace(SPACE_OPTION);
    this->mb_.update((this->who_)); 
  }

  void    Accueil::menu_credits_(int const & dir)
  {
    if (dir == MUP)
      this->who_ -= 1;
    else if (dir == MDOWN)
      this->who_ += 1;
    
    if (this->who_ > MAX_CREDITS)
      this->who_ = OPTION_ONE;
    else if (this->who_ < OPTION_ONE)
      this->who_ = MAX_CREDITS;

    this->mb_.setSpace(SPACE_OPTION);
    this->mb_.update((this->who_)); 
  }

  void    Accueil::menu_optMap_(int const & dir)
  {
    if (dir == MUP)
      this->who_ -= 1;
    else if (dir == MDOWN)
      this->who_ += 1;

    if (this->who_ > MAX_OPTMAP)
      this->who_ = OPTION_ONE;
    else if (this->who_ < OPTION_ONE)
      this->who_ = MAX_OPTMAP;

    this->mb_.setSpace(SPACE_OPTION);
    this->mb_.update((this->who_)); 
  }

  void    Accueil::menu_optPlay_(int const & dir)
  {
    if (dir == MUP)
      this->who_ -= 1;
    else if (dir == MDOWN)
      this->who_ += 1;

    if (this->who_ > MAX_OPTPLAY)
      this->who_ = OPTION_ONE;
    else if (this->who_ < OPTION_ONE)
      this->who_ = MAX_OPTPLAY;

    this->mb_.setSpace(SPACE_OPTION);
    this->mb_.update((this->who_)); 
  }

  void    Accueil::menu_map_(int const & dir)
  {
    if (dir == MUP)
      this->who_ -= 1;
    else if (dir == MDOWN)
      this->who_ += 1;

    if (this->who_ > MAX_MAP)
      this->who_ = OPTION_ONE;
    else if (this->who_ < OPTION_ONE)
      this->who_ = MAX_MAP;

    this->mb_.setSpace(SPACE_OPTION);
    this->mb_.update((this->who_)); 
  }

  int		Accueil::update(int const & who)
  {
    this->who_ = who;
    this->mb_.update(this->who_);
    return(0);
  }

  int		Accueil::update(int const & dir, int const & menu)
  {
    if (dir != 0)
      {
	switch (menu)
	  {
	  case MENU_FIRST:
	    this->menu_first_(dir);
	    break;
	  case MENU_OPTGEN:
	    this->menu_optGen_(dir);
	    break;
	  case MENU_OPTMAP:
	    this->menu_optMap_(dir);
	    break;
	  case MENU_OPTPLAY:
	    this->menu_optPlay_(dir);
	    break;
	  case MENU_MAP:
	    this->menu_map_(dir);  
	    break;
	  }    
      }
    return(this->who_);
  }

  void		Accueil::draw_first_(void)
  {
    this->tTitle_.bind();
    this->text_.setSize((SPACE_MENU / 2) - 10);
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(-LARGEUR_ECRAN + 900, (HAUTEUR_ECRAN) - 300, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex3f(-300, -600/2, 600);
    glTexCoord2d(0, 0); glVertex3f(-300, 600/2, 600);
    glTexCoord2d(1, 0); glVertex3f(900, 600/2, 600);
    glTexCoord2d(1, 1); glVertex3f(900, -600/2, 600);
    glEnd();
    glDisable(GL_BLEND);
    glTranslatef(-300, -400, 0);
    if (this->ng_ == false)
      this->text_.putStr("New Game\n\nResume\n\nLoad\n\nOptions\n\nExit");
    else
      {
	this->text_.putStr("New Game\n\n\n\nLoad\n\nOptions\n\nExit");
	this->text_.putStr("\n\n-No game-");
      }
    glPopMatrix();
  }

  void    Accueil::draw_optGen_(void)
  {
    this->tOption_.bind();
    this->text_.setSize((SPACE_OPTION / 2) - 10);
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(-LARGEUR_ECRAN + 900, (HAUTEUR_ECRAN) - 300, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex3f(-300, -600/2, 600);
    glTexCoord2d(0, 0); glVertex3f(-300, 600/2, 600);
    glTexCoord2d(1, 0); glVertex3f(900, 600/2, 600);
    glTexCoord2d(1, 1); glVertex3f(900, -600/2, 600);
    glEnd();
    glDisable(GL_BLEND);
    glTranslatef(-500, -400, 0);
    this->text_.putStr("Map\n\nPlayers\n\nCredits\n\nConfirmer");
    glPopMatrix();
  }

  void    Accueil::draw_credits_(void)
  {
    this->tOption_.bind();
    this->text_.setSize((SPACE_OPTION / 2) - 10);
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(-LARGEUR_ECRAN + 900, (HAUTEUR_ECRAN) - 300, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex3f(-300, -600/2, 600);
    glTexCoord2d(0, 0); glVertex3f(-300, 600/2, 600);
    glTexCoord2d(1, 0); glVertex3f(900, 600/2, 600);
    glTexCoord2d(1, 1); glVertex3f(900, -600/2, 600);
    glEnd();
    glDisable(GL_BLEND);
    glTranslatef(-500, -400, 0);
    this->text_.putStr("Audran Eric\n\nEmirot Nolan\n\nGresse Mickael\n\nMorales Cyril\n\nRomera Thomas");
    glPopMatrix();
  }

  void    Accueil::draw_map_(void)
  {
    this->tOption_.bind();
    this->text_.setSize((SPACE_OPTION / 2) - 10);
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(-LARGEUR_ECRAN + 900, (HAUTEUR_ECRAN) - 300, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex3f(-300, -600/2, 600);
    glTexCoord2d(0, 0); glVertex3f(-300, 600/2, 600);
    glTexCoord2d(1, 0); glVertex3f(900, 600/2, 600);
    glTexCoord2d(1, 1); glVertex3f(900, -600/2, 600);
    glEnd();
    glDisable(GL_BLEND);
    glTranslatef(-500, -400, 0);
    this->text_.putStr("Level 1\n\nLevel 2\n\nRandomized Map\n\nBack");
    glPopMatrix();
  }

  void    Accueil::draw_optMap_(Option const & opt)
  {
    std::ostringstream    x;
    std::ostringstream    y;
    std::ostringstream    bloc;
    std::ostringstream    bonus;

    x << opt.getXMap() - 2;
    y << opt.getYMap() - 2;
    bloc << opt.getDensityBloc();
    bonus << opt.getBonusDensity();

    this->tOption_.bind();
    this->text_.setSize((SPACE_OPTION / 2) - 10);
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(-LARGEUR_ECRAN + 900, (HAUTEUR_ECRAN) - 300, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex3f(-300, -600/2, 600);
    glTexCoord2d(0, 0); glVertex3f(-300, 600/2, 600);
    glTexCoord2d(1, 0); glVertex3f(900, 600/2, 600);
    glTexCoord2d(1, 1); glVertex3f(900, -600/2, 600);
    glEnd();
    glDisable(GL_BLEND);
    glTranslatef(-500, -400, 0);
    this->text_.putStr("Max X:\n\nMax Y:\n\n\%break:\n\n\%bonus:\n\nConfirmer");
    glPushMatrix();

    glPopMatrix();
    glTranslatef(1000, 0, 0);
    this->text_.putStr(x.str());
    glTranslatef(0, -SPACE_OPTION + 10, 0);
    this->text_.putStr(y.str());
    glTranslatef(0, -SPACE_OPTION + 10, 0);
    this->text_.putStr(bloc.str());
    glTranslatef(0, -SPACE_OPTION + 10, 0);
    this->text_.putStr(bonus.str());
    glPopMatrix();
  }

  void    Accueil::draw_optPlay_(Option const & opt)
  {
    std::ostringstream    nbPlayer;
    std::ostringstream    nbIa;

    nbPlayer << opt.getNbPlayer();
    nbIa << opt.getNbIa();

    this->tOption_.bind();
    this->text_.setSize((SPACE_OPTION / 2) - 10);
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(-LARGEUR_ECRAN + 900, (HAUTEUR_ECRAN) - 300, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex3f(-300, -600/2, 600);
    glTexCoord2d(0, 0); glVertex3f(-300, 600/2, 600);
    glTexCoord2d(1, 0); glVertex3f(900, 600/2, 600);
    glTexCoord2d(1, 1); glVertex3f(900, -600/2, 600);
    glEnd();
    glDisable(GL_BLEND);
    glTranslatef(-500, -400, 0);
    this->text_.putStr("Player\n\nIa\n\nConfirmer");
    glPushMatrix();

    glPopMatrix();
    glTranslatef(1000, 0, 0);
    this->text_.putStr(nbPlayer.str());
    glTranslatef(0, -200, 0);
    this->text_.putStr(nbIa.str());
    glPopMatrix();
  }

  void		Accueil::draw(Option const & opt, int const & mod)
  {
    switch (mod)
      {
      case MENU_FIRST:
	this->draw_first_();
	break;
      case MENU_OPTGEN:
	this->draw_optGen_();
	break;
      case MENU_OPTPLAY:
	this->draw_optPlay_(opt);
	break;
      case MENU_OPTMAP:
	this->draw_optMap_(opt);
	break;
      case MENU_MAP:
	this->draw_map_();
	break;
      case MENU_CREDITS:
	this->draw_credits_();
	break;
      }
    this->mb_.draw();
  }

  bool  Accueil::isNewGame(void) const
  {
    return(this->ng_);
  }

  void  Accueil::setNewGame(bool const & ng)
  {
    this->ng_ = ng;
  }
}

