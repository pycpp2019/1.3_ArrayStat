FLAGS=-std=c++11 -I.

.PHONY: all test

all: test

test: out/run

out/run: out/main.o
	g++ ${FLAGS} $^ -o $@

out/main.o: test/main.cpp test/*.hh *.h
	g++ ${FLAGS} -c $< -o $@

run-test: test
	./out/run
