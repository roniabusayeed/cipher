CXX=clang
CXXFLAGS=-Wall
OUT=cipher

all: main.o
	${CXX} ${CXXFLAGS} main.o -o cipher

main.o: main.c
	${CXX} ${CXXFLAGS} -c main.c

clean:
	rm -rf *.o ${OUT} 
