NAME=raspisator

CXX=g++
CXXFLAGS=-Wall -O2 -g -I. -Werror

RM=git rm
INSTALL=install

BIN=$(NAME)
OBJECTS=$(shell echo *.cpp | sed 's/\.cpp/.o/g')

PREFIX=/usr
BINDIR=$(PREFIX)/bin

default: all

all: $(BIN)

$(BIN):$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJECTS) $(BIN)

install: $(BIN)
	$(INSTALL) $(BIN) $(BINDIR)/$(BIN)

