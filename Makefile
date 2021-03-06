#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -std=c++11
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = -lSDLmain -lSDL -lSDL_ttf

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -Wall -Wextra -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/Othello

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -Os -O3 -s
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/Othello

OBJ_DEBUG = $(OBJDIR_DEBUG)/interface/SelecteurNom.o \
	$(OBJDIR_DEBUG)/interface/Interface.o \
	$(OBJDIR_DEBUG)/interface/Menu.o \
	$(OBJDIR_DEBUG)/interface/MenuJouer.o \
	$(OBJDIR_DEBUG)/interface/Message.o \
	$(OBJDIR_DEBUG)/jeu/Joueur.o \
	$(OBJDIR_DEBUG)/jeu/Partie.o \
	$(OBJDIR_DEBUG)/jeu/Plateau.o \
	$(OBJDIR_DEBUG)/main.o \
	$(OBJDIR_DEBUG)/affichage/Tuile.o \
	$(OBJDIR_DEBUG)/Jeu.o \
	$(OBJDIR_DEBUG)/Sequenceur.o \
	$(OBJDIR_DEBUG)/affichage/Image.o \
	$(OBJDIR_DEBUG)/affichage/Sprite.o \
	$(OBJDIR_DEBUG)/Horloge.o \
	$(OBJDIR_DEBUG)/fichiers/Configuration.o \
	$(OBJDIR_DEBUG)/fichiers/Replay.o \
	$(OBJDIR_DEBUG)/interface/AutoMenu.o \
	$(OBJDIR_DEBUG)/interface/Bouton.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/interface/SelecteurNom.o \
	$(OBJDIR_RELEASE)/interface/Interface.o \
	$(OBJDIR_RELEASE)/interface/Menu.o \
	$(OBJDIR_RELEASE)/interface/MenuJouer.o \
	$(OBJDIR_RELEASE)/interface/Message.o \
	$(OBJDIR_RELEASE)/jeu/Joueur.o \
	$(OBJDIR_RELEASE)/jeu/Partie.o \
	$(OBJDIR_RELEASE)/jeu/Plateau.o \
	$(OBJDIR_RELEASE)/main.o \
	$(OBJDIR_RELEASE)/affichage/Tuile.o \
	$(OBJDIR_RELEASE)/Jeu.o \
	$(OBJDIR_RELEASE)/Sequenceur.o \
	$(OBJDIR_RELEASE)/affichage/Image.o \
	$(OBJDIR_RELEASE)/affichage/Sprite.o \
	$(OBJDIR_RELEASE)/Horloge.o \
	$(OBJDIR_RELEASE)/fichiers/Configuration.o \
	$(OBJDIR_RELEASE)/fichiers/Replay.o \
	$(OBJDIR_RELEASE)/interface/AutoMenu.o \
	$(OBJDIR_RELEASE)/interface/Bouton.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/interface || mkdir -p $(OBJDIR_DEBUG)/interface
	test -d $(OBJDIR_DEBUG)/jeu || mkdir -p $(OBJDIR_DEBUG)/jeu
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)
	test -d $(OBJDIR_DEBUG)/affichage || mkdir -p $(OBJDIR_DEBUG)/affichage
	test -d $(OBJDIR_DEBUG)/fichiers || mkdir -p $(OBJDIR_DEBUG)/fichiers

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/interface/SelecteurNom.o: interface/SelecteurNom.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c interface/SelecteurNom.cpp -o $(OBJDIR_DEBUG)/interface/SelecteurNom.o

$(OBJDIR_DEBUG)/interface/Interface.o: interface/Interface.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c interface/Interface.cpp -o $(OBJDIR_DEBUG)/interface/Interface.o

$(OBJDIR_DEBUG)/interface/Menu.o: interface/Menu.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c interface/Menu.cpp -o $(OBJDIR_DEBUG)/interface/Menu.o

$(OBJDIR_DEBUG)/interface/MenuJouer.o: interface/MenuJouer.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c interface/MenuJouer.cpp -o $(OBJDIR_DEBUG)/interface/MenuJouer.o

$(OBJDIR_DEBUG)/interface/Message.o: interface/Message.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c interface/Message.cpp -o $(OBJDIR_DEBUG)/interface/Message.o

$(OBJDIR_DEBUG)/jeu/Joueur.o: jeu/Joueur.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c jeu/Joueur.cpp -o $(OBJDIR_DEBUG)/jeu/Joueur.o

$(OBJDIR_DEBUG)/jeu/Partie.o: jeu/Partie.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c jeu/Partie.cpp -o $(OBJDIR_DEBUG)/jeu/Partie.o

$(OBJDIR_DEBUG)/jeu/Plateau.o: jeu/Plateau.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c jeu/Plateau.cpp -o $(OBJDIR_DEBUG)/jeu/Plateau.o

$(OBJDIR_DEBUG)/main.o: main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.cpp -o $(OBJDIR_DEBUG)/main.o

$(OBJDIR_DEBUG)/affichage/Tuile.o: affichage/Tuile.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c affichage/Tuile.cpp -o $(OBJDIR_DEBUG)/affichage/Tuile.o

$(OBJDIR_DEBUG)/Jeu.o: Jeu.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Jeu.cpp -o $(OBJDIR_DEBUG)/Jeu.o

$(OBJDIR_DEBUG)/Sequenceur.o: Sequenceur.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Sequenceur.cpp -o $(OBJDIR_DEBUG)/Sequenceur.o

$(OBJDIR_DEBUG)/affichage/Image.o: affichage/Image.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c affichage/Image.cpp -o $(OBJDIR_DEBUG)/affichage/Image.o

$(OBJDIR_DEBUG)/affichage/Sprite.o: affichage/Sprite.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c affichage/Sprite.cpp -o $(OBJDIR_DEBUG)/affichage/Sprite.o

$(OBJDIR_DEBUG)/Horloge.o: Horloge.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Horloge.cpp -o $(OBJDIR_DEBUG)/Horloge.o

$(OBJDIR_DEBUG)/fichiers/Configuration.o: fichiers/Configuration.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c fichiers/Configuration.cpp -o $(OBJDIR_DEBUG)/fichiers/Configuration.o

$(OBJDIR_DEBUG)/fichiers/Replay.o: fichiers/Replay.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c fichiers/Replay.cpp -o $(OBJDIR_DEBUG)/fichiers/Replay.o

$(OBJDIR_DEBUG)/interface/AutoMenu.o: interface/AutoMenu.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c interface/AutoMenu.cpp -o $(OBJDIR_DEBUG)/interface/AutoMenu.o

$(OBJDIR_DEBUG)/interface/Bouton.o: interface/Bouton.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c interface/Bouton.cpp -o $(OBJDIR_DEBUG)/interface/Bouton.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/interface
	rm -rf $(OBJDIR_DEBUG)/jeu
	rm -rf $(OBJDIR_DEBUG)
	rm -rf $(OBJDIR_DEBUG)/affichage
	rm -rf $(OBJDIR_DEBUG)/fichiers

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE)/interface || mkdir -p $(OBJDIR_RELEASE)/interface
	test -d $(OBJDIR_RELEASE)/jeu || mkdir -p $(OBJDIR_RELEASE)/jeu
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)
	test -d $(OBJDIR_RELEASE)/affichage || mkdir -p $(OBJDIR_RELEASE)/affichage
	test -d $(OBJDIR_RELEASE)/fichiers || mkdir -p $(OBJDIR_RELEASE)/fichiers

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/interface/SelecteurNom.o: interface/SelecteurNom.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c interface/SelecteurNom.cpp -o $(OBJDIR_RELEASE)/interface/SelecteurNom.o

$(OBJDIR_RELEASE)/interface/Interface.o: interface/Interface.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c interface/Interface.cpp -o $(OBJDIR_RELEASE)/interface/Interface.o

$(OBJDIR_RELEASE)/interface/Menu.o: interface/Menu.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c interface/Menu.cpp -o $(OBJDIR_RELEASE)/interface/Menu.o

$(OBJDIR_RELEASE)/interface/MenuJouer.o: interface/MenuJouer.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c interface/MenuJouer.cpp -o $(OBJDIR_RELEASE)/interface/MenuJouer.o

$(OBJDIR_RELEASE)/interface/Message.o: interface/Message.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c interface/Message.cpp -o $(OBJDIR_RELEASE)/interface/Message.o

$(OBJDIR_RELEASE)/jeu/Joueur.o: jeu/Joueur.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c jeu/Joueur.cpp -o $(OBJDIR_RELEASE)/jeu/Joueur.o

$(OBJDIR_RELEASE)/jeu/Partie.o: jeu/Partie.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c jeu/Partie.cpp -o $(OBJDIR_RELEASE)/jeu/Partie.o

$(OBJDIR_RELEASE)/jeu/Plateau.o: jeu/Plateau.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c jeu/Plateau.cpp -o $(OBJDIR_RELEASE)/jeu/Plateau.o

$(OBJDIR_RELEASE)/main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)/main.o

$(OBJDIR_RELEASE)/affichage/Tuile.o: affichage/Tuile.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c affichage/Tuile.cpp -o $(OBJDIR_RELEASE)/affichage/Tuile.o

$(OBJDIR_RELEASE)/Jeu.o: Jeu.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Jeu.cpp -o $(OBJDIR_RELEASE)/Jeu.o

$(OBJDIR_RELEASE)/Sequenceur.o: Sequenceur.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Sequenceur.cpp -o $(OBJDIR_RELEASE)/Sequenceur.o

$(OBJDIR_RELEASE)/affichage/Image.o: affichage/Image.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c affichage/Image.cpp -o $(OBJDIR_RELEASE)/affichage/Image.o

$(OBJDIR_RELEASE)/affichage/Sprite.o: affichage/Sprite.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c affichage/Sprite.cpp -o $(OBJDIR_RELEASE)/affichage/Sprite.o

$(OBJDIR_RELEASE)/Horloge.o: Horloge.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Horloge.cpp -o $(OBJDIR_RELEASE)/Horloge.o

$(OBJDIR_RELEASE)/fichiers/Configuration.o: fichiers/Configuration.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c fichiers/Configuration.cpp -o $(OBJDIR_RELEASE)/fichiers/Configuration.o

$(OBJDIR_RELEASE)/fichiers/Replay.o: fichiers/Replay.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c fichiers/Replay.cpp -o $(OBJDIR_RELEASE)/fichiers/Replay.o

$(OBJDIR_RELEASE)/interface/AutoMenu.o: interface/AutoMenu.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c interface/AutoMenu.cpp -o $(OBJDIR_RELEASE)/interface/AutoMenu.o

$(OBJDIR_RELEASE)/interface/Bouton.o: interface/Bouton.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c interface/Bouton.cpp -o $(OBJDIR_RELEASE)/interface/Bouton.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)/interface
	rm -rf $(OBJDIR_RELEASE)/jeu
	rm -rf $(OBJDIR_RELEASE)
	rm -rf $(OBJDIR_RELEASE)/affichage
	rm -rf $(OBJDIR_RELEASE)/fichiers

.PHONY: before_release after_release clean_release

