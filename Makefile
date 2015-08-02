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
LDLIBS = -lpopt -lboost_system
INCLUDE = -I./include -I/usr/include -I/usr/local/include
RM	= rm -rf

OUTDIR		= ./bin/
SRC_FILES = ./cbengine/engine.cpp
INCLUDE_FILES = ./include/
BASE_FILES = ./base/
O_FILES	= $(SRC_FILES:%.cpp=%.o)

# Make COSBB Engine
cossb: $(OUTDIR)engine.o $(OUTDIR)compmanager.o $(OUTDIR)sysmanager.o $(OUTDIR)broker.o $(OUTDIR)config.o $(OUTDIR)icomponent.o $(OUTDIR)instance.o $(OUTDIR)pid.o  
	$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ $(LDLIBS)
	
# Make COSBB Engine Daemon
cossbd: $(OUTDIR)engined.o $(OUTDIR)compmanager.o $(OUTDIR)broker.o $(OUTDIR)config.o $(OUTDIR)icomponent.o
	$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ $(LDLIBS)

#Make libcbcore.so	
#libcbcore.so: $(OUTDIR)cbcore.o 
#	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
	
$(OUTDIR)compmanager.o: $(INCLUDE_FILES)compmanager.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)sysmanager.o: $(INCLUDE_FILES)sysmanager.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)broker.o: $(INCLUDE_FILES)broker.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)config.o: $(INCLUDE_FILES)config.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

$(OUTDIR)icomponent.o: $(INCLUDE_FILES)interface/icomponent.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)instance.o: $(INCLUDE_FILES)instance.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)pid.o: $(INCLUDE_FILES)util/pid.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)sha1.o: $(INCLUDE_FILES)util/sha1.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	

# compile cossb engine
$(OUTDIR)engine.o: ./src/engine.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)engined.o: ./src/engined.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	

# make all
all: cossb cossbd

# Clean
clean: 
	$(RM) $(OUTDIR)*.o $(OUTDIR)cossb $(OUTDIR)cossbd $(OUTDIR)*.so