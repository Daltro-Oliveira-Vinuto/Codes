/* Imprime na tela caracteres aleatorios */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void replicate(void) {
	int i;
	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	srand(time(NULL));

	for(i=0;i<1e3;i++) {
		printf("%c",alphabet[rand()%26]);

	}

}

int main(void) {

	while(1) {
		replicate();
		
	}
	return 0;
}