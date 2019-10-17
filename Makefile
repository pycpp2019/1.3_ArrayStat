FLAGS=-std=c++11 -I. -pthread -lpthread

.PHONY: all test

all: test

test: out/run

out/run: out/main.o out/ArrayStat.o
	g++ ${FLAGS} $^ -o $@

out/main.o: test/main.cpp test/*.hh *.h
	g++ ${FLAGS} -c $< -o $@

out/ArrayStat.o: ArrayStat.cpp ArrayStat.h
	g++ ${FLAGS} -c $< -o $@

run-test: test
	./out/run
