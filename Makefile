vpath %.c src
vpath % build

c3d: src curses3d.c
	gcc src/curses3d.c -lm -lncurses -o build/curses3d

.PHONY: test
test: c3d
	build/curses3d
