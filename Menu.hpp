#ifndef __MENU__
#define __MENU__

typedef enum e_menuPosCursor
{
	OPTION_ONE = 1,
	OPTION_TWO = 2,
	OPTION_THR = 3,
	OPTION_FOU = 4,
	OPTION_FIV = 5,
	OPTION_SIX = 6
}		e_menuWho;

typedef enum e_menuWhichMenu
{
	MENU_FIRST = 1,
	MENU_OPTGEN	= 2,
	MENU_OPTMAP	= 3,
	MENU_OPTPLAY = 4,
	MENU_MAP = 5,
	MENU_CREDITS = 6
}			e_menuWhere;

#define MAX_MENU	OPTION_FIV
#define MAX_MAP 	OPTION_FOU
#define MAX_OPTGEN	OPTION_FOU
#define MAX_OPTMAP	OPTION_FIV
#define MAX_OPTPLAY	OPTION_THR
#define MAX_CREDITS	OPTION_FIV

#define SPACE_MENU		280.0f
#define SPACE_OPTION	250.0f
#define SPACE_CREDITS	320.0f

typedef enum  e_menuKeyDir
{
	MUP	= 1,
	MLEFT = 2,
	MDOWN = 3,
	MRIGHT = 4
}			e_menuKey;

class Menu
{
public:
  int		where_;
  int		who_;
  int		what_;
  bool		ng_;
};

#endif
