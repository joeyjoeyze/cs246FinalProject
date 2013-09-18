CXX = g++
CXXFLAGS = -Wall -g -MMD -L/usr/X11R6/lib -lX11
OBJECTS = main.o block.o board.o cell.o game.o randomblock.o window.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY : clean

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
