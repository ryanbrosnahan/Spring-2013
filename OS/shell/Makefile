##
# Build hello

all: main
	./main

main: $(wildcard *.cpp)
	g++ -std=c++0x $^ -o main

clean:
	rm -f *.o *.exe