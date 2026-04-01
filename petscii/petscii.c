#include <stdio.h>
#include <conio.h>
#include <ctype.h>

int main(void) {
	int i;

	clrscr();
	for(i=65;i<256;i++) {
		if(isprint(i)) printf("%3d%c \t",i,i);
	}

	return 0;
}
