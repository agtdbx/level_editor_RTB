TARGET = RTB

CC = g++

OBJ = 	obj/main.o \
		obj/Button.o \
		obj/Camera.o \
		obj/Editor.o \
		obj/EditorBar.o \
		obj/Functions.o \
		obj/Input.o \
		obj/Map.o \
		obj/Menu.o \
		obj/Select.o \
		obj/Switch.o \
		obj/Tuile.o \
		obj/Zone.o

INCLUDE = 	-I include/ \
			-I src/jsoncpp-src-0.5.0/include

SDL_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

JSON_FLAGS = -ljsoncpp


obj/%.o : src/%.cpp
	$(CC) -o $@ -c $(INCLUDE) $^ $(SDL_FLAGS) $(JSON_FLAGS)

bin/$(TARGET) : $(OBJ)
	$(CC) -o $@ $(INCLUDE) $^ $(SDL_FLAGS) $(JSON_FLAGS)


run : bin/$(TARGET)
	bin/$(TARGET)

clean :
	rm -f obj/*.o

fclean : clean
	rm -f bin/$(TARGET)

re : clean bin/$(TARGET)

install :
	sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
	sudo apt-get install libjsoncpp-dev
	mkdir bin
	mkdir obj


.PHONY: run clean re install