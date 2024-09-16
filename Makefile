# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external
LDFLAGS = -L$(RAYLIB_PATH)/src -L$(RAYLIB_PATH)/src/external
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Paths
RAYLIB_PATH = C:/path/to/raylib

# Project files
SRC = Player.cpp PL_test.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = PL_test.exe

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJ)
	$(CXX) -o $(EXEC) $(OBJ) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Compile C++ source files to object files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean up build artifacts
clean:
	del *.o *.exe

.PHONY: all clean
