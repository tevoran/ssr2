CC=x86_64-w64-mingw32-g++

SRC=$(wildcard src/*.cpp)

CFLAGS=-mwindows -o windows/y_fight.exe -Lwindows/libs -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -lopengl32 -lglu32 -Iwindows/include -static-libstdc++ -static-libgcc -pedantic -Wall -lmingw32

main: $(SRC)
	$(CC) $(SRC) $(CFLAGS)


