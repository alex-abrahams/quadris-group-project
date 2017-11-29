CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla -Ih
EXEC = quadris
OBJECTS = cc/main.o cc/cmdparser.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
