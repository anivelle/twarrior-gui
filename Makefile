
FLAGS = `pkg-config --cflags --libs gtk4`
all:
	gcc $(FLAGS) -o hello-world hello-world.c -v -Wall

example4:
	gcc $(FLAGS) -o example-4 example-4.c -v -Wall
