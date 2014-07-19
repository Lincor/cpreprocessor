#include <stdio.h>
#include "stage1.h" // splice lines
#include "stage2.h" // remove comments
#include "stage3.h" // macro expansion and directive handling

int main(void)
{
	FILE *i, *o;

	i = fopen("demo/main.c", "r");
	o = fopen("demo/output.c.1", "w");
	stage1(i, o);
	fclose(i);
	fclose(o);

	i = fopen("demo/output.c.1", "r");
	o = fopen("demo/output.c.2", "w");
	stage2(i, o);
	fclose(i);
	fclose(o);

	i = fopen("demo/output.c.2", "r");
	o = fopen("demo/output.c.3", "w");
	stage3(i, o);
	fclose(i);
	fclose(o);

	return 0;
}
