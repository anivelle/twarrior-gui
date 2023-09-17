
FLAGS = `pkg-config --cflags --libs gtk4`
all:
	gcc $(FLAGS) -o hello-world hello-world.c -v -Wall
