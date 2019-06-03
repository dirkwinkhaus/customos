# boot targets

lib_directory = /source/lib
out_directory = /source/out

compile-kernel: working_directory = /source/kernel
compile-kernel: prepare-release
	docker exec -i compiler \
	i686-elf-as -g $(working_directory)/kernel.asm -o $(out_directory)/kernel_asm.o
	docker exec -i compiler \
	i686-elf-g++ -g -I $(lib_directory) -c $(working_directory)/kernel.cpp -o $(out_directory)/kernel_c.o -ffreestanding -O0 -Wall -Wextra -fno-exceptions -fno-rtti
	docker exec -i compiler \
	i686-elf-g++ -g -T $(working_directory)/kernel.ld -o $(release_directory)/boot/kernel.bin -ffreestanding -O0 -nostdlib $(out_directory)/kernel_asm.o $(out_directory)/kernel_c.o
