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
LDLIBS = -lpopt -lboost_system -lboost_thread -ltinyxml2 -ldl
LDLIBS_TEST = -lpopt -lboost_system -lboost_thread -ltinyxml2 -ldl -lgtest -lpthread
INCLUDE = -I./include -I/usr/include -I/usr/local/include
RM	= rm -rf

OUTDIR		= ./bin/
SRC_FILES = ./cbengine/engine.cpp
INCLUDE_FILES = ./include/
COMPONENT_FILES = ./support/
EXAMPLE_FILES = ./examples/
LIB_FILES = ./lib/
TEST_FILES = ./test/
SOURCE_FILES = ./src/
BASE_FILES = ./base/


# Make COSBB Engine
cossb: $(OUTDIR)engine.o $(OUTDIR)compmanager.o $(OUTDIR)sysmanager.o $(OUTDIR)broker.o $(OUTDIR)configreader.o $(OUTDIR)instance.o \
		$(OUTDIR)pid.o $(OUTDIR)auth.o $(OUTDIR)driver.o $(OUTDIR)xmlprofile.o $(OUTDIR)logger.o $(OUTDIR)localtime.o   
		$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ $(LDLIBS)
	
# Make COSBB Engine Daemon
cossbd: $(OUTDIR)engined.o $(OUTDIR)compmanager.o $(OUTDIR)broker.o $(OUTDIR)config.o
		$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ $(LDLIBS)
	
cossb_test: $(OUTDIR)engine_test.o $(OUTDIR)sysmanager_test.o \
			$(OUTDIR)compmanager.o $(OUTDIR)sysmanager.o $(OUTDIR)broker.o $(OUTDIR)configreader.o $(OUTDIR)instance.o \
			$(OUTDIR)pid.o $(OUTDIR)auth.o $(OUTDIR)driver.o $(OUTDIR)xmlprofile.o $(OUTDIR)logger.o $(OUTDIR)localtime.o
			$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ $(LDLIBS_TEST)	

#Make libcbcore.so	
libcblog.so:	$(OUTDIR)cblog.o $(OUTDIR)localtime.o 
				$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
	
#Make libcbmdns.so	
libcbmdns.so:	$(OUTDIR)cbmdns.o 
				$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
	
#example components
helloworld.comp: $(OUTDIR)helloworld.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)helloworld.o: $(EXAMPLE_FILES)helloworld/helloworld.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

#================== compserial component
compserial.comp: $(OUTDIR)compserial.o $(OUTDIR)libserial.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)compserial.o: $(COMPONENT_FILES)compserial/compserial.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@	
$(OUTDIR)libserial.o: $(COMPONENT_FILES)compserial/libserial.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

#================== compmdns component
compmdns.comp: $(OUTDIR)compmdns.o
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)compmdns.o: $(COMPONENT_FILES)compmdns/compmdns.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@		
	
#================== messagepub component
messagepub.comp: $(OUTDIR)messagepub.o
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)messagepub.o: $(EXAMPLE_FILES)messagepub/messagepub.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@			
	
$(OUTDIR)compmanager.o: $(INCLUDE_FILES)compmanager.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)sysmanager.o: $(INCLUDE_FILES)sysmanager.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)broker.o: $(INCLUDE_FILES)broker.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)driver.o: $(INCLUDE_FILES)driver.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)configreader.o: $(INCLUDE_FILES)base/configreader.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)logger.o: $(INCLUDE_FILES)logger.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)localtime.o: $(INCLUDE_FILES)util/localtime.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)xmlprofile.o: $(INCLUDE_FILES)xmlprofile.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
		
$(OUTDIR)auth.o: $(INCLUDE_FILES)auth/auth.cpp
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

#libraries	
$(OUTDIR)cblog.o: $(LIB_FILES)libcblog/cblog.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)cbmdns.o: $(LIB_FILES)libcbmdns/cbmdns.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
#for google test
$(OUTDIR)engine_test.o: $(TEST_FILES)engine_test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
$(OUTDIR)sysmanager_test.o: $(TEST_FILES)sysmanager_test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@		

# make all
all: cossb libcblog.so helloworld.comp compserial.comp compmdns.comp messagepub.comp

base: cossb

example : helloworld.comp

component: compserial.comp compmdns.comp messagepub.comp

test: cossb_test

# Clean
clean: 
	$(RM) $(OUTDIR)*.o $(OUTDIR)cossb $(OUTDIR)cossbd $(OUTDIR)*.so