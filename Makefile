CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = window.o graphicsdisplay.o cell.o textdisplay.o grid.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = a4q4

${EXEC} : ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

.PHONY : clean

clean :
		rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
