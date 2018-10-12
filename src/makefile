BASEDIR	= ..

CC	=	g++
CXX	=	g++
CPPFLAGS = -Wall -Ofast -std=c++11 -I ${BASEDIR}/include
CFLAGS =
LDFLAGS =
LDLIBS =

GENERATED	=	main	#programas_outros

OBJETOS = exception.o quote.o stock.o individual.o population.o

all: main.cpp
	@g++ main.cpp exception.cpp quote.cpp stock.cpp individual.cpp population.cpp $(CPPFLAGS) -o run
	@mv run ../
	@echo "Done"

${OBJETOS}: exception.cpp quote.cpp stock.cpp individual.cpp population.cpp

clean:
	@echo "limpo"
	@rm ../run
