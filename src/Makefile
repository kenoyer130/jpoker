COMPILER = clang++
OPTIONS = -std=c++0x

LINK_TARGET = bin/jpoker.exe

OBJS =  \
 table.o \
 gamestate.o \
 poker.o \
 main.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all : $(LINK_TARGET)
	echo "done!"

$(LINK_TARGET) : $(OBJS)
	$(COMPILER) $(OPTIONS) -g -o $@ $^

%.o : %.cpp
	$(COMPILER) $(OPTIONS) -g -o $@ -c $<

poker.h: enums.h
card.o: card.h
player.o : player.h
table.o : table.h
poker.o : poker.h | gamestate.o


:clean
	rm *.o




