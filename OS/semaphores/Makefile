##
# Build hello

all: smokers
	./smokers

smokers: smokers.c
	gcc smokers.c -lrt -std=gnu99 -pthread -o smokers

clean:
	rm -f *.o *.exe smokers

