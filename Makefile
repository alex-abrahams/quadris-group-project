CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
EXEC = quadris
OBJECTS = main.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean: 
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
