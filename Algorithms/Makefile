##
# Build Elephant

all: elephant
	./elephant

elephant: $(wildcard *.cpp)
	g++ -std=c++0x $^ -o elephant

clean:
	rm -f *.o *.exe