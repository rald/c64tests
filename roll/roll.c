#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void randomize() {
	srand(time(NULL));
}

void roll(int *d1,int *d2) {
	*d1=rand()%6+1;
	*d2=rand()%6+1;
}

int main(void) {
	int i,d1,d2;

	randomize();
	clrscr();
	for(i=0;i<10;i++) {
		roll(&d1,&d2);
		printf("%d %d\n",d1,d2);
	}

	return 0;
}
