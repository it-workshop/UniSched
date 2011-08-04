NAME=raspisator

CXX=g++
CXXFLAGS=-Wall -O2 -g -I.

RM=rm
INSTALL=install

BIN=$(NAME)
OBJECTS=$(shell echo *.cc | sed 's/\.cc/.o/g')

PREFIX=/usr
BINDIR=$(PREFIX)/bin

default: all

all: $(BIN)

$(BIN):$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJECTS)
	$(RM) $(BIN)

install: $(BIN)
	$(INSTALL) $(BIN) $(BINDIR)/$(BIN)

