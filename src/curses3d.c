#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

void draw_line(int y0, int x0, int y1, int x1) {
	/* Implementation of Bresenham's line-drawing algorithm */
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	for(;;) {
		mvaddch(y0, x0, ' '|A_REVERSE);
		if(x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if(e2 >= dy) { err += dy; x0 += sx; }
		if(e2 <= dx) { err += dx; y0 += sy; }
	}
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

	int scale = 15;
	float p1[] = {y_mid - scale, x_mid - scale};
	int p2[] = {y_mid - scale, x_mid + scale};
	int p3[] = {y_mid + scale, x_mid - scale};
	int p4[] = {y_mid + scale, x_mid + scale};

	float angle = 0.05;
	float st = sin(angle);
	float ct = cos(angle);
	int p1_initialy = y_mid - scale;
	int p1_initialx = x_mid - scale;
	do {
		/*
		draw_line(p1[0], p1[1], p2[0], p2[1]);
		draw_line(p1[0], p1[1], p3[0], p3[1]);
		draw_line(p2[0], p2[1], p4[0], p4[1]);
		draw_line(p3[0], p3[1], p4[0], p4[1]);
		*/
		mvaddch(p1[0], p1[1], '1');
		/*
		mvaddch(p2[0], p2[1], '2');
		mvaddch(p3[0], p3[1], '3');
		mvaddch(p4[0], p4[1], '4');
		*/

		mvaddch(0, 0, 'a');
		p1[0] = (p1[0] - p1_initialy) + 3;
		p1[1] = (p1[1] - p1_initialx) + 3;
		p1[0] = (p1[1] * st) + (p1[0] * ct);
		p1[1] = (p1[1] * ct) - (p1[0] * st);
		p1[0] = p1[0] + p1_initialy - 3;
		p1[1] = p1[1] + p1_initialx - 3;
		mvprintw(1, 0, "p1[0] is now %4.3f", p1[0]);
		mvprintw(2, 0, "p1[1] is now %4.3f", p1[1]);

		/*
		mvaddch(0, 0, 'b');
		p2[0] = round((p2[1] * st) + (p2[0] * ct));
		p2[1] = round((p2[1] * ct) - (p2[0] * st));

		mvaddch(0, 0, 'c');
		p3[0] = round((p3[1] * st) + (p3[0] * ct));
		p3[1] = round((p3[1] * ct) - (p3[0] * st));

		mvaddch(0, 0, 'd');
		p4[0] = round((p4[1] * st) + (p4[0] * ct));
		p4[1] = round((p4[1] * ct) - (p4[0] * st));
		*/
		mvprintw(0, 0, "Refreshing");
		refresh();
		usleep(90000);

	} while(1);
	endwin();

	return 0;
}
