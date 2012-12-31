CC = gcc
CXX = g++

MAUVE = faggot

MINGW = /usr/i486-mingw32
CC_WIN = i486-mingw32-gcc
CXX_WIN = i486-mingw32-g++
LIBS = -lsfml-system  -lsfml-window -lsfml-graphics -lsfml-audio
LIBS_WIN = -L$(MINGW)/lib/ -lmingw32  -lsfml-system  -lsfml-window -lsfml-graphics -lsfml-audio -mwindows
TARGET = opensoku
TARGET_WIN = $(TARGET).exe
OBJS =  \
	archive.cpp\
	background.cpp\
	char_sprite.cpp\
	character_def.cpp\
	crc32.cpp\
	file_read.cpp\
	framedata.cpp\
	graph.cpp\
	input.cpp\
	mt.cpp\
	music.cpp\
	scene.cpp\
	chars/alice.cpp\
 	chars/marisa.cpp\
	chars/marisa_bullets.cpp\
	main.cpp\
	sfx.cpp\
	scene_fx.cpp\
	fx_sprite.cpp\
	bullets.cpp\
	moveable.cpp\
	fxsprite/fxSprite.cpp\
	fxsprite/fxTransform.cpp\
	fxsprite/fxTransformable.cpp\
	utils.cpp\
	unknown.cpp\
	meta.cpp

linux: $(OBJS)
	$(CXX) -O3 -Os --std=c++11 -o $(TARGET) $(OBJS) $(LIBS) -I /usr/include/ 

win32: $(OBJS)
	$(CXX_WIN) -O3 -Os --std=c++11 -o $(TARGET_WIN) $(OBJS) $(WINOBJ) $(LIBS_WIN) -I $(MINGW)/include/ 

clean:
	rm -f $(TARGET) $(TARGET_WIN) *.o
