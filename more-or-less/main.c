// main entry point
//

extern int compare(int val, int guess);

#include <stdio.h>

int main() {
	int val;
	
	time_t t;
	srand((unsigned) time(&t));

	val = rand() % 1000;
	int guess;
	printf("Enter a number : ");
	scanf("%d", &guess);
	int s = 0;
	while ((s=compare(val, guess)) != 0) {
			printf("Nop ! ");
			if (s == -1) {
					printf("It's greater !\n");
			} else {
					printf("It's smaller !\n");
			}
			printf("Enter a number : ");
			scanf("%d", &guess);
	}
}
