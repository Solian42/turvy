# Set up basic variables:
CC = g++
CFLAGS = -c -Wall -pedantic
LDFLAGS =
 
# List of sources:
SOURCES = demo.cpp
OBJECTS = $(SOURCES:.cpp=.o)
 
# Name of executable target:
EXECUTABLE = demo
 
# pkg-config specific flags:
CFLAGS += `pkg-config --cflags sdl2 SDL2_image SDL2_ttf SDL2_mixer libmikmod`
LDFLAGS += `pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer libmikmod`

#all target
all: $(SOURCES) $(EXECUTABLE)

#executable targets 
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

#object target
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

#clean target 
clean:
	rm $(OBJECTS) $(EXECUTABLE)