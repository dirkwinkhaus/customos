# Kernel with Grub
sudo dd if=myos.iso of=/dev/sdx && sync

## Usage

### Run qemu
make qemu

### Run gdb
make gdb

#### Output
docker exec -i compiler \
	gdb -x /root/gdb_startup.gdb
GNU gdb (Debian 7.12-6) 7.12.0.20161007-git
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word".
add symbol table from file "/source/out/kernel_asm.o" at
	.text_addr = 0x7c00
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x0000fff0 in ?? ()
(gdb) break _start
Breakpoint 1 at 0x7c00: file /source/kernel/kernel.asm, line 66.
(gdb) continue
Continuing.

Breakpoint 1, _start () at /source/kernel/kernel.asm:66
66		mov $stack_top, %esp
(gdb) 
