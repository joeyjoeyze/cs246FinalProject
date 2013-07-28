CXX = g++
CXXFLAGS = -Wall -g -MMD
OBJECTS = main.o block.o board.o cell.o game.o randomblock.o window.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY : clean

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
