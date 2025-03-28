.DEFAULT_GOAL := generate
say_hello:
	@echo "Hello World"
run:
	make clean
	make generate
	clear
	./main
generate:
	make clean
	gcc main.c -o main -lm -ansi -lncurses
debug:
	make clean
	gcc main.c -o main -g -lm -ansi -lncurses
	gdb main
clean:
	rm -f main
	@echo Cleaned all compiled programs
