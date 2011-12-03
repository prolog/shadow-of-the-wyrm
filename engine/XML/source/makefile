-include ../../../makefile.common

INCLUDE=-I../include -I../../../display/include -I../../../world/include -I../../include -I../../../../gtest-1.6.0/include -I../../../include

all: XML

XML: XMLClassesReader.o XMLConfigurationReader.o XMLDataStructures.o XMLFileReader.o XMLRacesReader.o XMLResistancesReader.o XMLSkillsReaders.o XMLTilesReader.o

XMLClassesReader.o: XMLClassesReader.cpp ../include/XMLClassesReader.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) XMLClassesReader.cpp

XMLConfigurationReader.o: XMLConfigurationReader.cpp ../include/XMLConfigurationReader.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) XMLConfigurationReader.cpp

XMLDataStructures.o: XMLDataStructures.cpp ../include/XMLDataStructures.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) XMLDataStructures.cpp

XMLFileReader.o: XMLFileReader.cpp ../include/XMLFileReader.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) XMLFileReader.cpp

XMLRacesReader.o: XMLRacesReader.cpp ../include/XMLRacesReader.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) XMLRacesReader.cpp

XMLResistancesReader.o: XMLResistancesReader.cpp ../include/XMLResistancesReader.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) XMLResistancesReader.cpp

XMLSkillsReaders.o: XMLSkillsReaders.cpp ../include/XMLSkillsReaders.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) XMLSkillsReaders.cpp

XMLTilesReader.o: XMLTilesReader.cpp ../include/XMLTilesReader.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) XMLTilesReader.cpp

clean:
	rm -rf *.o
