#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

static double cx = 0, cy = 0;
static struct matrix * edges;


void hilbert(double x, double y, double xi, double xj, double yi, double yj, double n){


	if (n <= 0){
		double nx = x + (xi + yi)/2;
		double ny = y + (xj + yj)/2;
		add_edge(edges, cx, cy, 0, nx, ny, 0);

		cx = nx;
		cy = ny;
	}
	else
	{
		hilbert(x,           y,           yi/2, yj/2,  xi/2,  xj/2, n-1);
		hilbert(x+xi/2,      y+xj/2 ,     xi/2, xj/2,  yi/2,  yj/2, n-1);
		hilbert(x+xi/2+yi/2, y+xj/2+yj/2, xi/2, xj/2,  yi/2,  yj/2, n-1);
		hilbert(x+xi/2+yi,   y+xj/2+yj,  -yi/2,-yj/2, -xi/2, -xj/2, n-1);
	}

}

int main() {

	screen s;
    color c;

    c.red = 255;
    c.blue = 0;
    c.green = 0;

	struct matrix *a = new_matrix(4, 4);
	struct matrix *b = new_matrix(4, 4);

	for(int i = 1; i < 3; i++) add_edge(a, i, i, i, i+1, i+1, i+1);
	for(int i = 0; i < 6; i++) add_edge(b, i, i, i, i+1, i+1, i+1);

	clear_screen(s);

    printf("Matrix A\n");
	print_matrix(a);
    printf("Matrix B\n");
	print_matrix(b);

	matrix_mult(a, b);

    printf("Matrix AB\n");
	print_matrix(b);

	struct matrix *id = new_matrix(4, 4);
	ident(id);

	printf("Identity matrix\n");
	print_matrix(id);


	edges = new_matrix(4, 1);
	hilbert (0, 0, 10000, 0, 0, 10000, 10);



	draw_lines(edges, s, c);

    save_extension(s, "matrix.png");
	free_matrix(a);
	free_matrix(b);
	free_matrix(edges);
	free_matrix(id);
}
