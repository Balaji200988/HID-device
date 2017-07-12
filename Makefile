###########################################
# Simple Makefile for HIDAPI test program
#
# Alan Ott
# Signal 11 Software
# 2010-06-01
###########################################

all: main 

CC       ?= gcc
CFLAGS   ?= -Wall -g

#CXX      ?= g++
#CXXFLAGS ?= -Wall -g

CLIBOBJ   = hid-libusb.o
CMAINOBJ  = main.o
OBJS      = $(CLIBOBJ) $(CMAINOBJ)
LIBS      = `pkg-config libusb-1.0 libudev --libs` 
INCLUDES ?= -I../hidapi `pkg-config libusb-1.0 --cflags`


main: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LIBS) -o main

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJS) main

.PHONY: clean
