################################
# COSSB CMakeList.txt
################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(cossb)

#COSSB version
SET(COSSB_VERSION_MAJOR	0)
SET(COSSB_VERSION_MINOR	0)
SET(COSSB_VERSION_REV	1)

ADD_EXECUTABLE(cossb engine.cxx)
ADD_EXECUTABLE(cossbd engined.cxx)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(support)
ADD_SUBDIRECTORY(examples)