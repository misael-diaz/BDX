#!/usr/bin/make
#
# BDX						December 05, 2023
#
# source: src/spheroid/Makefile
# author: @misael-diaz
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
# Copyright (c) 2023 Misael Diaz-Maldonado
# This file is released under the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#

include make-inc

all: $(SPHEROID_OBJ)

$(SPHEROID_OBJ): $(HEADERS) $(SPHEROID_CXX)
	$(CXX) $(INC) $(CXXOPT) -c $(SPHEROID_CXX) -o $(SPHEROID_OBJ)

clean:
	/bin/rm -f *.obj
