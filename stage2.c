#include <stdio.h>
#include "stage2.h"

void stage2(FILE *input, FILE *output)
{
	enum { S_NONE, S_LINE_COMMENT, S_COMMENT } state = S_NONE;
	int c, d;
	while ((c = getc(input)) != EOF) {
		switch (state) {
			case S_NONE:
				if (c == '/') {
					if ((d = getc(input)) == '/') {
						state = S_LINE_COMMENT;
						break;
					} else if (d == '*') {
						state = S_COMMENT;
						break;
					} else
						ungetc(d, input);
				}
				putc(c, output);
				break;
			case S_LINE_COMMENT:
				if (c == '\n')
					state = S_NONE;
				break;
			case S_COMMENT:
				if (c == '*' && getc(input) == '/')
						state = S_NONE;
		}
	}
}
