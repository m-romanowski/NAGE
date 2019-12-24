# --
# NAGE Makefile - static library
# --

# Project build
BUILD_PATH = ./build
BUILD_NAME = NAGE.a
OUTPUT = $(BUILD_PATH)/$(BUILD_NAME)

# Compiler settings
CXX = g++
CXX_VERSION = c++17

CXXFLAGS += -std=$(CXX_VERSION) -Wall -Wextra -pedantic-errors
LDFLAGS = -L$(GLFW_PATH)/lib -lglfw3 -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread -ldl

# GLFW
GLFW_PATH = ./lib/glfw

# GLAD
GLAD_PATH = ./lib/glad

# OS detection
ifeq ($(OS),Windows_NT)
	CXXFLAGS += -D WIN32
	DETECTED_OS = WINDOWS
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
	CXXFLAGS += -D AMD64
	else
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	CXXFLAGS += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	CXXFLAGS += -D IA32
	endif
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
	CXXFLAGS += -D LINUX
		DETECTED_OS = LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
	CXXFLAGS += -D OSX
		DETECTED_OS = OSX
	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
	CXXFLAGS += -D AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
	CXXFLAGS += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
	CXXFLAGS += -D ARM
	endif
endif

# Include path
INCLUDE = $(GLFW_PATH)/include $(GLAD_PATH) ./lib ./src
INCLUDE_PARAMS = $(foreach d, $(INCLUDE), -I$d)

# Project
SOURCES = $(GLAD_PATH)/glad.c # Append glad source file
SOURCES = $(shell find -path './src/common/*.cpp')
SOURCES += $(shell find -path './src/components/*.cpp')
SOURCES += $(shell find -path './src/engine/*.cpp')
SOURCES += $(shell find -path './src/game/*.cpp')
OBJS = $(SOURCES:.cpp=.o)

.cpp.o: $(SOURCES)
	$(CXX) $(INCLUDE_PARAMS) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

$(OUTPUT): $(OBJS)
	ar rcs $(OUTPUT) $(OBJS)

.PHONY: clean cleanall

clean:
	rm $(OBJS)

cleanall:
	rm $(OUTPUT) $(OBJS)
