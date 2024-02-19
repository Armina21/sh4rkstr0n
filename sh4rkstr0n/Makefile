
CORE = core/Jeu.cpp core/Joueur.cpp core/Terrain.cpp core/vec2D.cpp

SRCS_MAIN = $(CORE) main/mainTest.cpp
FINAL_TARGET_MAIN = main

SRCS_TXT = $(CORE) txt/txt_jeu.cpp txt/winTxt.cpp txt/main_txt.cpp
FINAL_TARGET_TXT = tron_txt
#DEFINE_TXT = -DJEU_TXT

SRCS_SFML = $(CORE) sfml/sfmlJeu.cpp sfml/main_sfml.cpp sfml/sfmlMenu.cpp
FINAL_TARGET_SFML = tron_sfml
#DEFINE_TXT = -DJEU_SFML

ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SFML = 	-Iextern/windows/include

	LIBS_SFML = -Lextern/windows/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

else
	INCLUDE_DIR_SFML = -Iextern/linux/include
	LIBS_SFML = -Lextern/linux/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
endif

CC					= g++
LD 					= g++
LDFLAGS  			=
CPPFLAGS 			= -Wall -ggdb   #-O2   # pour optimiser
OBJ_DIR 			= obj
SRC_DIR 			= src
BIN_DIR 			= bin
INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/sfml -Itxt

default: make_dir $(BIN_DIR)/$(FINAL_TARGET_MAIN) $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SFML)

make_dir:
ifeq ($(OS),Windows_NT)
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR) $(OBJ_DIR)\txt $(OBJ_DIR)\sfml $(OBJ_DIR)\main $(OBJ_DIR)\core
else
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) $(OBJ_DIR)/txt $(OBJ_DIR)/sfml $(OBJ_DIR)/main $(OBJ_DIR)/core
endif

$(BIN_DIR)/$(FINAL_TARGET_MAIN): $(SRCS_MAIN:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(BIN_DIR)/$(FINAL_TARGET_TXT): $(SRCS_TXT:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(BIN_DIR)/$(FINAL_TARGET_SFML): $(SRCS_SFML:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_SFML)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR_SFML) $(INCLUDE_DIR) $< -o $@


docu: doc/tron.doxy
	cd doc ; doxygen tron.doxy

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJ_DIR)\txt\*.o $(OBJ_DIR)\sfml\*.o $(OBJ_DIR)\core\*.o $(BIN_DIR)\$(FINAL_TARGET_MAIN).exe $(BIN_DIR)\$(FINAL_TARGET_TXT).exe $(BIN_DIR)\$(FINAL_TARGET_SFML).exe
else
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(FINAL_TARGET_MAIN) $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SFML) doc/html
endif


