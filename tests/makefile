CC=g++

output: Smatrix.o Smatrix_test.o
		g++ Smatrix.o Smatrix_test.o -o Smatrix_test

Smatrix.o: ../src/Smatrix.cpp
		g++ -c ../src/Smatrix.cpp

Smatrix_test.o: Smatrix_test.cpp
		g++ -c Smatrix_test.cpp

clean:
	rm -rf *.o Smatrix