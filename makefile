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
	gcc main.c -o main -lm -ansi
debug:
	make clean
	gcc main.c -o main -g -lm
	gdb main
clean:
	rm -f main
	@echo Cleaned all compiled programs
