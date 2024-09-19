# YOU WILL HAVE TO CHANGE THIS BASED ON OPERATING SYSTEM

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -DPLATFORM_DESKTOP
LDFLAGS = -L$(RAYLIB_PATH)/src -L$(RAYLIB_PATH)/src/external

# Static linking flags for C++ libraries
STATIC_FLAGS = -static-libgcc -static-libstdc++

# Raylib linking for Windows (static)
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm $(STATIC_FLAGS)

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

# Link the executable for PL_test with static linking
$(EXEC_PL): $(OBJ_PL)
	$(CXX) -o $(EXEC_PL) $(OBJ_PL) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Link the executable for Aster_test with static linking
$(EXEC_ASTER): $(OBJ_ASTER)
	$(CXX) -o $(EXEC_ASTER) $(OBJ_ASTER) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Compile C++ source files to object files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean up build artifacts
clean:
ifeq ($(OS),Windows_NT)
	del /q *.o *.exe
else
	rm -f *.o *.exe
endif

.PHONY: all clean
