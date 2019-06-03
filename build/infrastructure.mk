#infrastructure

setup: setup-compiler

stop: remove-compiler

prepare-release:
	mkdir -p rc/boot/grub

release-clean:
	cd rc && find ./ ! -name '.gitignore' ! -name '.' -exec rm -fr {} \;

clean: release-clean remove-compiler

setup: setup-compiler

burn: compile
	docker exec -i compiler \
	grub-mkrescue -o /iso/preos.iso /release

compile: compile-kernel
	cp src/infrastructure/grub/grub.cfg rc/boot/grub

run:
	docker exec -it compiler \
	qemu-system-i386 -curses -cdrom /iso/preos.iso

qemu:
	docker exec -it compiler \
	qemu-system-i386 -curses -gdb tcp::9090 -S -cdrom /iso/preos.iso

qemu-stop:
	docker exec -i compiler \
	ps aux | grep qemu | grep curses | awk '{print $$2}' | xargs kill

gdb:
	docker exec -i compiler \
	gdb -x /root/gdb_startup.gdb
