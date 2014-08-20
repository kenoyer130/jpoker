COMPILER = clang++
OPTIONS = -std=c++0x -g -Wall

LINK_TARGET = bin/jpoker.exe

OBJS =  \
 configurator.o \
 hand.o \
 humanai.o \
 stockai.o \
 card.o \
 player.o \
 players.o \
 table.o \
 poker.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all : bin/jpoker.exe test/handtester.exe
	echo "done!"

bin/jpoker.exe : $(OBJS) main.o
	$(COMPILER) $(OPTIONS) -o $@ $^

test/handtester.exe : $(OBJS) rank_tester.o
	$(COMPILER) $(OPTIONS) -o $@ $^

%.o : %.cpp
	$(COMPILER) $(OPTIONS) -o $@ -c $<

rank_tester.o : rank_tester.h
configurator.o : configurator.h
hand.o : hand.h
humanai.o : humanai.h
stockai.o : stockai.h
poker.h: enums.h
player.o: player.h
players.o: players.h
card.o: card.h
player.o : player.h
table.o : table.h
poker.o : poker.h

clean : 
	rm *.o
