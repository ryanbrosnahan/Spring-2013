##
# Build hello

all: test
	./test

main: $(wildcard *.cpp)
	g++ -std=c++0x $^ -o main

clean:
	rm -f *.o *.exe
