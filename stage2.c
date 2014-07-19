#include <stdio.h>
#include <stdlib.h>
#include "stage2.h"

void stage2(FILE *input, FILE *output)
{
	enum { S_NONE, S_LINE_COMMENT, S_COMMENT, S_STRING } state = S_NONE;
	int c, d, backslash = 0;
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
				} else if (c == '"')
					state = S_STRING;
				putc(c, output);
				break;
			case S_STRING:
				if (backslash % 2 == 0 && c == '"')
					state = S_NONE;
				if (c == '\\')
					backslash++;
				else
					backslash = 0;
				putc(c, output);
				break;
			case S_LINE_COMMENT:
				if (c == '\n') {
					state = S_NONE;
					putc(c, output);
				}
				break;
			case S_COMMENT:
				if (c == '*' && getc(input) == '/')
						state = S_NONE;
		}
	}
}
