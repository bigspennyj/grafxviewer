CC=g++
CFLAGS=-W -Wall -pedantic
LFLAGS=-lSDL2 -lSDL2_image
SRCDIR=src
BINDIR=bin

_SOURCES=main.cpp io.cpp app.cpp component.cpp
SOURCES=$(patsubst %,$(SRCDIR)/%,$(_SOURCES))
_OBJS=$(_SOURCES:.cpp=.o)
OBJS=$(patsubst %,$(BINDIR)/%,$(_OBJS))

EXECUTABLE=$(BINDIR)/app

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $@

$(BINDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
