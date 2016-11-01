#get the OS name
UNAME_S := $(shell uname -s)

#directories
SRCDIR   := .
OBJDIR   := ./obj
BINDIR   := ../bin

#target executable
TARGET   := lizard

#C compiler/linker
ifeq ($(UNAME_S), Darwin)
	CC       := g++-6.2.0
	LINKER   := g++-6.2.0 -o
else
	CC := g++
	LINKER := g++ -o
endif
# compiling flags here
CFLAGS   := -c -g -std=c++11 -g -O2 -Wall -Wextra -pedantic `pkg-config --cflags sdl2 SDL2_image SDL2_ttf SDL2_mixer`


# linking flags here
LFLAGS   := `pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer` -Wall -lm -std=c++11

#defining source/include/obj variables.
SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

#making rm force
rm       = rm -f


#Target for linking objects
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"	


#Target for compiling object files
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled "$<" successfully!"

#Cleaning target
.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

#removing target
.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@$(rm) -r $(BINDIR)/*.dSYM
	@echo "Executable removed!"