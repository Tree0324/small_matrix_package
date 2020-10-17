
test_for_matrix: test_matrix_fun.o matrix_fun.o
	g++ -o test_matrix_fun test_matrix_fun.o matrix_fun.o

matrix_fun.o: matrix_fun.cpp matrix_fun.h
	g++ -c matrix_fun.cpp

test_matrix_fun.o: test_matrix_fun.cpp
	g++ -c test_matrix_fun.cpp

clean:
	del test_matrix_fun *.o, *.exe