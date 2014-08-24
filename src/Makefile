COMPILER = clang++
OPTIONS = -std=c++0x -g -Wall

CPPFLAGS += -isystem ./include

GTEST_HEADERS =  include/gtest/*.h \
                 include/gtest/internal/*.h

LINK_TARGET = bin/jpoker.exe

OBJS =  \
 jout.o \
 configurator.o \
 hand.o \
 humanai.o \
 stockai.o \
 card.o \
 player.o \
 players.o \
 deck.o \
 poker.o \
 
TESTS = \
players_test.o \
hand_test.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all : bin/jpoker.exe bin/tests.exe
	echo "done!"

bin/jpoker.exe : $(OBJS) main.o
	$(COMPILER) $(OPTIONS) $(CPPFLAGS) -o $@ $^

bin/tests.exe : $(OBJS) $(TESTS) tests.o
	$(COMPILER) $(OPTIONS) $(CPPFLAGS) -o $@ $^ lib/gtest_main.a -pthread

%.o : %.cpp
	$(COMPILER) $(OPTIONS) $(CPPFLAGS) -o $@ -c $<

configurator.o : configurator.h
hand.o : hand.h 
humanai.o : humanai.h
stockai.o : stockai.h
poker.h: enums.h
player.o: player.h
players.o: players.h
card.o: card.h
player.o : player.h
deck.o : deck.h
poker.o : poker.h
hand_test.o: hand.o

clean : 
	rm *.o
