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

COBJS     = hid.o
CPPOBJS   = main.o
OBJS      = $(COBJS) $(CPPOBJS)
LIBS      = `pkg-config libusb-1.0 libudev --libs`
INCLUDES ?= -I../hidapi `pkg-config libusb-1.0 --cflags`


main: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LIBS) -o main
# gcc -Wall -g  hid.o main.o `pkg-config libusb-1.0 libudev --libs` -o main
 

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
# gcc -Wall -g -c -I../hidapi `pkg-config libusb-1.0 --cflags` hid.c -o hid.o 

$(CPPOBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
# gcc -Wall -g -c -I../hidapi `pkg-config libusb-1.0 --cflags` main.c -o main.o 

clean:
	rm -f $(OBJS) main

.PHONY: clean
