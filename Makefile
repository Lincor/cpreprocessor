CC=cc
default:
	$(CC) test.c filestack.c stage1.c stage2.c stage3.c -o test

debug:
	$(CC) -g test.c filestack.c stage1.c stage2.c stage3.c -o test
