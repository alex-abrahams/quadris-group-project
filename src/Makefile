CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla -Ih
EXEC = quadris
OBJECTS = cc/level.o cc/utility.o cc/cmdparser.o cc/gamesingleton.o cc/tetrominoblock.o cc/abstracttetromino.o cc/tetrominofactory.o cc/gameoverexception.o cc/cell.o cc/board.o cc/textdisplay.o cc/main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
