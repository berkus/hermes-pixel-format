
CXX=g++
CFLAGS=-I../src -Wall -O 
HERMES_PATH=../src/.libs
LINK_OPTS=-L$(HERMES_PATH) -Wl,-rpath,$(HERMES_PATH) -lHermes -L/usr/X11R6/lib -lX11 -lXext

ALLFILES = Test TestPalette Request CheckLeaks Efence

all: $(ALLFILES)

Test: Test.o
	gcc Test.o $(LINK_OPTS) -o $@

TestPalette: TestPalette.o
	gcc TestPalette.o $(LINK_OPTS) -o $@ -lm

Request: Request.o
	gcc Request.o $(LINK_OPTS) -o $@

CheckLeaks: CheckLeaks.o
	gcc CheckLeaks.o $(LINK_OPTS) -o $@

Efence: Efence.o
	g++ Efence.o $(LINK_OPTS)  -lefence -o $@

.c.o:
	gcc $(CFLAGS) -c $<

.cc.o:
	g++ $(CFLAGS) -c $<

clean:
	rm -f *.o

distclean: clean
	rm -f $(ALLFILES)

