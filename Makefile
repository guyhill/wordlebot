CC = gcc

wordlebot.exe: wordlebot.o solver.o
	$(CC) -o $@ $^

analyzer.exe: analyzer.o solver.o
	$(CC) -o $@ $^

.PHONY: clean
clean:
	-del /q /f *.o wordlebot.exe > NUL 2> NUL
