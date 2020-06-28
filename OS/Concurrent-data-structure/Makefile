test: test.c
	gcc -o test test.c -pthread

run: test
	for i in 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 ; do echo "$$i: "; ./test $$i; done;
