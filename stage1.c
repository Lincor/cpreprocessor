#include <stdio.h>
#include "stage1.h"

void stage1(FILE *input, FILE *output)
{
	int c, d;
	while ((c = getc(input)) != EOF) {
		if (c == '\\') {
			if ((d = getc(input)) == '\n')
				continue;
			else
				ungetc(d, input);
		}
		putc(c, output);
	}
}
