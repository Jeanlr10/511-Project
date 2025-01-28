.DEFAULT_GOAL := generate
say_hello:
	@echo "Hello World"
run:
	make clean
	make generate
	./main
generate:
	make clean
	gcc main.c -o main -lm
debug:
	make clean
	gcc main.c -o main -g -lm
clean:
	rm -f main
	@echo Cleaned all compiled programs
