default:
	clang test.c filestack.c stage1.c stage2.c stage3.c

debug:
	clang -g test.c filestack.c stage1.c stage2.c stage3.c
