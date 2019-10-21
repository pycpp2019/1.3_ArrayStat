FLAGS=-std=c++11 -I. -lpthread -pthread

.PHONY: all test run-test run-scal-test run-vec-test

all: test

test: scal_test vec_test


scal-test: out/scal_run

out/scal_run: out/scal_test.o out/ArrayStat.o
	g++ ${FLAGS} $^ -o $@

out/scal_test.o: test/scal_test.cpp test/*.hh *.h
	g++ ${FLAGS} -c $< -o $@

out/ArrayStat.o: ArrayStat.cpp ArrayStat.h
	g++ ${FLAGS} -c $< -o $@

run-scal-test: out/scal_run
	./$<


out/vec_run: out/vec_test.o out/VecArrayStat.o
	g++ ${FLAGS} $^ -o $@

out/vec_test.o: test/vec_test.cpp test/*.hh *.h
	g++ ${FLAGS} -c $< -o $@

out/VecArrayStat.o: VecArrayStat.cpp VecArrayStat.h
	g++ ${FLAGS} -c $< -o $@

run-vec-test: out/vec_run
	./$<


run-test: run-scal-test run-vec-test
