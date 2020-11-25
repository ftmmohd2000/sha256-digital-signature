run: output
	./output

output: main.o rsa.o sha.o
	g++ -I../include -I.  -g -O2 -std=c++11 -pthread -march=native main.o rsa.o sha.o /usr/local/lib/libntl.a -lgmp -o output

main.o: main.cpp
	g++ -c main.cpp

rsa.o: rsa.cpp
	g++ -c  rsa.cpp

sha.o: sha.cpp
	g++ -c  sha.cpp

clean:
	rm -rf output *.o
	clear
