#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "filestack.h"

#define INCLUDE "include/"

void handle_include(char *);

void stage3(FILE *input, FILE *output)
{
	char *s, *p;
	stack_push(input);
	while ((s = stack_get_line())) {
		p = s;
		while (isspace(*p)) p++;
		if (!strncmp("#include", p, 8))
			handle_include(p + 8);
		else
			fputs(s, output);
	}
}

char *include_path(char *, char);

void handle_include(char *include)
{
	FILE *f;
	char *filename, *path;
	char type;

	while (isspace(*include)) include++;

	type = *include;
	if (type != '<' && type != '"') {
		fprintf(stderr, "Invalid #include directive.\n");
		exit(1);
	}

	filename = ++include;
	while (*include && *include != '>' && *include != '"')
		include++;
	if ((type == '<' && *include != '>') ||
		(type == '"' && *include != '"')) {
		fprintf(stderr, "Invalid #include directive.\n");
		exit(1);
	}
	*include = '\0';

	path = include_path(filename, type);
	if (!(f = fopen(path, "r"))) {
		fprintf(stderr, "Can't open file '%s'.\n", path);
		exit(1);
	}
	stack_push(f);
}

char *strcat2(const char *, const char*);

char *include_path(char *filename, char type)
{
	if (type == '"')
		return filename;
	else if (type == '<') {
		return strcat2(INCLUDE, filename);
	} else
		return NULL;
}

char *strcat2(const char *s1, const char *s2)
{
	char *s = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	char *p = s;
	for (; *s1; s1++)
		*p++ = *s1;
	for (; *s2; s2++)
		*p++ = *s2;
	*p = '\0';
	return s;
}
