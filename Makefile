CC=g++
CFLAGS= -c -Wall -g
LDFLAGS=
SOURCES= Sudoku.cpp Sell.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sudoku

sudoku: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

clear:
	rm -rf $(OBJECTS) $(EXECUTABLE)

$(OBJECTS) :
	$(CC) $(CFLAGS) $(SOURCES) 

	