rm MapTester.o
cd engine/source ; make mode=map
cd engine/generators/source ; make mode=map
cd world/source ; make mode=map
cd ~/jrcpp
make MapTester.o mode=map
