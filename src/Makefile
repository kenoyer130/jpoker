COMPILER = clang++
OPTIONS = -std=c++0x -g -Wall

LINK_TARGET = bin/jpoker.exe

OBJS =  \
 card.o \
 table.o \
 poker.o \
 main.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all : $(LINK_TARGET)
	echo "done!"

$(LINK_TARGET) : $(OBJS)
	$(COMPILER) $(OPTIONS) -o $@ $^

%.o : %.cpp
	$(COMPILER) $(OPTIONS) -o $@ -c $<

poker.h: enums.h
card.o: card.h
player.o : player.h
table.o : table.h | card.o
poker.o : poker.h


