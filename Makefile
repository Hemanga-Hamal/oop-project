# YOU WILL HAVE TO CHANGE THIS BASED ON OPERATING SYSTEM

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external
LDFLAGS = -L$(RAYLIB_PATH)/src -L$(RAYLIB_PATH)/src/external
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Paths
RAYLIB_PATH = C:/raylib/raylib

# Project files for PL_test
SRC_PL = Player.cpp PL_test.cpp Enemy.cpp Asteroids.cpp
OBJ_PL = $(SRC_PL:.cpp=.o)
EXEC_PL = PL_test.exe

# Project files for Aster_test
SRC_ASTER = Player.cpp Aster_test.cpp Enemy.cpp Asteroids.cpp
OBJ_ASTER = $(SRC_ASTER:.cpp=.o)
EXEC_ASTER = Aster_test.exe

# Default target
all: $(EXEC_PL) $(EXEC_ASTER)

# Link the executable for PL_test
$(EXEC_PL): $(OBJ_PL)
	$(CXX) -o $(EXEC_PL) $(OBJ_PL) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Link the executable for Aster_test
$(EXEC_ASTER): $(OBJ_ASTER)
	$(CXX) -o $(EXEC_ASTER) $(OBJ_ASTER) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Compile C++ source files to object files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean up build artifacts
clean:
	del *.o *.exe

.PHONY: all clean
