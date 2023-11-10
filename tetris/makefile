# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O3

# Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Directories
SRCDIR = src
OBJDIR = obj

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cc)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SOURCES))

# Executable name
EXECUTABLE = tetris

# Default target
all: $(EXECUTABLE)

# Build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the project
clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

.PHONY: all clean
