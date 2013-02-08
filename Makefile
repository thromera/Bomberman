NAME =		bomberman

SRC =		main.cpp\
		ObjMenu/MenuBomb.cpp\
		ObjMenu/Accueil.cpp\
		ObjMap/Wall.cpp\
		ObjMap/Ground.cpp\
		ObjMap/BlockFire.cpp\
		ObjMap/Block.cpp\
		ObjMap/BlockDes.cpp\
		ObjMap/Panel.cpp\
		ObjIntro/Intro.cpp\
		ObjIntro/Model.cpp\
		BonusMap/HeartUp.cpp\
		BonusMap/FireUp.cpp\
		BonusMap/BombUp.cpp\
		BonusMap/SpeedUp.cpp\
		BonusMap/Light.cpp\
		Bomb.cpp \
		Caracteristique.cpp \
		Objects.cpp \
		Position.cpp \
		APlayer.cpp \
		Option.cpp \
		Menu.cpp \
		CoreMap.cpp \
		Core.cpp \
		MyGame.cpp\
		Pos3f.cpp\
		Camera.cpp\
		Music.cpp \
		Ia.cpp \
		Intro_MyGame.cpp\
		Save.cpp\
		Load.cpp\
		EndGame.cpp\
		TextMap.cpp

OBJ =		$(SRC:.cpp=.o)

CPPFLAGS =	-I./libgdl_gl-2012.1/include -O3

LDFLAGS =	-L./libgdl_gl-2012.1/lib -Wl,--rpath=./libgdl_gl-2012.1/lib,--rpath=/usr/local/lib -lgdl_gl -lGL -lGLU -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lpthread

all:		$(NAME)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(OBJ) $(LDFLAGS)

%.o:		%.cpp
		g++ $(CPPFLAGS) -o $@ -c $<

clean:
		rm -fr $(OBJ)

fclean:		clean
		rm -fr $(NAME)

re:		fclean all