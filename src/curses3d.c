#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


struct Point {
	float y;
	float x;
};

void display_point(struct Point p) {
	mvaddch(round(p.y), round(p.x), ' '|A_REVERSE);
}

void erase_point(struct Point p) {
	mvaddch(round(p.y), round(p.x), ' ');
}

void draw_line(struct Point p0, struct Point p1, int erase) {
	/* Implementation of Bresenham's line-drawing algorithm */
	int dx = abs(p1.x - p0.x), sx = p0.x < p1.x ? 1 : -1;
	int dy = -abs(p1.y - p0.y), sy = p0.y < p1.y ? 1 : -1;
	int err = dx + dy, e2;

	for(;;) {
		if(erase == 0) {
			display_point(p0);
		} else {
			erase_point(p0);
		}
		if(p0.x == p1.x && p0.y == p1.y) break;
		e2 = 2 * err;
		if(e2 >= dy) { err += dy; p0.x += sx; }
		if(e2 <= dx) { err += dx; p0.y += sy; }
	}
}

struct Point rotate_point(struct Point p0, float theta_an) {
	struct Point p1;
	p1.x = (p0.x * cos(theta_an)) - (p0.y * sin(theta_an));
	p1.y = (p0.x * sin(theta_an)) + (p0.y * cos(theta_an));
	
	return p1;
}

int main() {
	initscr();

	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	/* Check the current screen size so we can see what we're working with */
	int y_max;
	int x_max;
	getmaxyx(stdscr, y_max, x_max);
	int y_mid = round(y_max / 2);
	int x_mid = round(x_max / 2);
	
	struct Point p1;
	p1.x = x_mid - 10;
	p1.y = y_mid - 10;
	
	struct Point midpoint;
	midpoint.x = x_mid;
	midpoint.y = y_mid;

	float theta_angle = 0.15;
	do {
		draw_line(p1, midpoint, 0);
		refresh();
		draw_line(p1, midpoint, 1);

		p1.x = p1.x - x_mid;
		p1.y = p1.y - y_mid;
		p1 = rotate_point(p1, theta_angle);
		p1.x = round(p1.x) + x_mid;
		p1.y = round(p1.y) + y_mid;
		usleep(20000);
	} while(1);

	endwin();

	return 0;
}
