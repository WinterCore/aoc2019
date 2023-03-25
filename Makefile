CFLAGS = -Wall -Wextra -pedantic -std=c11 -ggdb

.PHONY: clean all day01

all: day01/day01.out
	
aids.o: aids.h aids.c
	cc $(CFLAGS) -c aids.c

day01/day01.out: day01/main.c day01/exampleinput day01/input aids.o
	cc $(CFLAGS) -o ./day01/day01.out day01/main.c aids.o


day01: day01/day01.out
	cd day01 && ./day01.out


clean:
	rm -rf ./d01.out

