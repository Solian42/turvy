#directories
SRCDIR   = .
OBJDIR   = ./obj
BINDIR   = ../bin

TARGET   = lizard

CC       = g++
# compiling flags here
CFLAGS   = -Wall -Wextra -pedantic

LINKER   = g++ -o
# linking flags here
LFLAGS   = -Wall -lm

CFLAGS += `pkg-config  sdl2 SDL2_image SDL2_ttf SDL2_mixer --cflags`
LFLAGS += `pkg-config  sdl2 SDL2_image SDL2_ttf SDL2_mixer --libs`

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"