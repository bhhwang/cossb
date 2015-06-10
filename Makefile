# Makefile for all component project

# compiler flags
#	-g	--Enable debugging
#	-Wall	--Turn on all warnings
#	-D_USE_FIXED_PROTOTYPES_
#	--Force the compiler to use the correct headers
#	-ansi	--Don't use GNU ext; do use ansi standard.

CC = gcc
CXX = g++
CXXFLAGS = -O3 -g3 -fPIC -Wall -std=c++11 -D__cplusplus=201103L
CCFLAGS = $(CXXFLAGS)
LDFLAGS = -Wl,--export-dynamic
LDLIBS = 
INCLUDE = -I./include -I/usr/include -I/usr/local/include
RM	= rm -rf
TARGET = engine

OUTDIR		= ./bin/
SRC_FILES = ./cbengine/engine.cpp
O_FILES	= $(SRC_FILES:%.cpp=%.o)

all: $(TARGET)

# Make COSBB Engine
engine: $(OUTDIR)engine.o 
	$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^


# compile cossb engine
$(OUTDIR)engine.o: ./cbengine/engine.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	

# Clean
clean: 
	$(RM) $(OUTDIR)*.o $(OUTDIR)engine