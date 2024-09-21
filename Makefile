# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -DPLATFORM_DESKTOP
LDFLAGS = -L$(RAYLIB_PATH)/src -L$(RAYLIB_PATH)/src/external

# Full static linking
STATIC_FLAGS = -static -static-libgcc -static-libstdc++

# Raylib linking (assuming static library is available)
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm $(STATIC_FLAGS)

# Paths
RAYLIB_PATH = C:/raylib/raylib

# Project files for PL_test
SRC_PL =  PL_test.cpp Player.cpp Enemy.cpp Asteroids.cpp PlayerProj.cpp Projectiles.cpp
OBJ_PL = $(SRC_PL:.cpp=.o)
EXEC_PL = PL_test.exe

# Project files for Aster_test
SRC_ASTER =  Aster_test.cpp Player.cpp Enemy.cpp Asteroids.cpp PlayerProj.cpp Projectiles.cpp
OBJ_ASTER = $(SRC_ASTER:.cpp=.o)
EXEC_ASTER = Aster_test.exe

# Project files for PLproj_test
SRC_PLproj = PLproj_test.cpp PlayerProj.cpp Projectiles.cpp Player.cpp PlayerProj.cpp Projectiles.cpp
OBJ_PLproj = $(SRC_PLproj:.cpp=.o)
EXEC_PLproj = PLproj_test.exe

# Default target
all: $(EXEC_PL) $(EXEC_ASTER) $(EXEC_PLproj)

# Link the executable for PL_test with full static linking
$(EXEC_PL): $(OBJ_PL)
	$(CXX) -o $(EXEC_PL) $(OBJ_PL) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Link the executable for Aster_test with full static linking
$(EXEC_ASTER): $(OBJ_ASTER)
	$(CXX) -o $(EXEC_ASTER) $(OBJ_ASTER) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Compilation rule for the executable with full static linking
$(EXEC_PLproj): $(OBJ_PLproj)
	$(CXX) -o $(EXEC_PLproj) $(OBJ_PLproj) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

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
