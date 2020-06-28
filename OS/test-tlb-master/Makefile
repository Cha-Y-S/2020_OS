test-tlb: test-tlb.c
	gcc -g -Wall -O test-tlb.c -o test-tlb -lm

run: test-tlb
	for i in 4k 8k 16k 32k 64k 128k 256k 512k 1M 2M 4M 6M 8M 16M 32M 64M 128M 256M ; do echo "$$i:"; ./test-tlb -H $$i 16; ./test-tlb $$i 16 ; ./test-tlb -Hr $$i 16; ./test-tlb -r $$i 16; done

run_map: test-tlb
	for i in 64 128 256 512 1k 2k 4k 8k 16k 32k 64k 128k 256k 512k 1M 2M 4M 8M 16M 32M 64M 128M 256M 512M 1G 2G 4G; do echo -n "$$i,"; ./test-tlb -r $$i 64; done;

run_16: test-tlb
	for i in 64 4k 32k 128k 512k 2M 4M 8M 32M 64M 128M 512M 1024M ; do echo -n "$$i,"; ./test-tlb -r $$i 16; done

run_32: test-tlb
	for i in 64 4k 32k 128k 512k 2M 4M 8M 32M 64M 128M 512M 1024M ; do echo -n "$$i,"; ./test-tlb -r $$i 32; done

run_64: test-tlb
	for i in 64 4k 32k 128k 512k 2M 4M 8M 32M 64M 128M 512M 1024M ; do echo -n "$$i,"; ./test-tlb -r $$i 64; done

run_test: test-tlb
	for i in 64 4k 32k 64k 128k 256k 512k 1M 1536k 2M 2560k 3M 3584k 4M 8M 32M 64M 128M 512M ; do echo -n "$$i,"; ./test-tlb -r $$i 64; done

run_16_test: test-tlb
	for i in 32k 64k 128k 256k 512k 1M 2M 4M 8M 16M 32M 64M ; do echo -n "$$i,"; ./test-tlb -r $$i 4 ; done


run_same_16: test-tlb
	for i in 4k 8k 16k 32k 64k 128k 256k 512k 1M 2M 4M ; do echo -n "$$i,"; ./test-tlb -r $$i 16 ; done > same_16.xlsx

run_same_32: test-tlb
	for i in 4k 8k 16k 32k 64k 128k 256k 512k 1M 2M 4M ; do echo -n "$$i,"; ./test-tlb -r $$i 32 ; done > same_32.xlsx

run_same_64: test-tlb
	for i in 4k 8k 16k 32k 64k 128k 256k 512k 1M 2M 4M ; do echo -n "$$i,"; ./test-tlb -r $$i 64 ; done > same_64.xlsx

run_same_128: test-tlb
	for i in 4k 8k 16k 32k 64k 128k 256k 512k 1M 2M 4M ; do echo -n "$$i,"; ./test-tlb -r $$i 128 ; done > same_128.xlsx

run_same_256: test-tlb
	for i in 4k 8k 16k 32k 64k 128k 256k 512k 1M 2M 4M ; do echo -n "$$i,"; ./test-tlb -r $$i 256 ; done > same_256.xlsx

run_same_512: test-tlb
	for i in 4k 8k 16k 32k 64k 128k 256k 512k 1M 2M 4M; do echo -n "$$i,"; ./test-tlb -r $$i 512 ; done > same_512.xlsx

run_same_1k: test-tlb
	for i in 4k 8k 16k 32k 64k 128k 256k 512k 1M 2M 4M; do echo -n "$$i,"; ./test-tlb -r $$i 1k ; done > same_1k.xlsx


#
# 15485863 is a random prime number that is used as a index into
# the 128MB array. 15485863*4=61943452
odd-case: test-tlb
	./test-tlb 128M 61943452
