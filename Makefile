CXX=clang++
CXXFLAGS=-Wall
OUT=cipher

all: main.o
	${CXX} ${CXXFLAGS} main.o -o cipher

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

clean:
	rm -rf *.o ${OUT} 
