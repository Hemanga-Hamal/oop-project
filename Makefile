# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -DPLATFORM_DESKTOP
LDFLAGS = -L$(RAYLIB_PATH)/src -L$(RAYLIB_PATH)/src/external

# Paths
RAYLIB_PATH_LINUX = /home/hemanga/raylib
RAYLIB_PATH_WINDOWS = C:/raylib/raylib

# Detect OS for proper linking
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    # On Linux, we'll link OpenGL dynamically but everything else statically
    STATIC_FLAGS = -static-libgcc -static-libstdc++
    LDLIBS = -lraylib -lGL -lm -lpthread -lX11 -lXrandr -lXinerama -lXi -lXcursor $(STATIC_FLAGS)
    RAYLIB_PATH = $(RAYLIB_PATH_LINUX)
else
    # On Windows, full static linking
    STATIC_FLAGS = -static -static-libgcc -static-libstdc++
    LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm $(STATIC_FLAGS)
    RAYLIB_PATH = $(RAYLIB_PATH_WINDOWS)
endif

# Project files for PL_test
SRC_PL = PL_test.cpp Player.cpp Enemy.cpp Asteroids.cpp PlayerProj.cpp Projectiles.cpp
OBJ_PL = $(SRC_PL:.cpp=.o)
EXEC_PL = PL_test.exe

# Project files for Aster_test
SRC_ASTER = Aster_test.cpp Player.cpp Enemy.cpp Asteroids.cpp PlayerProj.cpp Projectiles.cpp
OBJ_ASTER = $(SRC_ASTER:.cpp=.o)
EXEC_ASTER = Aster_test.exe

# Project files for PLproj_test
SRC_PLproj = PLproj_test.cpp PlayerProj.cpp Projectiles.cpp Player.cpp
OBJ_PLproj = $(SRC_PLproj:.cpp=.o)
EXEC_PLproj = PLproj_test.exe

# Project files for Scout_test
SRC_Scout = Scout_test.cpp ScoutAlien.cpp Player.cpp Enemy.cpp Asteroids.cpp PlayerProj.cpp Projectiles.cpp
OBJ_Scout = $(SRC_Scout:.cpp=.o)
EXEC_Scout = Scout_test.exe

# Default target
all: $(EXEC_PL) $(EXEC_ASTER) $(EXEC_PLproj) $(EXEC_Scout)

# Link the executable for PL_test
$(EXEC_PL): $(OBJ_PL)
	$(CXX) -o $(EXEC_PL) $(OBJ_PL) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Link the executable for Aster_test
$(EXEC_ASTER): $(OBJ_ASTER)
	$(CXX) -o $(EXEC_ASTER) $(OBJ_ASTER) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Link the executable for PLproj_test
$(EXEC_PLproj): $(OBJ_PLproj)
	$(CXX) -o $(EXEC_PLproj) $(OBJ_PLproj) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Link the executable for Scout_test
$(EXEC_Scout): $(OBJ_Scout)
	$(CXX) -o $(EXEC_Scout) $(OBJ_Scout) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Compile C++ source files to object files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean up build artifacts
clean:
ifeq ($(UNAME_S),Linux)
	rm -f *.o $(EXEC_PL) $(EXEC_ASTER) $(EXEC_PLproj) $(EXEC_Scout)
else
	del /q *.o *.exe
endif

.PHONY: all clean
