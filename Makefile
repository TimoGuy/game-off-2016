# Files to compile
OBJS = MainDriver.cpp res/Resources.cpp events/input/Input.cpp events/input/KeyboardInput.cpp

# Compiler that we're using
CC = g++

# Compiler flags
COMPILER_FLAGS = -w

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image

# Name of executable
OBJ_NAME = hello_world_SDL2

# Compile it!
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
