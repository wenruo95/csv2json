#include<stdio.h>

struct Header {
	char [256][256];
	unsigned int len;
};

int main(void) {
	char in_filename[] = "input.csv";
	char out_filename[] = "output.json";

	for (int i = 0; header[i] != NULL; i++) {
		printf("%d :\t %s\n", i, header[i]);
	}
	return 0;
}
