// Game of life
//

#include <stdio.h>


extern char *step(int h, int w, char *tbl);

int cmp(char* tbl, char* out, int length) {
	if (length == 0) return 1;
	if (tbl != out) return 0;
	return cmp(++tbl, ++out, --length);
}

void print_grid(int h, int w, char *tbl, int step) {
	printf("Step %d : \n", step);
	for (int i=0; i<h; i++) {
		for (int j=0; j<w; j++) {
			printf("%d ", (int)tbl[i*w+j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	int h = 4, w = 4;
	char tbl[16] = {0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0};
	char out[16] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1};
	print_grid(h, w, tbl, 0);
	for (int i=0; i<4; i++) {
		step(h, w, tbl);
		print_grid(h, w, tbl, i+1);
	}
	if (cmp(tbl, out, 16) != 0) {
		printf("You have failed the test ! Go try again, you can do it !\n");
	} else {
		printf("Great ! You did it ! If you want, go look at the C code if you want to test you program on other data !\n");
	}
	return 0;
}
