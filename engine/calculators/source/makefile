-include ../../../makefile.common

INCLUDE=-I../include -I../../../world/include -I../../../world/tiles/include -I../../include -I../../../../gtest-1.6.0/include -I../../../include -I ../../../display/include

all: calculators

calculators: SkillsCalculator.o ResistancesCalculator.o

SkillsCalculator.o: SkillsCalculator.cpp ../include/SkillsCalculator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) SkillsCalculator.cpp

ResistancesCalculator.o: ResistancesCalculator.cpp ../include/ResistancesCalculator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) ResistancesCalculator.cpp

clean:
	rm -rf *.o
