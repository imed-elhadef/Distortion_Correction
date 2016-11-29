# ----------------------------------------------------------------------------
# Makefile for building application
#
# Copyright 2016 Imed Elhadef imed.elhadef@arcangel.fr
#

 # the compiler: g++ for C++ program or gcc for C program
  CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  #  -std=c++11 for C++11 compilation
  CFLAGS  = -g -Wall -std=c++11

  #openCV flag
  OPENCV = `pkg-config opencv --cflags --libs`

  # the build target executable:
  TARGET = correction

  all: $(TARGET)

  $(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(OPENCV)

  clean:
	$(RM) $(TARGET)
